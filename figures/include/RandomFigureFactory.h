#pragma once

#include <unordered_map>

#include "FigureFactory.h"
#include "RandomFigureCreator.h"

class RandomFigureFactory : public FigureFactory
{
	std::unordered_map<std::string, std::unique_ptr<RandomFigureCreator>> creators;
public:
	RandomFigureFactory();

	std::unique_ptr<Figure> createFigure() override;

	void registerFigure(const std::string& figureName, std::unique_ptr<RandomFigureCreator> rfc);
	void removeFigure(const std::string& figureName);
};
