#include "catch_amalgamated.hpp"
#include "Circle.h"
#include <numbers>

class CongruentCirclesFixture
{
public:
    Circle c1{ 5 };
    Circle c2{ 5 };
    Circle c3{ 5 };
};

TEST_CASE("Circle creates successfully")
{
    Circle c(5);
    double perimeter = c.getPerimeter();
    REQUIRE(abs(perimeter - 2 * 5 * std::numbers::pi) <= std::numeric_limits<double>::epsilon());
    REQUIRE(c.toString() == "circle 5");
}

TEST_CASE_METHOD(CongruentCirclesFixture, "Perimeter is the same for congruent circles")
{
    REQUIRE(abs(c1.getPerimeter() - c2.getPerimeter()) <= std::numeric_limits<double>::epsilon());
    REQUIRE(abs(c1.getPerimeter() - c3.getPerimeter()) <= std::numeric_limits<double>::epsilon());
}

TEST_CASE("Creating a circle with a negative radius causes an exception to be thrown")
{
    REQUIRE_THROWS_AS(Circle(-5), std::invalid_argument);
}

TEST_CASE("Creating a circle with a radius equal to zero causes an exception to be thrown")
{
    REQUIRE_THROWS_AS(Circle(0), std::invalid_argument);
}

TEST_CASE("Circle toString returns correct string representation")
{
    Circle c(5);
    REQUIRE(c.toString() == "circle 5");
}

TEST_CASE_METHOD(CongruentCirclesFixture, "Circle toString returns correct string representation for congruent circles")
{
    REQUIRE(c1.toString() == "circle 5");
    REQUIRE(c2.toString() == "circle 5");
    REQUIRE(c3.toString() == "circle 5");
}


