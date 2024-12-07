#include <sstream>
#include <stdexcept>

#include "StringToFigure.h"
#include "CircleParser.h"
#include "TriangleParser.h"

StringToFigure::StringToFigure()
{
	parsers["circle"] = std::make_unique<CircleParser>();
	parsers["triangle"] = std::make_unique<TriangleParser>();
}

void StringToFigure::registerFigure(const std::string& figureName, 
									std::unique_ptr<FigureParser> fp)
{
	if (parsers.find(figureName) != parsers.end())
	{
		throw std::invalid_argument("Figure already registered: " + figureName);
	}

	parsers[figureName] = std::move(fp);
}

std::unique_ptr<Figure> StringToFigure::createFrom(const std::string& representation)
{
	std::istringstream iss(representation);
	std::string figureType;
	iss >> figureType;

	const auto& it = parsers.find(figureType);

	if (it == parsers.end())
	{
		throw std::invalid_argument("Invalid figure type: " + figureType);	
	}

	std::string remaining;
	if (!std::getline(iss >> std::ws, remaining))
	{
		throw std::invalid_argument("Invalid figure representation: " + representation);
	}

	return it->second->createFigureFromString(remaining);
	//return it->second->createFigureFromString(representation.substr(figureType.size() + 1));
}

void StringToFigure::removeFigure(const std::string& figureName)
{
	const auto& it = parsers.find(figureName);

	if (it == parsers.end())
	{
		throw std::invalid_argument("Figure not registered: " + figureName);
	}

	parsers.erase(it);
}