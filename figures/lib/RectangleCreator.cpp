#include <sstream>
#include <random>
#include <stdexcept>

#include "RectangleCreator.h"
#include "Rectangle.h"
#include "RectangleConfig.h"

std::unique_ptr<Figure> RectangleCreator::createFigureFromString(const std::string& representation) const
{
	std::istringstream iss(representation);

	double width;
	double height;

	if (!(iss >> width >> height) || !(iss >> std::ws).eof())
	{
		throw std::invalid_argument("Invalid rectangle representation: rectangle " + representation);
	}

	return std::make_unique<Rectangle>(width, height);
}

std::unique_ptr<Figure> RectangleCreator::createRandomFigure() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> d(RectangleConfig::minSideLength, RectangleConfig::maxSideLength);

	int width = d(gen);
	int height = d(gen);

	return std::make_unique<Rectangle>(width, height);
}