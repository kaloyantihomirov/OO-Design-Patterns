#pragma once

#include <string>

#include "Figure.h"

class StringToFigure
{
public:
	static Figure* createFrom(const std::string& representation);
};
