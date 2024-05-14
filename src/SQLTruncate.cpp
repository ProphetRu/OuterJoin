#include "SQLTruncate.h"

SQLTruncate::SQLTruncate(const std::string& table_name) noexcept :
	ISQL{ SQLType::Truncate },
	m_TableName{ table_name }
{
}

std::string SQLTruncate::GetTableName() const noexcept
{
	return m_TableName;
}
