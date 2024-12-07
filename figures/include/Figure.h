#pragma once

#include <string>
#include <memory>

class Figure
{
protected:
	std::string strRepresentation;
public:
	virtual double getPerimeter() const = 0;
	virtual ~Figure() = default;
	virtual std::string toString() const = 0;
	virtual std::unique_ptr<Figure> clone() const = 0;
};
