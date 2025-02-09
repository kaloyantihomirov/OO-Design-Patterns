#include "catch_amalgamated.hpp"

#include "NormaliseSpace.h"

TEST_CASE("NormaliseSpace returns string with maximum one consecutive space character")
{
	NormaliseSpace ns;
	std::string text = "maximum  one consecutive     space characters    ";
	std::string expected = "maximum one consecutive space characters ";
	REQUIRE(ns.transform(text) == expected);
}

TEST_CASE("NormaliseSpace returns same string when normalised input")
{
	NormaliseSpace ns;
	std::string text = " maximum one consecutive space characters example ";
	REQUIRE(ns.transform(text) == text);
}

TEST_CASE("NormaliseSpace returns same string when no whitespace chars")
{
	NormaliseSpace ns;
	std::string text = "verylongwordwithoutspaces";
	REQUIRE(ns.transform(text) == text);
}

TEST_CASE("NormaliseSpace returns empty string when empty input")
{
	NormaliseSpace ns;
	REQUIRE(ns.transform("").empty());
}

TEST_CASE("NormaliseSpace returns one space when given a sequence of 2 or more spaces")
{
	auto i = GENERATE(2, 3, 4, 5, 6);

	DYNAMIC_SECTION("Check if input of " << i << "spaces produces one space as a result")
	{
		NormaliseSpace ns;
		REQUIRE(ns.transform(std::string(i, ' ')) == " ");
	}
}

TEST_CASE("NormaliseSpace handles mixed whitespace characters")
{
	NormaliseSpace ns;

	SECTION("one")
	{
		std::string text = "\t\nsample text";
		REQUIRE(ns.transform(text) == " sample text");
	}
	SECTION("two")
	{
		std::string text = "\t\t\n      sample  text      ";
		REQUIRE(ns.transform(text) == " sample text ");
	}
}

TEST_CASE("Every two normalise space transformations are considered equal")
{
	TextTransformation* tt1 = new NormaliseSpace();
	TextTransformation* tt2 = new NormaliseSpace();
	REQUIRE(*tt1 == *tt2);
	delete tt1;
	delete tt2;
}