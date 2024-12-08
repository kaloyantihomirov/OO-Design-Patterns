#pragma once

#include "FigureFactory.h"
#include "RandomFigureCreator.h"

class RandomFigureFactory : public FigureFactory
{
public:
	std::unique_ptr<Figure> createFigure() override;
};
