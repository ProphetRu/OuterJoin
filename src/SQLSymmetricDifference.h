#pragma once

#include "ISQL.h"

/**
 * @brief A class representing a SQL SYMMETRIC DIFFERENCE operation.
 */
class SQLSymmetricDifference final : public ISQL
{
public:
    /**
     * @brief Constructs a SQLSymmetricDifference object.
     */
    SQLSymmetricDifference() noexcept;

    /**
     * @brief Default destructor.
     */
    virtual ~SQLSymmetricDifference() noexcept override = default;
};
