#pragma once

#include <string>
#include <map>
#include <unordered_map>

/**
 * @brief A type alias for a record, which is a pair of integer and string.
 */
using Record = std::pair<int, std::string>;

/**
 * @brief A type alias for a table, which is a map of integer keys to string values.
 */
// id, name
using Table = std::map<int, std::string>;

/**
 * @brief A type alias for a collection of tables, which is an unordered map of string keys to Table values.
 */
// table name, table
using Tables = std::unordered_map<std::string, Table>;

/**
 * @brief A type alias for a joined table, which is a map of integer keys to pairs of strings.
 */
using JoinedTable = std::map<int, std::pair<std::string, std::string>>;
