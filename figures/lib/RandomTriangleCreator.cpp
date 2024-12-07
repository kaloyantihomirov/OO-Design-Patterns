#include <random>

#include "RandomTriangleCreator.h"

std::unique_ptr<Figure> RandomTriangleCreator::createRandomFigure() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> d(1, 1000);

	int a = d(gen);
	int b = d(gen);

	int c_min = abs(a - b) + 1;
	int c_max = a + b - 1;

	d = std::uniform_int_distribution<>(c_min, c_max);
	int c = d(gen);

	return std::make_unique<Triangle>(a, b, c);
}
