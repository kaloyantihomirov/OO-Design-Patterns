#pragma once

#include "Circle.h"
#include "Triangle.h"

class FigureFactory
{
public:
	Figure* createFigure(std::istream&) const;
	virtual Triangle* createTriangle(std::istream&) const = 0;
	virtual Circle* createCircle(std::istream&) const = 0;
	virtual ~FigureFactory() = default;
};
