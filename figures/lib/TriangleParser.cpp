#include <sstream>
#include <random>

#include "TriangleParser.h"

std::unique_ptr<Figure> TriangleParser::createFigureFromString(const std::string& representation) const
{
	std::istringstream iss(representation);

	int a;
	int b;
	int c;

	if (!(iss >> a >> b >> c) || !(iss >> std::ws).eof())
	{
		throw std::invalid_argument("Invalid triangle representation: triangle " + representation);
	}

	return std::make_unique<Triangle>(a, b, c);
}
