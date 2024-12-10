#pragma once

#include "FigureCreator.h"

class RectangleCreator : public FigureCreator
{
public:
	std::unique_ptr<Figure> createFigureFromString(const std::string& representation) const override;
	std::unique_ptr<Figure> createRandomFigure() const override;
};