#include "ISQL.h"

ISQL::ISQL(SQLType type) noexcept :
	m_Type{ type }
{
}

SQLType ISQL::GetType() const noexcept
{
	return m_Type;
}
