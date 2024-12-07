#include <random>

#include "RandomFigureFactory.h"
#include "RandomCircleCreator.h"
#include "RandomTriangleCreator.h"

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

	const auto& random_it = std::next(std::begin(creators),
		distr(generator));

	return random_it->second->createRandomFigure();
}

RandomFigureFactory::RandomFigureFactory()
{
	creators["circle"] = std::make_unique<RandomCircleCreator>();
	creators["triangle"] = std::make_unique<RandomTriangleCreator>();
}

void RandomFigureFactory::registerFigure(const std::string& figureName, std::unique_ptr<RandomFigureCreator> fp)
{
	if (creators.find(figureName) != creators.end())
	{
		throw std::invalid_argument("Figure already registered: " + figureName);
	}

	creators[figureName] = std::move(fp);
}


void RandomFigureFactory::removeFigure(const std::string& figureName)
{
	const auto& it = creators.find(figureName);

	if (it == creators.end())
	{
		throw std::invalid_argument("Figure not registered: " + figureName);
	}

	creators.erase(it);
}

