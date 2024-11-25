#pragma once

#include "Figure.h"

class Triangle : public Figure
{
	double a;
	double b;
	double c;

	mutable std::string strRepresentation;
public:
	Triangle(double a, double b, double c);
	double getPerimeter() const override;
	std::string toString() const override;
	void readFromStream(std::istream&) override;
};