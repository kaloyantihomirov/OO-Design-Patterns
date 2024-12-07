#pragma once

#include "Triangle.h"
#include "RandomFigureCreator.h"

class RandomTriangleCreator : public RandomFigureCreator
{
public:
	std::unique_ptr<Figure> createRandomFigure() const override;
};