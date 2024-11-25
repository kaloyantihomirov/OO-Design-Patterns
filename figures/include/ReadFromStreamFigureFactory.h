#pragma once

#include "FigureFactory.h"

class ReadFromStreamFigureFactory : public FigureFactory
{
	std::istream& in_;
public:
	explicit ReadFromStreamFigureFactory(std::istream& in);

	ReadFromStreamFigureFactory(const ReadFromStreamFigureFactory&) = delete;
	ReadFromStreamFigureFactory& operator=(const ReadFromStreamFigureFactory&) = delete;

	Figure* createFigure() override;
};
