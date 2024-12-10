#pragma once

#include "FigureFactory.h"

class AbstractFigureFactory
{
public:
	static std::unique_ptr<FigureFactory> createFigureFactory(const std::string& input);
	virtual ~AbstractFigureFactory() = default;
};
