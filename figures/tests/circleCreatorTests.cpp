#include <numbers>

#include "catch_amalgamated.hpp"

#include "CircleCreator.h"

struct CircleCreatorTestFixture
{
	CircleCreator circleCreator;
};

TEST_CASE_METHOD(CircleCreatorTestFixture, "Creating a circle from string representation works correctly")
{
	std::string circleStr = "5";
	std::unique_ptr<Figure> circle = circleCreator.createFigureFromString(circleStr);
	REQUIRE(circle->toString() == "circle 5");
	REQUIRE(abs(circle->getPerimeter() - 5 * std::numbers::pi * 2) <= std::numeric_limits<double>::epsilon());
}

TEST_CASE_METHOD(CircleCreatorTestFixture, "Creating a circle correctly ignores white space characters")
{
	std::string circleStr = "    5          ";
	std::unique_ptr<Figure> circle = circleCreator.createFigureFromString(circleStr);
	REQUIRE(circle->toString() == "circle 5");
}

TEST_CASE_METHOD(CircleCreatorTestFixture, "Creating a circle throws when given representation with more than one dimension")
{
	SECTION("Two dimensions given")
	{
		std::string circleStr = "5 6";
		REQUIRE_THROWS_AS(circleCreator.createFigureFromString(circleStr), std::invalid_argument);
	}
	SECTION("Three dimensions given")
	{
		std::string circleStr = "5 6 7";
		REQUIRE_THROWS_AS(circleCreator.createFigureFromString(circleStr), std::invalid_argument);
	}
}

TEST_CASE_METHOD(CircleCreatorTestFixture, "Creating a circle throws when given empty str for representation")
{
	std::string circleStr = "";
	REQUIRE_THROWS_AS(circleCreator.createFigureFromString(circleStr), std::invalid_argument);
}

TEST_CASE_METHOD(CircleCreatorTestFixture, "Creating a circle throws when given a whitespace string for representation")
{
	std::string circleStr = "       ";
	REQUIRE_THROWS_AS(circleCreator.createFigureFromString(circleStr), std::invalid_argument);
}

TEST_CASE_METHOD(CircleCreatorTestFixture, "Creating a circle throws when given a str dimension")
{
	std::string circleStr = "dim1";
	REQUIRE_THROWS_AS(circleCreator.createFigureFromString(circleStr), std::invalid_argument);
}

// note that in fact the constructor of the circle is the one that throws the
// exception, but we are testing the triangle creator class here, so there's no need to continue in that direction
// (as it's expected we've already covered the constructor)
TEST_CASE_METHOD(CircleCreatorTestFixture, "Creating a circle throws when given negative radius")
{
	std::string circleStr = "-5";
	REQUIRE_THROWS_AS(circleCreator.createFigureFromString(circleStr), std::invalid_argument);
}

