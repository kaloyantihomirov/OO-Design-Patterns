#pragma once

#include <memory>

#include "Figure.h"

class FigureFactory
{
public:
	virtual std::unique_ptr<Figure> createFigure() = 0;
	virtual ~FigureFactory() = default;
};
