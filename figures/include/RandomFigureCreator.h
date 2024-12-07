#pragma once

#include "Figure.h"

class RandomFigureCreator
{
public:
	virtual std::unique_ptr<Figure> createRandomFigure() const = 0;
	virtual ~RandomFigureCreator() = default;
};

