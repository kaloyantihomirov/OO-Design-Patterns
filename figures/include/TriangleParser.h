#pragma once

#include "FigureParser.h"
#include "Triangle.h"

class TriangleParser : public FigureParser
{
public:
	std::unique_ptr<Figure> createFigureFromString(const std::string& representation) const override;
};
