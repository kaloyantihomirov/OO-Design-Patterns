#include <numbers>

#include "catch_amalgamated.hpp"
#include "Circle.h"
#include "Triangle.h"

TEST_CASE("Cloning a circle works correctly")
{
	Figure* circle = new Circle(5);
	Figure* cloned = circle->clone();
	REQUIRE(cloned->toString() == "circle 5");
	delete circle;
	delete cloned;
}

TEST_CASE("Cloning a triangle works correctly")
{
	Figure* triangle = new Triangle(3, 4, 5);
	Figure* cloned = triangle->clone();
	REQUIRE(cloned->toString() == "triangle 3 4 5");
	delete triangle;
	delete cloned;
}

TEST_CASE("Cloning a circle produces a deep copy")
{
	Figure* circle = new Circle(5);
	Figure* cloned = circle->clone();
	delete circle;
	REQUIRE(cloned->toString() == "circle 5");
	delete cloned;
}

TEST_CASE("Cloning a triangle produces a deep copy")
{
	Figure* triangle = new Triangle(3, 4, 5);
	Figure* cloned = triangle->clone();
	delete triangle;
	REQUIRE(cloned->toString() == "triangle 3 4 5");
	delete cloned;
}