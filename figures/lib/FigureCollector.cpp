#include <stdexcept>
#include <fstream>

#include "FigureCollector.h"

void FigureCollector::addFigure(std::unique_ptr<Figure> figure)
{
    figures.push_back(std::move(figure));
}

void FigureCollector::deleteFigure(size_t indexToDelete)
{
    if (indexToDelete >= figures.size())
    {
        throw std::invalid_argument("Invalid index.");
    }
    else
    {
        figures.erase(figures.begin() + indexToDelete);
    }
}

void FigureCollector::cloneFigure(size_t indexToClone)
{
    if (indexToClone >= figures.size())
    {
        throw std::invalid_argument("Invalid index.");
    }

    if (!figures[indexToClone])
    {
        throw std::invalid_argument("Invalid figure.");
    }

    figures.push_back(figures[indexToClone]->clone());
}

void FigureCollector::writeFiguresToStream(std::ostream& os) const
{
    for (const auto& figure : figures)
    {
        os << figure->toString() << "\n";
    }
}
