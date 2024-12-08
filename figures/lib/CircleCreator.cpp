#include <sstream>
#include <random>

#include "CircleCreator.h"
#include "CircleConfig.h"

std::unique_ptr<Figure> CircleCreator::createFigureFromString(const std::string& representation) const
{
	std::istringstream iss(representation);
	double radius;

	if (!(iss >> radius) || !(iss >> std::ws).eof())
	{
		throw std::invalid_argument("Invalid circle representation: circle " + representation);
	}

	return std::make_unique<Circle>(radius);
}

std::unique_ptr<Figure> CircleCreator::createRandomFigure() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> d(CircleConfig::minRadiusRandom, CircleConfig::maxRadiusRandom);
	return std::make_unique<Circle>(d(gen));
}