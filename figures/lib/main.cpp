#include <iostream>
#include <fstream>
#include <vector>

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

int main()
{
	std::cout << "Please choose factory type: [0 for random, 1 for importing figures from file, 2 for reading figures from std::cin]: ";
	int choice;
	std::cin >> choice;

	std::unique_ptr<FigureFactory> factory;
	std::vector<std::unique_ptr<Figure>> figures;

	if (choice == 0)
	{
		size_t figuresCount;
		std::cout << "Please enter the number of random figures to generate: ";
		std::cin >> figuresCount;

		factory = std::make_unique<RandomFigureFactory>();

		for (size_t i = 0; i < figuresCount; i++)
		{
			figures.push_back(factory->createFigure());
		}
	}
	else if (choice == 1)
	{
		std::string fileName;
		std::cout << "Please enter file name: ";
		std::cin >> fileName;
		std::ifstream is(fileName);
		if (!is.is_open())
		{
			std::cout << "Could not open file.\n";
			return 1;
		}

		factory = std::make_unique<ReadFromStreamFigureFactory>(is);

		while (is)
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
	else if (choice == 2)
	{
		std::cout << "Please, press enter two times to stop reading figures from the console!\n";

		factory = std::make_unique<ReadFromStreamFigureFactory>(std::cin);
		std::cin.ignore();

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
	else
	{
		std::cout << "Invalid factory type.\n";
	}

	std::string command;
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

		std::cin >> command;
	}

	return 0;
}
