#pragma once

#include <string>
#include <memory>

#include "Figure.h"

class FigureCreator
{
public:
	virtual std::unique_ptr<Figure> createFigureFromString(const std::string& representation) const = 0;
	virtual std::unique_ptr<Figure> createRandomFigure() const = 0;
	virtual ~FigureCreator() = default;
};
	