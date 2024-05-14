#include "DBMS.h"
#include <stdexcept>

void DBMS::AddTable(const std::string& table_name) noexcept
{
	if (!table_name.empty())
	{
		m_Tables[table_name] = {};
	}
}

void DBMS::Insert(const std::string& table_name, const Record& record)
{
	if (table_name.empty() || record.first < 0 || record.second.empty())
	{
		throw std::invalid_argument("Invalid argument");
	}

	if (!m_Tables.contains(table_name))
	{
		throw std::runtime_error("Table doesn't exist");
	}

	if (m_Tables[table_name].contains(record.first))
	{
		throw std::runtime_error("duplicate " + std::to_string(record.first));
	}

	std::lock_guard writer_lock{ m_Mutex }; // writer
	m_Tables[table_name].emplace(record);
}

void DBMS::Truncate(const std::string& table_name)
{
	if (table_name.empty())
	{
		throw std::invalid_argument("Invalid argument");
	}

	if (!m_Tables.contains(table_name))
	{
		throw std::runtime_error("Table doesn't exist");
	}

	std::lock_guard writer_lock{ m_Mutex }; // writer
	m_Tables.erase(table_name);
}

JoinedTable DBMS::Intersection()
{
	JoinedTable table;

	if (m_Tables.empty())
	{
		throw std::runtime_error("DB is empty");
	}

	if (m_Tables.size() < 2)
	{
		throw std::runtime_error("DB contains only one table");
	}

	std::shared_lock reader_lock{ m_Mutex }; // reader

	// enum tables
	for (auto it{ begin(m_Tables) }; it != end(m_Tables); ++it)
	{
		for (auto jt{ it }; jt != end(m_Tables); ++jt)
		{
			if (it == jt)
			{
				continue;
			}

			// enum fields
			for (auto table1{ begin(it->second) }; table1 != end(it->second); ++table1)
			{
				for (auto table2{ begin(jt->second) }; table2 != end(jt->second); ++table2)
				{
					if (table1->first == table2->first)
					{
						table[table1->first] = std::make_pair(table1->second, table2->second);
						break;
					}
				}
			}
		}
	}

	return table;
}

JoinedTable DBMS::SymmetricDifference()
{
	JoinedTable table;

	if (m_Tables.empty())
	{
		throw std::runtime_error("DB is empty");
	}

	if (m_Tables.size() < 2)
	{
		throw std::runtime_error("DB contains only one table");
	}

	std::shared_lock reader_lock{ m_Mutex }; // Reader lock

	auto update_table = [&table](const auto& table1, const auto& table2, const bool is_first) noexcept
	{
		for (auto entry1 = begin(table1); entry1 != end(table1); ++entry1)
		{
			auto is_find = false;

			for (auto entry2 = begin(table2); entry2 != end(table2); ++entry2)
			{
				if (entry1->first == entry2->first)
				{
					is_find = true;
					break;
				}
			}

			if (!is_find)
			{
				if (is_first)
				{
					table[entry1->first] = std::make_pair(entry1->second, "");
				}
				else
				{
					table[entry1->first] = std::make_pair("", entry1->second);
				}
			}
		}
	};

	// Enumerate tables
	for (auto it = begin(m_Tables); it != end(m_Tables); ++it)
	{
		for (auto jt = it; jt != end(m_Tables); ++jt)
		{
			if (it == jt)
			{
				continue;
			}

			// Enumerate fields
			update_table(it->second, jt->second, true);
			update_table(jt->second, it->second, false);
		}
	}

	return table;
}
