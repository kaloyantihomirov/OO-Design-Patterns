#include <iostream>

#include "ReadFromStreamFigureFactory.h"
#include "StringToFigure.h"

ReadFromStreamFigureFactory::ReadFromStreamFigureFactory(std::istream& in) : in_(in)
{
}

Figure* ReadFromStreamFigureFactory::createFigure()
{
	std::string line;
	if (!std::getline(in_, line))
	{
		throw std::runtime_error("Could not read from stream.");
	}

	return StringToFigure::createFrom(line);
}
