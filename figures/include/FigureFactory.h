#pragma once

#include "Figure.h"

class FigureFactory
{
public:
	virtual Figure* createFigure() = 0;
	virtual ~FigureFactory() = default;
};
