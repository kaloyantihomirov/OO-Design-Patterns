#pragma once

#include <memory>
#include <unordered_map>

#include "Figure.h"
#include "FigureCreator.h"

class FigureFactory
{
protected:
	std::unordered_map<std::string, std::unique_ptr<FigureCreator>> creators;
	FigureFactory();
public:
	virtual std::unique_ptr<Figure> createFigure() = 0;
	void registerFigure(const std::string& figureName, std::unique_ptr<FigureCreator> fp);
	void deleteFigure(const std::string& figureName);
	//std::unordered_map<std::string, std::unique_ptr<FigureCreator>>::const_iterator getCreator(const std::string& figureName) const;
	void clearCreators();
	virtual ~FigureFactory() = default;
};
