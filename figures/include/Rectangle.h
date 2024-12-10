#pragma once

#include <memory>
#include <string>

#include "Figure.h"

class Rectangle : public Figure
{
    double width;
    double height;
    void setStrRepresentation();

public:
    Rectangle(double width, double height);
    double getPerimeter() const override;
    std::string toString() const override;
    std::unique_ptr<Figure> clone() const override;
};

