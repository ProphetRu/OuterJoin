#pragma once

#include "ISQL.h"

/**
 * @brief A class representing a SQL INTERSECTION operation.
 */
class SQLIntersection final : public ISQL
{
public:
    /**
     * @brief Constructs a SQLIntersection object.
     */
    SQLIntersection() noexcept;

    /**
     * @brief Default destructor.
     */
    virtual ~SQLIntersection() noexcept override = default;
};
