#pragma once

#include "Figure.h"

class Circle : public Figure
{
private:
	double radius;
	std::string strRepresentation;

	void setStrRepresentation();
public:
	explicit Circle(double radius);
	double getPerimeter() const override;
	std::string toString() const override;
	void readFromStream(std::istream&) override;
};