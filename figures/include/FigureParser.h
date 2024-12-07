#pragma once

#include <string>
#include <memory>

#include "Figure.h"

class FigureParser
{
public:
	virtual std::unique_ptr<Figure> createFigureFromString(const std::string& representation) const = 0;
	virtual ~FigureParser() = default;
};
	