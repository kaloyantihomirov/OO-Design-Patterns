#include <numbers>

#include "catch_amalgamated.hpp"

#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"

TEST_CASE("Cloning a circle works correctly")
{
    std::unique_ptr<Figure> circle = std::make_unique<Circle>(5);
    std::unique_ptr<Figure> cloned = circle->clone();
    REQUIRE(cloned->toString() == "circle 5");
    REQUIRE(cloned->getPerimeter() == circle->getPerimeter());
}

TEST_CASE("Cloning a triangle works correctly")
{
    std::unique_ptr<Figure> triangle = std::make_unique<Triangle>(3, 4, 5);
    std::unique_ptr<Figure> cloned = triangle->clone();
    REQUIRE(cloned->toString() == "triangle 3 4 5");
    REQUIRE(cloned->getPerimeter() == triangle->getPerimeter());
}

TEST_CASE("Cloning a rectangle works correctly")
{
    std::unique_ptr<Figure> rectangle = std::make_unique<Rectangle>(5, 10);
    std::unique_ptr<Figure> cloned = rectangle->clone();
    REQUIRE(cloned->toString() == "rectangle 5 10");
    REQUIRE(cloned->getPerimeter() == rectangle->getPerimeter());
}

TEST_CASE("Cloning a circle produces a deep copy")
{
    std::unique_ptr<Figure> circle = std::make_unique<Circle>(5);
    std::unique_ptr<Figure> cloned = circle->clone();
    circle.reset();
    REQUIRE(cloned->toString() == "circle 5");
    REQUIRE(cloned.get() != circle.get());
}

TEST_CASE("Cloning a triangle produces a deep copy")
{
    std::unique_ptr<Figure> triangle = std::make_unique<Triangle>(3, 4, 5);
    std::unique_ptr<Figure> cloned = triangle->clone();
    triangle.reset();
    REQUIRE(cloned->toString() == "triangle 3 4 5");
    REQUIRE(cloned.get() != triangle.get());
}

TEST_CASE("Cloning a rectangle produces a deep copy")
{
	std::unique_ptr<Figure> rectangle = std::make_unique<Rectangle>(5, 10);
	std::unique_ptr<Figure> cloned = rectangle->clone();
	rectangle.reset();
	REQUIRE(cloned->toString() == "rectangle 5 10");
	REQUIRE(cloned.get() != rectangle.get());
}