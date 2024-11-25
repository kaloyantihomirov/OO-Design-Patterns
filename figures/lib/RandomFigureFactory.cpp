#include <random>

#include "RandomFigureFactory.h"

Triangle* RandomFigureFactory::createTriangle(std::istream& in) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> d(1, 1000);

	double a = d(gen);
	double b = d(gen);

	double c_min = abs(a - b) + 1;
	double c_max = a + b - 1;

	d = std::uniform_int_distribution<>(c_min, c_max);
	double c = d(gen);

	return new Triangle(a, b, c);
}

Circle* RandomFigureFactory::createCircle(std::istream& in) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> d(1, 1000);

	return new Circle(d(gen));
}

