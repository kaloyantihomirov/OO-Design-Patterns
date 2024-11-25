#include <numbers>

#include "StringToFigure.h"
#include "catch_amalgamated.hpp"

TEST_CASE("Creating a circle from string representation works correctly")
{
	std::string circleStr = "circle 5";
	Figure* circle = StringToFigure::createFrom(circleStr);
	REQUIRE(circle->toString() == "circle 5");
	REQUIRE(abs(circle->getPerimeter() - 5 * std::numbers::pi * 2) <= std::numeric_limits<double>::epsilon());
	delete circle;
}

TEST_CASE("Creating a circle correctly ignores white space characters")
{
	std::string circleStr = "circle    5          ";
	Figure* circle = StringToFigure::createFrom(circleStr);
	REQUIRE(circle->toString() == "circle 5");
	delete circle;
}

TEST_CASE("Creating a circle throws when given representation with more than one dimension")
{
	SECTION("Two dimensions give")
	{
		std::string circleStr = "circle 5 6";
		REQUIRE_THROWS_AS(StringToFigure::createFrom(circleStr), std::invalid_argument);
	}
	SECTION("Three dimensions given")
	{
		std::string circleStr = "circle 5 6 7";
		REQUIRE_THROWS_AS(StringToFigure::createFrom(circleStr), std::invalid_argument);
	}
}

TEST_CASE("Creating a circle throws when given no dimensions in representation")
{
	std::string circleStr = "circle";
	REQUIRE_THROWS_AS(StringToFigure::createFrom(circleStr), std::invalid_argument);
}

TEST_CASE("Creating a circle throws when given a str dimension")
{
	std::string circleStr = "circle dim1";
	REQUIRE_THROWS_AS(StringToFigure::createFrom(circleStr), std::invalid_argument);
}

// note that in fact the constructor of the circle is the one that throws the
// exception, but we are testing the factory method here, so there's no need to continue in that direction
// (as it's expected we've already covered the constructor)
TEST_CASE("Creating a circle throws when given negative radius")
{
	std::string circleStr = "circle -5";
	REQUIRE_THROWS_AS(StringToFigure::createFrom(circleStr), std::invalid_argument);
}

TEST_CASE("Creating a triangle from string representation works correctly")
{
	std::string triangleStr = "triangle 3 4 5";
	Figure* triangle = StringToFigure::createFrom(triangleStr);
	REQUIRE(triangle->toString() == "triangle 3 4 5");
	REQUIRE(abs(triangle->getPerimeter() - 12) <= std::numeric_limits<double>::epsilon());
	delete triangle;
}

TEST_CASE("Creating a triangle throws when params provided in representation are less than 3")
{
	SECTION("Two dimensions given")
	{
		std::string triangleStr = "triangle 3 4";
		REQUIRE_THROWS_AS(StringToFigure::createFrom(triangleStr), std::invalid_argument);
	}
	SECTION("One dimension given")
	{
		std::string triangleStr = "triangle 3";
		REQUIRE_THROWS_AS(StringToFigure::createFrom(triangleStr), std::invalid_argument);
	}
	SECTION("One dimension which is str given")
	{
		std::string triangleStr = "triangle dim1";
		REQUIRE_THROWS_AS(StringToFigure::createFrom(triangleStr), std::invalid_argument);
	}
	SECTION("No dimension given")
	{
		std::string triangleStr = "triangle";
		REQUIRE_THROWS_AS(StringToFigure::createFrom(triangleStr), std::invalid_argument);
	}
}

TEST_CASE("Creating a triangle throws when params provided in representation are 4")
{
	std::string triangleStr = "triangle 3 4 5 6";
	REQUIRE_THROWS_AS(StringToFigure::createFrom(triangleStr), std::invalid_argument);
}

TEST_CASE("Creating a triangle throws when some of the params provided in representation are not numbers")
{
	SECTION("Second and third are not numbers")
	{
		std::string triangleStr = "triangle 3 dim2 dim3";
		REQUIRE_THROWS_AS(StringToFigure::createFrom(triangleStr), std::invalid_argument);
	}
	SECTION("First is not a number")
	{
		std::string triangleStr = "triangle 3D 2 3";
		REQUIRE_THROWS_AS(StringToFigure::createFrom(triangleStr), std::invalid_argument);
	}
}

TEST_CASE("Creating a figure fails for empty figure type")
{
	std::string s;
	REQUIRE_THROWS_AS(StringToFigure::createFrom(s), std::invalid_argument);
}

TEST_CASE("Creating a figure fails for unknown figure type")
{
	std::string s = "very_cool_boat 124";
	REQUIRE_THROWS_AS(StringToFigure::createFrom(s), std::invalid_argument);
}
