#pragma once

#include <string>

class Figure
{
public:
	virtual double getPerimeter() const = 0;
	virtual ~Figure() = default;
	virtual std::string toString() const = 0;
	virtual Figure* clone() const = 0;
};
