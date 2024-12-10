#include "catch_amalgamated.hpp"

#include "Rectangle.h"

TEST_CASE("Rectangle creates successfully")
{
	Rectangle r(3, 4);
	double perimeter = r.getPerimeter();
	REQUIRE(r.toString() == "rectangle 3 4");
	REQUIRE(abs(perimeter - 14) <= std::numeric_limits<double>::epsilon());
}

TEST_CASE("Creating a rectangle with a negative side causes an exception to be thrown")
{
	SECTION("Throws when first side is negative")
	{
		REQUIRE_THROWS_AS(Rectangle(-1, 5), std::invalid_argument);
	}
	SECTION("Throws when second side is negative")
	{
		REQUIRE_THROWS_AS(Rectangle(1, -5), std::invalid_argument);
	}
}

TEST_CASE("Creating a rectangle with a side equal to zero causes an exception to be thrown")
{
	SECTION("Throws when first side is zero")
	{
		REQUIRE_THROWS_AS(Rectangle(0, 5), std::invalid_argument);
	}
	SECTION("Throws when second side is zero")
	{
		REQUIRE_THROWS_AS(Rectangle(1, 0), std::invalid_argument);
	}
}

TEST_CASE("Creating a rectangle with width and height's sum giving too large perimeter causes an exception to be thrown")
{
	REQUIRE_THROWS_AS(Rectangle(std::numeric_limits<double>::max() / 2, std::numeric_limits<double>::max() / 2), std::overflow_error);
}

//a perfect showcase of loss of precision when working with floating point numbers 
//this test mathematically should fail!
//TEST_CASE("Creating a rectangle with sides that give too large perimeter causes an exception to be thrown")
//{
//	REQUIRE_THROWS_AS(Rectangle(std::numeric_limits<double>::max() / 4 + 1, std::numeric_limits<double>::max() / 4), std::overflow_error);
//}

//this would pass, but the test is not understandable 
//TEST_CASE("Creating a rectangle with sides that give too large perimeter causes an exception to be thrown")
//{
//	REQUIRE_THROWS_AS(Rectangle(std::numeric_limits<double>::max() / 4 + 1e293, std::numeric_limits<double>::max() / 4), std::overflow_error);
//}

TEST_CASE("Rectangle toString() method works correctly")
{
	Rectangle r(3, 4);
	REQUIRE(r.toString() == "rectangle 3 4");
}