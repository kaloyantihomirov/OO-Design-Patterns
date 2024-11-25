#pragma once

#include "FigureFactory.h"
#include "Triangle.h"
#include "Circle.h"

class RandomFigureFactory : public FigureFactory
{
public:
	Triangle* createTriangle(std::istream& in) const override;
	Circle* createCircle(std::istream& in) const override;
};
