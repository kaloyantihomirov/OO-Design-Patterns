#include <iostream>
#include <fstream>

#include "RandomFigureFactory.h"
#include "ReadFromFileFigureFactory.h"

int main()
{
	std::cout << "Please choose factory type: [0 for random, 1 for importing figures from file]: ";
	int choice;
	std::cin >> choice;

	FigureFactory* factory = nullptr;

	if (choice == 0)
	{
		factory = new RandomFigureFactory();

		std::cout << R"(Please choose figure type: ["circle" for circle, "triangle" for triangle]: )";
		Figure* f = factory->createFigure(std::cin);
		while (f)
		{
			f = factory->createFigure(std::cin);
		}

	}
	else if (choice == 1)
	{
		factory = new ReadFromFileFigureFactory();
		std::cout << "Enter file name: ";
		std::string fileName;
		std::cin >> fileName;
		std::ifstream in(fileName);

		while (in)
		{
			Figure* figure = factory->createFigure(in);
		}
	}
	else
	{
		std::cout << "Invalid factory type.\n";
	}

	return 0;
}
