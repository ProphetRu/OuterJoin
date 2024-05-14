#pragma once

#include "DataTypes.h"
#include <shared_mutex>

/**
 * @brief A class representing a Database Management System (DBMS).
 */
class DBMS final
{
public:
    /**
     * @brief Adds a new table to the DBMS.
     * @param table_name The name of the table to add.
     */
    void AddTable(const std::string& table_name) noexcept;

    /**
     * @brief Inserts a record into the specified table.
     * @param table_name The name of the table.
     * @param record The record to insert.
     */
    void Insert(const std::string& table_name, const Record& record);

    /**
     * @brief Truncates (clears) the specified table.
     * @param table_name The name of the table to truncate.
     */
    void Truncate(const std::string& table_name);

    /**
     * @brief Computes the intersection of all tables in the DBMS.
     * @return The joined table representing the intersection.
     */
    [[nodiscard]] JoinedTable Intersection();

    /**
     * @brief Computes the symmetric difference of all tables in the DBMS.
     * @return The joined table representing the symmetric difference.
     */
    [[nodiscard]] JoinedTable SymmetricDifference();

private:
    Tables m_Tables; /**< The collection of tables in the DBMS. */
    std::shared_timed_mutex m_Mutex; /**< The mutex for thread-safe access to tables. */
};
