#pragma once

#include "Figure.h"

class Circle : public Figure
{
	double radius;

	void setStrRepresentation();
public:
	explicit Circle(double radius);
	double getPerimeter() const override;
	std::string toString() const override;
	std::unique_ptr<Figure> clone() const override;
};