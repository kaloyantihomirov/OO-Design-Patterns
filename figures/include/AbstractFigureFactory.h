#pragma once

#include "FigureFactory.h"

class AbstractFigureFactory
{
public:
	virtual std::unique_ptr<FigureFactory> createFigureFactory(const std::string& input) const = 0;
	virtual ~AbstractFigureFactory() = default;
}
