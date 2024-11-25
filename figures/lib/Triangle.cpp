#include <iostream>
#include <stdexcept>
#include <sstream>

#include "Triangle.h"
#include "DoubleNumsHelper.h"

void Triangle::setStrRepresentation()
{
	std::ostringstream oss;
	oss << "triangle " << a << " " << b << " " << c;
	strRepresentation = oss.str();
}

Triangle::Triangle(double a, double b, double c) 
{
	if (a <= 0 || b <= 0 || c <= 0)
	{
		throw std::invalid_argument("All sides of the triangle must be positive.");
	}

	if (DoubleNumsHelper::willAdditionOverflow(a, b) || DoubleNumsHelper::willAdditionOverflow(a + b, c))
	{
		throw std::overflow_error("The sum of the sides of the triangle causes overflow.");
	}

	if (a + b <= c || a + c <= b || b + c <= a)
	{
		throw std::invalid_argument("Invalid triangle sides");
	}

	this->a = a;
	this->b = b;
	this->c = c;
	setStrRepresentation();
}

double Triangle::getPerimeter() const
{
	return a + b + c;
}

std::string Triangle::toString() const
{
	return strRepresentation;
}

Triangle* Triangle::clone() const
{
	return new Triangle(*this);
}