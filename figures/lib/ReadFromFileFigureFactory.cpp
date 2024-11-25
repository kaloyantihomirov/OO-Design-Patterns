#include <iostream>

#include "ReadFromFileFigureFactory.h"

Circle* ReadFromFileFigureFactory::createCircle(std::istream& in) const
{
	Circle* circle = new Circle(1);
	circle->readFromStream(in);
	return circle;
}

Triangle* ReadFromFileFigureFactory::createTriangle(std::istream& in) const
{
	Triangle* triangle = new Triangle(1, 5, 5);
	triangle->readFromStream(in);
	return triangle;
}
