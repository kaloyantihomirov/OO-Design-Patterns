#pragma once

#include "FigureFactory.h"
#include "Triangle.h"
#include "Circle.h"

class RandomFigureFactory : public FigureFactory
{
protected:
	Triangle* createTriangle(std::istream& in) const ;
	Circle* createCircle(std::istream& in) const ;
};
