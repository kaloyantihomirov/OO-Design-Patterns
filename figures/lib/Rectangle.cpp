#include <stdexcept>
#include <sstream>

#include "Rectangle.h"

void Rectangle::setStrRepresentation()
{
    std::ostringstream oss;
    oss << "rectangle " << width << " " << height;
    strRepresentation = oss.str();
}

Rectangle::Rectangle(int width, int height)
{
    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("Width and height of the rectangle must be positive.");
    }

    if (width > std::numeric_limits<int>::max() - height)
    {
        throw std::overflow_error("The sum of width and height causes overflow.");
    }

    if (width > (std::numeric_limits<int>::max() / 2 - height))
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
