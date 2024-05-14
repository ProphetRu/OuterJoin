#pragma once

#include "ISQL.h"
#include <memory>

/**
 * @brief Type alias for a unique pointer to an ISQL object.
 */
using SQLQuery = std::unique_ptr<ISQL>;

/**
 * @brief A class for handling SQL queries and generating corresponding ISQL objects.
 */
class SQLHandler final
{
public:
    /**
     * @brief Handles the given SQL query and generates the corresponding ISQL object.
     * @param sql_query The SQL query to handle.
     * @return A unique pointer to the generated ISQL object.
     */
    SQLQuery Handle(const std::string& sql_query) const;

private:
    /**
     * @brief Handles an INSERT SQL query.
     * @param table_name The name of the table.
     * @param id The ID for insertion.
     * @param name The name for insertion.
     * @return A unique pointer to the generated ISQL object.
     */
    SQLQuery HandleInsert(const std::string& table_name, int id, const std::string& name) const noexcept;

    /**
     * @brief Handles a TRUNCATE SQL query.
     * @param table_name The name of the table to truncate.
     * @return A unique pointer to the generated ISQL object.
     */
    SQLQuery HandleTruncate(const std::string& table_name) const noexcept;

    /**
     * @brief Handles an INTERSECTION SQL query.
     * @return A unique pointer to the generated ISQL object.
     */
    SQLQuery HandleIntersection() const noexcept;

    /**
     * @brief Handles a SYMMETRIC DIFFERENCE SQL query.
     * @return A unique pointer to the generated ISQL object.
     */
    SQLQuery HandleSymmetricDifference() const noexcept;
};
