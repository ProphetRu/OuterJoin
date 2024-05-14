#include "SQLHandler.h"
#include "SQLInsert.h"
#include "SQLTruncate.h"
#include "SQLIntersection.h"
#include "SQLSymmetricDifference.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>

SQLQuery SQLHandler::Handle(const std::string& sql_query) const
{
    auto is_equal_nocase = [](const std::string& a, const std::string& b) noexcept
    {
        return std::ranges::equal(
            a, b,
            [](char ac, char bc) { return std::tolower(ac) == std::tolower(bc); }
        );
    };

    if (sql_query.empty())
    {
        throw std::invalid_argument("SQL query is empty");
    }

    std::istringstream iss{ sql_query };
    std::string command;
    iss >> command;

    if (is_equal_nocase(command, "INSERT")) 
    {
        std::string table_name;
	    int id{};
        std::string name;
        if (!(iss >> table_name >> id >> name))
        {
            throw std::runtime_error("Invalid query param");
        }

        return HandleInsert(table_name, id, name);
    }
    if (is_equal_nocase(command, "TRUNCATE")) 
    {
        std::string table_name;
        if (!(iss >> table_name)) 
        {
            throw std::runtime_error("Invalid query param");
        }

        return HandleTruncate(table_name);
    }
    if (is_equal_nocase(command, "INTERSECTION")) 
    {
        return HandleIntersection();
    }
    if (is_equal_nocase(command, "SYMMETRIC_DIFFERENCE"))
    {
        return HandleSymmetricDifference();
    }
    
    throw std::runtime_error("Invalid query");
}

SQLQuery SQLHandler::HandleInsert(const std::string& table_name, int id, const std::string& name) const noexcept
{
	return std::make_unique<SQLInsert>(table_name, std::make_pair(id, name));
}

SQLQuery SQLHandler::HandleTruncate(const std::string& table_name) const noexcept
{
	return std::make_unique<SQLTruncate>(table_name);
}

SQLQuery SQLHandler::HandleIntersection() const noexcept
{
	return std::make_unique<SQLIntersection>();
}

SQLQuery SQLHandler::HandleSymmetricDifference() const noexcept
{
	return std::make_unique<SQLSymmetricDifference>();
}
