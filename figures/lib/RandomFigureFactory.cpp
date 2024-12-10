#include <random>

#include "RandomFigureFactory.h"

std::unique_ptr<Figure> RandomFigureFactory::createFigure()
{
	if (creators.empty())
	{
		throw std::runtime_error("No figures registered");
	}

	const size_t from = 0;
	const size_t to = creators.size() - 1;
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int> distr(from, to);

	const auto& randomIt = std::next(std::begin(creators),
		distr(generator));

	return randomIt->second->createRandomFigure();
}


