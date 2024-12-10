#pragma once

#include "Figure.h"

class Triangle : public Figure
{
	double a;
	double b;
	double c;

	void setStrRepresentation();
public:
	Triangle(double a, double b, double c);
	double getPerimeter() const override;
	std::string toString() const override;
	std::unique_ptr<Figure> clone() const override;
};