#pragma once

#include <string>

/**
 * @brief An enumeration representing different types of SQL operations.
 */
enum class SQLType
{
    Insert = 0, /**< Represents an INSERT operation. */
    Truncate,   /**< Represents a TRUNCATE operation. */
    Intersection, /**< Represents an INTERSECTION operation. */
    SymmetricDifference, /**< Represents a SYMMETRIC DIFFERENCE operation. */
};

/**
 * @brief An interface class for SQL operations.
 */
class ISQL
{
public:
    /**
     * @brief Constructs an ISQL object with the specified SQL type.
     * @param type The type of the SQL operation.
     */
    explicit ISQL(SQLType type) noexcept;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ISQL() noexcept = default;

    /**
     * @brief Retrieves the type of the SQL operation.
     * @return The SQLType of the operation.
     */
    [[nodiscard]] SQLType GetType() const noexcept;

private:
    SQLType m_Type; /**< The type of the SQL operation. */
};
