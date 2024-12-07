#include <sstream>
#include <random>

#include "CircleParser.h"

std::unique_ptr<Figure> CircleParser::createFigureFromString(const std::string& representation) const
{
	std::istringstream iss(representation);
	double radius;

	if (!(iss >> radius) || !(iss >> std::ws).eof())
	{
		throw std::invalid_argument("Invalid circle representation: circle " + representation);
	}

	return std::make_unique<Circle>(radius);
}
