#include <iostream>
#include <fstream>
#include <vector>

#include "RandomFigureFactory.h"
#include "ReadFromStreamFigureFactory.h"

int main2()
{
	std::cout << "Please choose factory type: [0 for random, 1 for importing figures from file]: ";
	int choice;
	std::cin >> choice;

	FigureFactory* factory = nullptr;
	std::vector<Figure*> figures;

	if (choice == 0)
	{
		//factory = new RandomFigureFactory();
		for (int i = 0; i < 10; i++)
		{
			figures.push_back(factory->createFigure());
		}
	}
	else if (choice == 1)
	{
		std::string fileName;
		std::cout << "Please enter file name: ";
		std::cin >> fileName;
		std::ifstream in(fileName);
		if (!in)
		{
			std::cout << "Could not open file.\n";
			return 1;
		}
		factory = new ReadFromStreamFigureFactory(in);
		while (in)
		{
			figures.push_back(factory->createFigure());
		}
		in.close();
	}
	else
	{
		std::cout << "Invalid factory type.\n";

	}
	else if (choice == 1)
	{
		
	}
	else
	{
		std::cout << "Invalid factory type.\n";
	}

	

	return 0;
}
