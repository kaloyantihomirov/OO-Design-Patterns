#pragma once

#include "Figure.h"

class Triangle : public Figure
{
	int a;
	int b;
	int c;

	void setStrRepresentation();
public:
	Triangle(int a, int b, int c);
	double getPerimeter() const override;
	std::string toString() const override;
	std::unique_ptr<Figure> clone() const override;
};