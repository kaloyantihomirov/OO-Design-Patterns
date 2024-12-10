#include <sstream>

#include "ReadFromStreamFigureFactory.h"


//ReadFromStreamFigureFactory::ReadFromStreamFigureFactory(std::istream& in) : in_(in)
//{
//}

ReadFromStreamFigureFactory::ReadFromStreamFigureFactory(std::shared_ptr<std::istream> in) : in_(std::move(in))
{
}

std::unique_ptr<Figure> ReadFromStreamFigureFactory::createFigure()
{
	std::string line;

	if (!std::getline(*in_, line))
	{
		return nullptr;
		//throw std::runtime_error("Sorry, we could not read a line from the stream.");
		//and then the input becomes a hell to manage
	}
	if (line.empty())
	{
		return nullptr;
	}

	std::istringstream iss(line);
	std::string figureType;
	iss >> figureType;

	const auto& it = creators.find(figureType);

	if (it == creators.end())
	{
		throw std::invalid_argument("Invalid figure type: " + figureType);
	}

	std::string remaining;
	if (!std::getline(iss >> std::ws, remaining))
	{
		throw std::invalid_argument("Invalid figure representation: " + line);
	}

	return it->second->createFigureFromString(remaining);
}
