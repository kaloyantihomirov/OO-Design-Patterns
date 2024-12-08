#include <sstream>
#include <random>

#include "TriangleCreator.h"
#include "TriangleConfig.h"

std::unique_ptr<Figure> TriangleCreator::createFigureFromString(const std::string& representation) const
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

std::unique_ptr<Figure> TriangleCreator::createRandomFigure() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> d(TriangleConfig::minSideLengthRandom, TriangleConfig::maxSideLengthRandom);

	int a = d(gen);
	int b = d(gen);

	int c_min = abs(a - b) + 1;
	int c_max = a + b - 1;

	d = std::uniform_int_distribution<>(c_min, c_max);
	int c = d(gen);

	return std::make_unique<Triangle>(a, b, c);
}