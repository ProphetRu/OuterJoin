#include "SQLInsert.h"

SQLInsert::SQLInsert(const std::string& table_name, const Record& record) noexcept :
	ISQL{ SQLType::Insert },
	m_TableName{ table_name },
	m_Record{ record }
{
}

std::string SQLInsert::GetTableName() const noexcept
{
	return m_TableName;
}

Record SQLInsert::GetRecord() const noexcept
{
	return m_Record;
}
