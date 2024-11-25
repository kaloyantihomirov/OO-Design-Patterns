#include <numbers>

#include "StringToFigure.h"
#include "catch_amalgamated.hpp"

TEST_CASE("Creating a circle from string representation")
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
