#include <stdexcept>

#include "FigureFactory.h"
#include "CircleCreator.h"
#include "TriangleCreator.h"

FigureFactory::FigureFactory()
{
	creators["triangle"] = std::make_unique<TriangleCreator>();
	creators["circle"] = std::make_unique<CircleCreator>();
}

void FigureFactory::registerFigure(const std::string& figureName,	
	                               std::unique_ptr<FigureCreator> fp)
{
	if (creators.find(figureName) != creators.end())
	{
		throw std::invalid_argument("Figure already registered: " + figureName);
	}

	creators[figureName] = std::move(fp);
}

void FigureFactory::deleteFigure(const std::string& figureName)
{
	const auto& it = creators.find(figureName);

	if (it == creators.end())
	{
		throw std::invalid_argument(
			"Figure not registered: " + figureName);
	}

	creators.erase(it);
}

void FigureFactory::clearCreators()
{
	creators.clear();
}

