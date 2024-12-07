#include <iostream>

#include "ReadFromStreamFigureFactory.h"
#include "StringToFigure.h"

ReadFromStreamFigureFactory::ReadFromStreamFigureFactory(std::istream& in) : in_(in)
{
}

std::unique_ptr<Figure> ReadFromStreamFigureFactory::createFigure()
{
	std::string line;

	if (!std::getline(in_, line))
	{
		return nullptr;
		//throw std::runtime_error("Sorry, we could not read a line from the stream.");
		//and then the input becomes a hell to manage
	}
	if (line.empty())
	{
		return nullptr;
	}

	return StringToFigure::getInstance().createFrom(line);
}
