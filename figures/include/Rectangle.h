#pragma once

#include <memory>
#include <string>

#include "Figure.h"

class Rectangle : public Figure
{
    int width;
    int height;
    void setStrRepresentation();

public:
    Rectangle(int width, int height);
    double getPerimeter() const override;
    std::string toString() const override;
    std::unique_ptr<Figure> clone() const override;
};

