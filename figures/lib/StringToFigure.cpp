#include <sstream>
#include <stdexcept>

#include "StringToFigure.h"
#include "Triangle.h"
#include "Circle.h"

Figure* StringToFigure::createFrom(const std::string& representation)
{
	std::istringstream iss(representation);
	std::string figureType;
	iss >> figureType;
	Figure* figure = nullptr;

	if (figureType == "circle")
	{
		double radius;

		if (!(iss >> radius) || !(iss >> std::ws).eof())
		{
			throw std::invalid_argument("Invalid circle representation: " + representation);
		}

		figure = new Circle(radius);
	}
	else if (figureType == "triangle")
	{
		int a;
		int b;
		int c;

		if (!(iss >> a >> b >> c) || !(iss >> std::ws).eof())
		{
			throw std::invalid_argument("Invalid triangle representation: " + representation);
		}

		figure = new Triangle(a, b, c);
	}
	else
	{
		throw std::invalid_argument("Invalid figure type: " + figureType);
	}

	return figure;
}
