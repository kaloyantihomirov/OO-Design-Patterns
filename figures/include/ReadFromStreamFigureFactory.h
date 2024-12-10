#pragma once

#include "FigureFactory.h"
#include <fstream>

class ReadFromStreamFigureFactory : public FigureFactory
{
	std::shared_ptr<std::istream> in_;
public:
	//explicit ReadFromStreamFigureFactory(std::istream& in);
	explicit ReadFromStreamFigureFactory(std::shared_ptr<std::istream> in);

	ReadFromStreamFigureFactory(const ReadFromStreamFigureFactory&) = delete;
	ReadFromStreamFigureFactory& operator=(const ReadFromStreamFigureFactory&) = delete;

	std::unique_ptr<Figure> createFigure() override;
};
