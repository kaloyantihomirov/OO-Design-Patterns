#include <random>

#include "RandomCircleCreator.h"

std::unique_ptr<Figure> RandomCircleCreator::createRandomFigure() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> d(1, 1000);
	return std::make_unique<Circle>(d(gen));
}
