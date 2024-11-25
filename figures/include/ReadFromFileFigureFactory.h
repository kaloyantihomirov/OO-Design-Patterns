#pragma once

#include "Circle.h"
#include "FigureFactory.h"
#include "Triangle.h"

class ReadFromFileFigureFactory : public FigureFactory
{
public:
	Triangle* createTriangle(std::istream& in) const override;
	Circle* createCircle(std::istream& in) const override;
};
