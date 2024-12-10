#include <iostream>
#include <sstream>
#include <memory>

#include "catch_amalgamated.hpp"

#include "CircleCreator.h"
#include "ReadFromStreamFigureFactory.h"
#include "TriangleCreator.h"

struct FiguresCollectionFixture
{
	std::vector<std::unique_ptr<Figure>> figures;

	FiguresCollectionFixture()
	{
		generateFigures();
	}

	void generateFigures()
	{
		for (size_t i = 0; i < 10; i++)
		{
			if (i % 2 == 0)
			{
				figures.push_back(std::make_unique<Circle>(10 + i));
			}
			else
			{
				figures.push_back(std::make_unique<Triangle>(3 + i, 4 + i, 5 + i));
			}
		}
	}

	std::string getFiguresAsString() const
	{
		std::string figuresToStr;

		for (const auto& figure : figures)
		{
			figuresToStr += figure->toString() + "\n";
		}

		return figuresToStr;
	}
};

void setupFactory(ReadFromStreamFigureFactory& factory)
{
	factory.clearCreators();
	factory.registerFigure("triangle", std::make_unique<TriangleCreator>());
	factory.registerFigure("circle", std::make_unique<CircleCreator>());
}

TEST_CASE("ReadFromStreamFigureFactory throws when no figures registered")
{
	auto iss = std::make_shared<std::istringstream>("triangle 10 20 20");
	ReadFromStreamFigureFactory factory(iss);
	factory.clearCreators();
	REQUIRE_THROWS_AS(factory.createFigure(), std::invalid_argument);
}

TEST_CASE("ReadFromStreamFigureFactory correctly creates a triangle for a valid triangle representation")
{
	auto iss = std::make_shared<std::istringstream>("triangle 10 20 20");
	ReadFromStreamFigureFactory factory(iss);
	setupFactory(factory);
	std::unique_ptr<Figure> figure = factory.createFigure();
	REQUIRE(figure->toString() == "triangle 10 20 20");
}

TEST_CASE("ReadFromStreamFigureFactory throws when trying to create a figure from unregistered type")
{
	auto iss = std::make_shared<std::istringstream>("triangle 10 20 20");
	ReadFromStreamFigureFactory factory(iss);
	factory.clearCreators();
	factory.registerFigure("circle", std::make_unique<CircleCreator>());
	REQUIRE_THROWS_AS(factory.createFigure(), std::invalid_argument);
}

TEST_CASE_METHOD(FiguresCollectionFixture, "ReadFromStreamFigureFactory correctly creates figures from different registered types")
{
	auto iss = std::make_shared<std::istringstream>(getFiguresAsString());
	ReadFromStreamFigureFactory factory(iss);
	setupFactory(factory);

	std::vector<std::unique_ptr<Figure>> result;
	while (*iss)
	{
		std::unique_ptr<Figure> f = factory.createFigure();
		if (!f)
		{
			break;
		}
		result.push_back(std::move(f));
	}

	REQUIRE(result.size() == figures.size());

	for (size_t i = 0; i < 10; i++)
	{
		REQUIRE(result[i]->toString() == figures[i]->toString());
	}
}

TEST_CASE("ReadFromStreamFigureFactory handles empty input stream")
{
	auto iss = std::make_shared<std::istringstream>("");
	ReadFromStreamFigureFactory factory(iss);
	setupFactory(factory);
	REQUIRE(factory.createFigure() == nullptr);
}

TEST_CASE("ReadFromStreamFigureFactory handles broken input stream")
{
	auto iss = std::make_shared<std::istringstream>("design-Patterns");
	int num;
	*iss >> num; 
	ReadFromStreamFigureFactory factory(iss);
	REQUIRE(factory.createFigure() == nullptr);
}

TEST_CASE("ReadFromStreamFigureFactory throws when input format is invalid")
{
	auto iss = std::make_shared<std::istringstream>("invalid_format");
	ReadFromStreamFigureFactory factory(iss);
	setupFactory(factory);
	REQUIRE_THROWS_AS(factory.createFigure(), std::invalid_argument);
}



