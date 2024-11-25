#include <iostream>
#include <fstream>
#include <vector>

#include "RandomFigureFactory.h"
#include "ReadFromFileFigureFactory.h"

int main2()
{
	std::cout << "Please choose factory type: [0 for random, 1 for importing figures from file]: ";
	int choice;
	std::cin >> choice;

	FigureFactory* factory = nullptr;
	std::vector<Figure*> figures;

	if (choice == 0)
	{
		factory = new RandomFigureFactory();

		std::cout << R"(Please choose figure type: ["circle" for circle, "triangle" for triangle]: )";

		Figure* f = factory->createFigure(std::cin);
		while (f)
		{
			figures.push_back(f);
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
			figures.push_back(figure);
		}
	}
	else
	{
		std::cout << "Invalid factory type.\n";
	}

	for (size_t i = 0; i < figures.size(); i++)
	{
		std::cout << figures[i]->toString() << " perimeter: " << figures[i]->getPerimeter() << "\n";
		delete figures[i];
	}

	return 0;
}
