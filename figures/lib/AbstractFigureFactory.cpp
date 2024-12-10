#include <iostream>
#include <fstream>
#include <stdexcept>

#include "AbstractFigureFactory.h"
#include "ReadFromStreamFigureFactory.h"
#include "RandomFigureFactory.h"

std::unique_ptr<FigureFactory> AbstractFigureFactory::createFigureFactory(const std::string& input)
{
	if (input == "random")
	{
		return std::make_unique<RandomFigureFactory>();
	}
	else if (input == "file")
	{
		std::string fileName;
		std::cout << "Please enter the file name: ";
		std::cin >> fileName;

		std::ifstream is(fileName);
		if (!is.is_open())
		{
			throw std::invalid_argument("Could not open file.");
		}

		return std::make_unique<ReadFromStreamFigureFactory>(is);
	}
	else if (input == "console")
	{
		std::cout << "Please, press enter two times to stop reading figures from the console!\n";
		std::cin.ignore();
		return std::make_unique<ReadFromStreamFigureFactory>(std::cin);
	}
	else
	{
		throw std::invalid_argument("Invalid factory type.");
	}
}
