#pragma once

#include "Circle.h"
#include "RandomFigureCreator.h"

class RandomCircleCreator : public RandomFigureCreator
{
public:
	std::unique_ptr<Figure> createRandomFigure() const override;
};