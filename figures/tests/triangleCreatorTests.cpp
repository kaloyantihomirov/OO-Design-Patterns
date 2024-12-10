#include "catch_amalgamated.hpp"

#include "TriangleConfig.h"
#include "TriangleCreator.h"

struct TriangleCreatorTestFixture
{
	TriangleCreator triangleCreator;
};

TEST_CASE_METHOD(TriangleCreatorTestFixture, "Creating a triangle from string representation works correctly")
{
	std::string triangleStr = "3 4 5";
	std::unique_ptr<Figure> triangle = triangleCreator.createFigureFromString(triangleStr);
	REQUIRE(triangle->toString() == "triangle 3 4 5");
	REQUIRE(abs(triangle->getPerimeter() - 12) <= std::numeric_limits<double>::epsilon());
}

TEST_CASE_METHOD(TriangleCreatorTestFixture, "Creating a triangle from string representation with decimal point sides works correctly")
{
	std::string triangleStr = "3.5 4.5 5.5";
	std::unique_ptr<Figure> triangle = triangleCreator.createFigureFromString(triangleStr);
	REQUIRE(triangle->toString() == "triangle 3.5 4.5 5.5");
	REQUIRE(abs(triangle->getPerimeter() - 13.5) <= std::numeric_limits<double>::epsilon());
}

TEST_CASE_METHOD(TriangleCreatorTestFixture, "Creating a triangle throws when params provided in representation are less than 3")
{
	SECTION("Two dimensions given")
	{
		std::string triangleStr = "3 4";
		REQUIRE_THROWS_AS(triangleCreator.createFigureFromString(triangleStr), std::invalid_argument);
	}
	SECTION("One dimension given")
	{
		std::string triangleStr = "3";
		REQUIRE_THROWS_AS(triangleCreator.createFigureFromString(triangleStr), std::invalid_argument);
	}
	SECTION("One dimension given which is string")
	{
		std::string triangleStr = "dim1";
		REQUIRE_THROWS_AS(triangleCreator.createFigureFromString(triangleStr), std::invalid_argument);
	}
	SECTION("No dimension given")
	{
		std::string triangleStr = " ";
		REQUIRE_THROWS_AS(triangleCreator.createFigureFromString(triangleStr), std::invalid_argument);
	}
}

TEST_CASE_METHOD(TriangleCreatorTestFixture, "Creating a triangle throws when params provided in representation are 4")
{
	std::string triangleStr = "3 4 5 6";
	REQUIRE_THROWS_AS(triangleCreator.createFigureFromString(triangleStr), std::invalid_argument);
}

TEST_CASE_METHOD(TriangleCreatorTestFixture, "Creating a triangle throws when some of the params provided in representation are not numbers")
{
	SECTION("Second and third are not numbers")
	{
		std::string triangleStr = "3 dim2 dim3";
		REQUIRE_THROWS_AS(triangleCreator.createFigureFromString(triangleStr), std::invalid_argument);
	}
	SECTION("First is not a number")
	{
		std::string triangleStr = "3D 2 3";
		REQUIRE_THROWS_AS(triangleCreator.createFigureFromString(triangleStr), std::invalid_argument);
	}
}

TEST_CASE_METHOD(TriangleCreatorTestFixture, "Creating a triangle throws when given empty representation")
{
	REQUIRE_THROWS_AS(triangleCreator.createFigureFromString(""), std::invalid_argument);
}

//We can generate a lot of tests with lesser code using the so-called data-driven/parameterised tests
TEST_CASE_METHOD(TriangleCreatorTestFixture, "Creating a triangle throws for invalid string representations")
{
	std::string invalidString = GENERATE(
		"3 1",      // Two dimensions
		"3    4"    // Two dimensions with intervals
		"3",        // One dimension
		"dim1",     // One non-numeric dimension
		"",         // Empty representation
		"3 4 5 6",  // Four dimensions
		"3 dim2 dim3", // Mixed valid and invalid dimensions
		"3D 2 3"    // Non-numeric first dimension
	);

	REQUIRE_THROWS_AS(triangleCreator.createFigureFromString(invalidString), std::invalid_argument);
}

TEST_CASE_METHOD(TriangleCreatorTestFixture, "Creating a random triangle should work without throwing")
{
	std::unique_ptr<Figure> triangle;

	for (size_t i = 0; i < 10000; i++)
	{
		REQUIRE_NOTHROW(triangle = triangleCreator.createRandomFigure());
		REQUIRE(triangle != nullptr);
	}
}

TEST_CASE_METHOD(TriangleCreatorTestFixture, "Creating a random triangle should return a triangle with perimeter satisfying side constraints")
{
	std::unique_ptr<Figure> triangle;

	for (size_t i = 0; i < 10000; i++)
	{
		triangle = triangleCreator.createRandomFigure();
		INFO(triangle->getPerimeter());
		REQUIRE(((triangle->getPerimeter() >= 3 * TriangleConfig::twoOfTheSidesMinLengthRandom) 
			&& (triangle->getPerimeter() <= 4 * TriangleConfig::twoOfTheSidesMaxLengthRandom - 1)));
		//the second inequality comes from the fact that a + b < c for every two sides a, b of a triangle
		//maximising two of the sides, let's say a = max and b = max, and taking into consideration
		//the triangle inequality, we would get c <= a + b - 1 = 2max - 1.
	}
}

