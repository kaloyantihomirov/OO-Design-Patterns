#include "catch_amalgamated.hpp"

#include "Triangle.h"

class CongruentTrianglesFixture
{
public:
	Triangle t1{ 6, 7, 8 };
	Triangle t2{ 8, 6, 7 };
	Triangle t3{ 7, 8, 6 };
};

TEST_CASE("Triangle creates successfully")
{
	Triangle t(3, 4, 5);
	double perimeter = t.getPerimeter();
	REQUIRE(abs(perimeter - 12) <= std::numeric_limits<double>::epsilon());
	REQUIRE(t.toString() == "triangle 3 4 5");
}

TEST_CASE_METHOD(CongruentTrianglesFixture, "Perimeter is the same for congruent triangles")
{
	REQUIRE(abs(t1.getPerimeter() - t2.getPerimeter()) <= std::numeric_limits<double>::epsilon());
	REQUIRE(abs(t1.getPerimeter() - t3.getPerimeter()) <= std::numeric_limits<double>::epsilon());
}

TEST_CASE("Creating a triangle with a negative side causes an exception to be thrown")
{
	SECTION("Throws when first side is negative")
	{
		REQUIRE_THROWS_AS(Triangle(-1, 5, 6), std::invalid_argument);
	}
	SECTION("Throws when second side is negative")
	{
		REQUIRE_THROWS_AS(Triangle(1, -5, 8), std::invalid_argument);
	}
	SECTION("Throws when third side is negative")
	{
		REQUIRE_THROWS_AS(Triangle(1, 5, -8), std::invalid_argument);
	}
}

TEST_CASE("Creating a triangle with a side equal to zero causes an exception to be thrown")
{
	SECTION("Throws when first side is zero")
	{
		REQUIRE_THROWS_AS(Triangle(0, 5, 6), std::invalid_argument);
	}
	SECTION("Throws when second side is zero")
	{
		REQUIRE_THROWS_AS(Triangle(1, 0, 8), std::invalid_argument);
	}
	SECTION("Throws when third side is zero")
	{
		REQUIRE_THROWS_AS(Triangle(1, 5, 0), std::invalid_argument);
	}
}

//not a very good test!
//TEST_CASE("Creating a triangle with sides that give too large perimeter causes an exception to be thrown")
//{
//	REQUIRE_THROWS_AS(Triangle(std::numeric_limits<double>::max() / 3, std::numeric_limits<double>::max() / 3, std::numeric_limits<double>::max() / 3 + 1), std::overflow_error);
//}

TEST_CASE("Creating a triangle with sides that are not a triangle causes an exception to be thrown")
{
	SECTION("Triangle inequality does not hold for first side.")
	{
		REQUIRE_THROWS_AS(Triangle(3, 1, 1), std::invalid_argument);
	}
	SECTION("Triangle inequality does not hold for second side.")
	{
		REQUIRE_THROWS_AS(Triangle(1, 3, 1), std::invalid_argument);
	}
	SECTION("Triangle inequality does not hold for third side.")
	{
		REQUIRE_THROWS_AS(Triangle(1, 1, 3), std::invalid_argument);
	}
}

TEST_CASE("Triangle toString returns correct string representation")
{
	Triangle t(3, 4, 5);
	REQUIRE(t.toString() == "triangle 3 4 5");
}

TEST_CASE_METHOD(CongruentTrianglesFixture, "Triangle toString returns correct string representation for congruent triangles")
{
	REQUIRE(t1.toString() == "triangle 6 7 8");
	REQUIRE(t2.toString() == "triangle 8 6 7");
	REQUIRE(t3.toString() == "triangle 7 8 6");
}