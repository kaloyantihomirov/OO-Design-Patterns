#pragma once

#include "FigureCreator.h"
#include "Triangle.h"

class TriangleCreator : public FigureCreator
{
public:
	std::unique_ptr<Figure> createFigureFromString(const std::string& representation) const override;
	std::unique_ptr<Figure> createRandomFigure() const override;
};
