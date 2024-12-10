#pragma once

#include <vector>
#include <memory>

#include "Figure.h"

class FigureCollector
{
    std::vector<std::unique_ptr<Figure>> figures;
public:
    void addFigure(std::unique_ptr<Figure> figure);
    void deleteFigure(size_t indexToDelete);
    void cloneFigure(size_t indexToClone);
    void writeFiguresToStream(std::ostream& os) const;
};
