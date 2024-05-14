#pragma once

#include "ISQL.h"
#include "DataTypes.h"

/**
 * @brief A class representing a SQL TRUNCATE statement.
 */
class SQLTruncate final : public ISQL
{
public:
    /**
     * @brief Constructs a SQLTruncate object with the specified table name.
     * @param table_name The name of the table to truncate.
     */
    explicit SQLTruncate(const std::string& table_name) noexcept;

    /**
     * @brief Default destructor.
     */
    virtual ~SQLTruncate() noexcept override = default;

    /**
     * @brief Retrieves the name of the table to truncate.
     * @return The name of the table.
     */
    [[nodiscard]] std::string GetTableName() const noexcept;

private:
    std::string m_TableName; /**< The name of the table to truncate. */
};
