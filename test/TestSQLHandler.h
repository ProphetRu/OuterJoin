#pragma once

#include <gtest/gtest.h>
#include "ISQL.h"
#include "SQLHandler.h"
#include "SQLInsert.h"
#include "SQLTruncate.h"
#include "SQLIntersection.h"
#include "SQLSymmetricDifference.h"

// the linking error without this #include
#include "SQLHandler.cpp"
#include "ISQL.cpp"
#include "SQLInsert.cpp"
#include "SQLTruncate.cpp"
#include "SQLIntersection.cpp"
#include "SQLSymmetricDifference.cpp"

namespace TestSQLHandler
{
	TEST(TestSQLHandler, TestEmptyQuery)
	{
		constexpr SQLHandler sql_handler;
		EXPECT_THROW(sql_handler.Handle(""), std::invalid_argument);
	}

	TEST(TestSQLHandler, TestInvalidQuery)
	{
		constexpr SQLHandler sql_handler;
		EXPECT_THROW(sql_handler.Handle("INVALID"), std::runtime_error);
	}

	TEST(TestSQLHandler, TestInvalidQueryInsert)
	{
		constexpr SQLHandler sql_handler;
		EXPECT_THROW(sql_handler.Handle("INSERT"), std::runtime_error);
	}

	TEST(TestSQLHandler, TestInvalidQueryTruncate)
	{
		constexpr SQLHandler sql_handler;
		EXPECT_THROW(sql_handler.Handle("TRUNCATE"), std::runtime_error);
	}

	TEST(TestSQLHandler, TestCorrectQueryInsert)
	{
		constexpr SQLHandler sql_handler;

		EXPECT_NO_THROW(sql_handler.Handle("INSERT A 0 test"));

		const auto query{ sql_handler.Handle("INSERT A 0 test") };
		const auto query_ptr{ dynamic_cast<SQLInsert*>(query.get()) };
		EXPECT_TRUE(query_ptr != nullptr);
	}

	TEST(TestSQLHandler, TestCorrectQueryTruncate)
	{
		constexpr SQLHandler sql_handler;

		EXPECT_NO_THROW(sql_handler.Handle("TRUNCATE A"));

		const auto query{ sql_handler.Handle("TRUNCATE A") };
		const auto query_ptr{ dynamic_cast<SQLTruncate*>(query.get()) };
		EXPECT_TRUE(query_ptr != nullptr);
	}

	TEST(TestSQLHandler, TestCorrectQueryIntersection)
	{
		constexpr SQLHandler sql_handler;

		EXPECT_NO_THROW(sql_handler.Handle("INTERSECTION"));

		const auto query{ sql_handler.Handle("INTERSECTION") };
		const auto query_ptr{ dynamic_cast<SQLIntersection*>(query.get()) };
		EXPECT_TRUE(query_ptr != nullptr);
	}

	TEST(TestSQLHandler, TestCorrectQuerySymmetricDifference)
	{
		constexpr SQLHandler sql_handler;

		EXPECT_NO_THROW(sql_handler.Handle("SYMMETRIC_DIFFERENCE"));

		const auto query{ sql_handler.Handle("SYMMETRIC_DIFFERENCE") };
		const auto query_ptr{ dynamic_cast<SQLSymmetricDifference*>(query.get()) };
		EXPECT_TRUE(query_ptr != nullptr);
	}
}
