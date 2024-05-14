#pragma once

#include <gtest/gtest.h>
#include "DBMS.h"

// the linking error without this #include
#include "DBMS.cpp"

#define UNUSED(x) (void)(x); // hack to bypass [[nodiscard]]

namespace TestDBMS
{
	TEST(TestDBMS, TestDBMSNoTables)
	{
		DBMS dbms;

		EXPECT_THROW(dbms.Insert("test", std::make_pair(1, "test")), std::runtime_error);
		EXPECT_THROW(dbms.Truncate("test"), std::runtime_error);
		EXPECT_THROW(UNUSED(dbms.Intersection()), std::runtime_error);
		EXPECT_THROW(UNUSED(dbms.SymmetricDifference()), std::runtime_error);
	}

	TEST(TestDBMS, TestDBMSAddTable)
	{
		DBMS dbms;
		EXPECT_NO_THROW(dbms.AddTable("test"));
	}

	TEST(TestDBMS, TestDBMSInsert)
	{
		DBMS dbms;
		dbms.AddTable("A");
		
		EXPECT_THROW(dbms.Insert("", std::make_pair(1, "test")), std::invalid_argument);
		EXPECT_THROW(dbms.Insert("B", std::make_pair(1, "test")), std::runtime_error);

		EXPECT_NO_THROW(dbms.Insert("A", std::make_pair(1, "test")));
		EXPECT_THROW(dbms.Insert("A", std::make_pair(1, "test2")), std::runtime_error);
	}

	TEST(TestDBMS, TestDBMSTruncate)
	{
		DBMS dbms;
		dbms.AddTable("A");

		EXPECT_THROW(dbms.Truncate(""), std::invalid_argument);
		EXPECT_THROW(dbms.Truncate("B"), std::runtime_error);

		EXPECT_NO_THROW(dbms.Truncate("A"));
	}

	TEST(TestDBMS, TestDBMSIntersection)
	{
		DBMS dbms;
		EXPECT_THROW(UNUSED(dbms.Intersection()), std::runtime_error);

		dbms.AddTable("A");
		EXPECT_THROW(UNUSED(dbms.Intersection()), std::runtime_error);

		dbms.AddTable("B");
		EXPECT_NO_THROW(UNUSED(dbms.Intersection()));
	}

	TEST(TestDBMS, TestDBMSSymmetricDifference)
	{
		DBMS dbms;
		EXPECT_THROW(UNUSED(dbms.SymmetricDifference()), std::runtime_error);

		dbms.AddTable("A");
		EXPECT_THROW(UNUSED(dbms.SymmetricDifference()), std::runtime_error);

		dbms.AddTable("B");
		EXPECT_NO_THROW(UNUSED(dbms.SymmetricDifference()));
	}
}
