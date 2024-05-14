#pragma once

#include "ISQL.h"
#include "DataTypes.h"

/**
 * @brief A class representing a SQL INSERT statement.
 */
class SQLInsert final : public ISQL
{
public:
    /**
     * @brief Constructs a SQLInsert object with the specified table name and record.
     * @param table_name The name of the table to insert into.
     * @param record The record to insert.
     */
    explicit SQLInsert(const std::string& table_name, const Record& record) noexcept;

    /**
     * @brief Default destructor.
     */
    virtual ~SQLInsert() noexcept override = default;

    /**
     * @brief Retrieves the name of the table for the insert operation.
     * @return The table name.
     */
    [[nodiscard]] std::string GetTableName() const noexcept;

    /**
     * @brief Retrieves the record to be inserted.
     * @return The record to insert.
     */
    [[nodiscard]] Record GetRecord() const noexcept;

private:
    std::string m_TableName; /**< The name of the table for insertion. */
    Record m_Record; /**< The record to be inserted. */
};
