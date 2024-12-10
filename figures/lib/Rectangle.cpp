#include <stdexcept>
#include <sstream>

#include "Rectangle.h"

void Rectangle::setStrRepresentation()
{
    std::ostringstream oss;
    oss << "rectangle " << width << " " << height;
    strRepresentation = oss.str();
}

Rectangle::Rectangle(double width, double height)
{
    if (width <= 0 || height <= 0) 
    {
        throw std::invalid_argument("Width and height of the rectangle must be positive.");
    }

    if (width >= std::numeric_limits<double>::max() / 2 || height >= std::numeric_limits<double>::max() / 2) 
    {
        throw std::overflow_error("The perimeter of the rectangle causes overflow.");
    }

    if (width + height > std::numeric_limits<double>::max() / 2) 
    {
        throw std::overflow_error("The perimeter of the rectangle causes overflow.");
    }

    this->width = width;
    this->height = height;

    setStrRepresentation();
}

double Rectangle::getPerimeter() const
{
    return 2 * (width + height);
}

std::string Rectangle::toString() const
{
    return strRepresentation;
}

std::unique_ptr<Figure> Rectangle::clone() const
{
    return std::make_unique<Rectangle>(*this);
}
