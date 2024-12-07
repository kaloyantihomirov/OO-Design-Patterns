#include <stdexcept>
#include <numbers>
#include <sstream>

#include "Circle.h"

Circle::Circle(double radius)
{
	if (radius <= 0)
	{
		throw std::invalid_argument("Radius must be positive.");
	}

	if (radius > std::numeric_limits<double>::max() / std::numbers::pi / 2)
	{
		throw std::overflow_error("The perimeter of the circle causes overflow.");
	}

	this->radius = radius;
	setStrRepresentation();
}

void Circle::setStrRepresentation()
{
	std::ostringstream oss;
	oss << "circle " << radius;
	strRepresentation = oss.str();
}

double Circle::getPerimeter() const
{
	return 2 * std::numbers::pi * radius;
}

std::string Circle::toString() const
{
	return strRepresentation;
}

std::unique_ptr<Figure> Circle::clone() const
{
	return std::make_unique<Circle>(*this);
}