#pragma once

#include "Circle.h"
#include "FigureCreator.h"

class CircleCreator : public FigureCreator
{
public:
	std::unique_ptr<Figure> createFigureFromString(const std::string& representation) const override;
	std::unique_ptr<Figure> createRandomFigure() const override;
};	