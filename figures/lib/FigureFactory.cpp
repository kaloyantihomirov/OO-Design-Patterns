#include <iostream>

#include "FigureFactory.h"

Figure* FigureFactory::createFigure(std::istream& in) const
{
	std::string figureType;
	in >> figureType;

	Figure* figure = nullptr;
	if (figureType == "circle")
	{
		figure = createCircle(in);
	}
	else if (figureType == "triangle")
	{
		figure = createTriangle(in);
	}

	return figure;
}
