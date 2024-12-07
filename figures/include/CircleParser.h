#pragma once

#include "Circle.h"
#include "FigureParser.h"

class CircleParser : public FigureParser
{
public:
	std::unique_ptr<Figure> createFigureFromString(const std::string& representation) const override;
};	