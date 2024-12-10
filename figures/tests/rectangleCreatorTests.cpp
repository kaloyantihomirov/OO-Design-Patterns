#include "catch_amalgamated.hpp"

#include "RectangleCreator.h"
#include "RectangleConfig.h"

struct RectangleCreatorTestFixture
{
    RectangleCreator rectangleCreator;
};

TEST_CASE_METHOD(RectangleCreatorTestFixture, "Creating a rectangle from string representation works correctly") {
    std::string rectangleStr = "5 10";
    std::unique_ptr<Figure> rectangle = rectangleCreator.createFigureFromString(rectangleStr);
    REQUIRE(rectangle->toString() == "rectangle 5 10");
    REQUIRE(abs(rectangle->getPerimeter() - 30) <= std::numeric_limits<double>::epsilon());
}

TEST_CASE_METHOD(RectangleCreatorTestFixture, "Creating a rectangle throws when params provided in representation are less than 2")
{
    SECTION("One dimension given")
	{
        std::string rectangleStr = "5";
        REQUIRE_THROWS_AS(rectangleCreator.createFigureFromString(rectangleStr), std::invalid_argument);
    }
    SECTION("One dimension given which is string")
	{
        std::string rectangleStr = "dim1";
        REQUIRE_THROWS_AS(rectangleCreator.createFigureFromString(rectangleStr), std::invalid_argument);
    }
    SECTION("No dimension given")
	{
        std::string rectangleStr = " ";
        REQUIRE_THROWS_AS(rectangleCreator.createFigureFromString(rectangleStr), std::invalid_argument);
    }
}

TEST_CASE_METHOD(RectangleCreatorTestFixture, "Creating a rectangle throws when params provided in representation are more than 2")
{
    std::string rectangleStr = "5 10 15";
    REQUIRE_THROWS_AS(rectangleCreator.createFigureFromString(rectangleStr), std::invalid_argument);
}

TEST_CASE_METHOD(RectangleCreatorTestFixture, "Creating a rectangle throws when some of the params provided in representation are not numbers")
{
    SECTION("Second is not a number")
	{
        std::string rectangleStr = "5 dim2";
        REQUIRE_THROWS_AS(rectangleCreator.createFigureFromString(rectangleStr), std::invalid_argument);
    }
    SECTION("First is not a number")
	{
        std::string rectangleStr = "dim1 10";
        REQUIRE_THROWS_AS(rectangleCreator.createFigureFromString(rectangleStr), std::invalid_argument);
    }
}

TEST_CASE_METHOD(RectangleCreatorTestFixture, "Creating a rectangle throws when given empty representation")
{
    REQUIRE_THROWS_AS(rectangleCreator.createFigureFromString(""), std::invalid_argument);
}

//using a shorter syntax for the test cases:
TEST_CASE_METHOD(RectangleCreatorTestFixture, "Creating a rectangle throws for invalid string representations") {
    std::string invalidString = GENERATE(
        "5",        // One dimension
        "dim1",     // One non-numeric dimension
        "",         // Empty representation
        "5 10 15",  // Three dimensions
        "5 dim2",   // Mixed valid and invalid dimensions
        "dim1 10"   // Non-numeric first dimension
    );

    REQUIRE_THROWS_AS(rectangleCreator.createFigureFromString(invalidString), std::invalid_argument);
}

TEST_CASE_METHOD(RectangleCreatorTestFixture, "Creating a random rectangle should work without throwing")
{
    std::unique_ptr<Figure> rectangle;

    for (size_t i = 0; i < 10000; i++) {
        REQUIRE_NOTHROW(rectangle = rectangleCreator.createRandomFigure());
        REQUIRE(rectangle != nullptr);
    }
}

TEST_CASE_METHOD(RectangleCreatorTestFixture, "Creating a random rectangle should return a rectangle with valid dimensions")
{
    std::unique_ptr<Figure> rectangle;

    for (size_t i = 0; i < 20000; i++) 
    {
        rectangle = rectangleCreator.createRandomFigure();
        INFO(rectangle->toString());
        REQUIRE(rectangle->getPerimeter() >= 4 * RectangleConfig::minSideLength);
        REQUIRE(rectangle->getPerimeter() <= 4 * RectangleConfig::maxSideLength);
    }
}

