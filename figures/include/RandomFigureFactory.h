#pragma once

#include "FigureFactory.h"

class RandomFigureFactory : public FigureFactory
{
public:
	std::unique_ptr<Figure> createFigure() override;
};
