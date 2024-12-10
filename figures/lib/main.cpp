#include <iostream>
#include <fstream>

#include "AbstractFigureFactory.h"
#include "CommandHandler.h"
#include "FigureCollector.h"
#include "FigureFactory.h"

int main()
{
    std::cout << "Please choose factory type [random, file, console]: ";
    std::string factoryType;
    std::cin >> factoryType;

    std::unique_ptr<FigureFactory> factory;

    try
    {
		factory = AbstractFigureFactory::createFigureFactory(factoryType);
    }
    catch (const std::invalid_argument& e)
    {
		std::cout << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e)
    {
		std::cout << "Something went wrong, we're sorry!" << "\n";
		std::cout << e.what() << "\n";
		return 1;
    }
    catch (...)
    {
        std::cout << "Something went wrong!\n";
    }

    //factory holds a valid factory object

    FigureCollector figureCollector;
    if (factoryType == "random") 
    {
		size_t figuresCount;
		std::cout << "Please enter the number of random figures to generate: ";
		std::cin >> figuresCount;
        for (size_t i = 0; i < figuresCount; i++)
        {
            figureCollector.addFigure(factory->createFigure());
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
                figureCollector.addFigure(std::move(figure));
            }
            catch (const std::exception& e) //could be overflow as well!
            {
                std::cout << e.what() << "\n";
            }
            catch (...)
            {
                std::cout << "Something went wrong!\n";
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
            CommandHandler::handleDeleteCommand(figureCollector, indexToDelete);
        }
        else if (command == "clone") 
        {
            size_t indexToClone;
            std::cin >> indexToClone;
			CommandHandler::handleCloneCommand(figureCollector, indexToClone);
        }
        else if (command == "serialise") 
        {
			CommandHandler::handleSerialiseCommand(figureCollector);
        }
        else if (command == "print") 
        {
			CommandHandler::handlePrintCommand(figureCollector);
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