#include <iostream>
#include <stdexcept>
#include <fstream>

#include "CommandHandler.h"

void CommandHandler::handleDeleteCommand(FigureCollector& figureCollector, size_t indexToDelete)
{
    try
    {
        figureCollector.deleteFigure(indexToDelete);
    }
    catch (const std::invalid_argument& e)
	{
        std::cout << e.what() << "\n";
	}
    catch (const std::exception& e)
    {
        std::cout << "Something went wrong!\n";
        std::cout << e.what() << "\n";
    }
}

void CommandHandler::handleCloneCommand(FigureCollector& figureCollector, size_t indexToClone)
{
	try
	{
		figureCollector.cloneFigure(indexToClone);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << "Something went wrong!\n";
		std::cout << e.what() << "\n";
	}
}

void CommandHandler::handleSerialiseCommand(const FigureCollector& figureCollector)
{
	std::string fileName;
	std::cout << "Please enter the file name: ";
	std::cin >> fileName;
	std::ofstream os(fileName);
	if (!os.is_open())
	{
		std::cout << "Could not open file.\n";
		return;
	}
	figureCollector.writeFiguresToStream(os);
}

void CommandHandler::handlePrintCommand(const FigureCollector& figureCollector)
{
	figureCollector.writeFiguresToStream(std::cout);
}
