#pragma once

#include <unordered_map>
#include <string>

#include "Figure.h"
#include "FigureParser.h"

class StringToFigure
{
	std::unordered_map<std::string, std::unique_ptr<FigureParser>> parsers;
public:
	//I imagined that the initialisation of objects of type StringToFigure could become expensive
	//if we have too many figures for example, which with their own figure parser.
	static StringToFigure& getInstance()
	{
		static StringToFigure instance; //"magic" statics -> thread-safe from C++11
		return instance;
	}

	StringToFigure();

	void registerFigure(const std::string& figureName, std::unique_ptr<FigureParser> fp);
	void removeFigure(const std::string& figureName);

	std::unique_ptr<Figure> createFrom(const std::string& representation);
};
