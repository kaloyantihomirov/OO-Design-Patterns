#include <iostream>
#include <fstream>

#include "FigureFactory.h"
#include "RandomFigureFactory.h"
#include "ReadFromStreamFigureFactory.h"

void writeFiguresToStream(const std::vector<std::unique_ptr<Figure>>& figures, std::ostream& os)
{
    for (const auto& figure : figures)
    {
        os << figure->toString() << "\n";
    }
}

void deleteFigure(std::vector<std::unique_ptr<Figure>>& figures, size_t indexToDelete)
{
    if (indexToDelete >= figures.size())
    {
        std::cout << "Invalid index.\n";
    }
    else
    {
        figures.erase(figures.begin() + indexToDelete);
    }
}

void cloneFigure(std::vector<std::unique_ptr<Figure>>& figures, size_t indexToClone)
{
    if (indexToClone >= figures.size())
    {
        std::cout << "Invalid index.\n";
    }
    else
    {
        if (!figures[indexToClone])
        {
            std::cout << "Invalid figure.\n";
        }
        else
        {
            figures.push_back(figures[indexToClone]->clone());
        }
    }
}

int main2()
{
    std::cout << "Please choose factory type [random, file, console]: ";
    std::string inputType;
    std::cin >> inputType;

    std::unique_ptr<FigureFactory> factory;

    if (inputType == "random") 
    {
        factory = std::make_unique<RandomFigureFactory>();
    }
    else if (inputType == "file") 
    {
        std::string fileName;
        std::cout << "Please enter the file name: ";
        std::cin >> fileName;

        std::ifstream is(fileName);
        if (!is.is_open()) 
        {
            std::cerr << "Could not open file.\n";
            return 1;
        }

        factory = std::make_unique<ReadFromStreamFigureFactory>(is);
    }
    else if (inputType == "console") 
    {
        factory = std::make_unique<ReadFromStreamFigureFactory>(std::cin);
        std::cout << "Please, press enter two times to stop reading figures from the console!\n";
        std::cin.ignore();
    }
    else 
    {
        std::cerr << "Invalid factory type.\n";
        return 1;
    }

    std::vector<std::unique_ptr<Figure>> figures;
    if (inputType == "random") 
    {
        size_t figuresCount;
        std::cout << "Please enter the number of random figures to generate: ";
        std::cin >> figuresCount;

        for (size_t i = 0; i < figuresCount; i++) 
        {
            figures.push_back(factory->createFigure());
        }
    }
    else 
    {
        while (true) 
        {
            try 
            {
                std::unique_ptr<Figure> figure = factory->createFigure();
                if (!figure) 
                {
                    break;
                }
                figures.push_back(std::move(figure));
            }
            catch (const std::exception& e) 
            {
                std::cout << e.what() << "\n";
            }
        }
    }

    std::string command;
    std::cout << "Please, enter a command [delete, clone, serialise (to file), print (to console), end]: ";
    std::cin >> command;
    while (command != "end") 
    {
        if (command == "delete") 
        {
            size_t indexToDelete;
            std::cin >> indexToDelete;
            deleteFigure(figures, indexToDelete);
        }
        else if (command == "clone") 
        {
            size_t indexToClone;
            std::cin >> indexToClone;
            cloneFigure(figures, indexToClone);
        }
        else if (command == "serialise") 
        {
            std::string fileName;
            std::cout << "Please, enter a name for the file with the serialised figures: ";
            std::cin >> fileName;
            std::ofstream os(fileName);
            if (!os.is_open()) 
            {
                std::cout << "Could not open file.\n";
            }
            else 
            {
                writeFiguresToStream(figures, os);
            }
        }
        else if (command == "print") 
        {
            writeFiguresToStream(figures, std::cout);
        }
        else 
        {
            std::cout << "Invalid command.\n";
        }

        std::cout << "Please, enter a command [delete, clone, serialise (to file), print (to console), end]: ";
        std::cin >> command;
    }

    return 0;
}

int main3()
{
    std::unique_ptr<FigureFactory> factory = std::make_unique<RandomFigureFactory>();

    try
    {
        factory->deleteFigure("circle");
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << "\n";
    }

    std::vector<std::unique_ptr<Figure>> v;

    for (size_t i = 0; i < 10000; i++)
    {
        v.push_back(factory->createFigure());
    }

    for (size_t i = 0; i < 1000; i++)
    {
        std::cout << v[i]->toString() << "\n";
    }

    return 0;
}
