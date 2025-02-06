#include "catch_amalgamated.hpp"

#include "CapitaliseTransformation.h"

TEST_CASE("Capitalise capitalises first character if lowercase")
{
	CapitaliseTransformation ct;
	std::string res = ct.transform("aNABEL is the best movie ever");
	REQUIRE(res == "ANABEL is the best movie ever");
}

TEST_CASE("Capitalise returns empty string for empty input")
{
	CapitaliseTransformation ct;
	std::string res = ct.transform("");
	REQUIRE(res.empty());
}

TEST_CASE("Capitalise returns unchanged string when first character is punctuation")
{
	CapitaliseTransformation ct;
	std::string text = "@    sample input";
	std::string res = ct.transform(text);
	REQUIRE(res == text);
}

TEST_CASE("Capitalise doesn't change already capitalised string")
{
	CapitaliseTransformation ct;
	std::string text = "Sample input";
	std::string res = ct.transform(text);
	REQUIRE(res == text);
}

TEST_CASE("Capitalise handles single lowercase character")
{
	CapitaliseTransformation ct;
	REQUIRE(ct.transform("a") == "A");
}

TEST_CASE("Capitalise handles single character equal to everything but lowercase letter")
{
	CapitaliseTransformation ct;
	REQUIRE(ct.transform("L") == "L");
	REQUIRE(ct.transform("#") == "#");
}

TEST_CASE("Every two capitalise transformations are considered equal")
{
	TextTransformation* tt1 = new CapitaliseTransformation();
	TextTransformation* tt2 = new CapitaliseTransformation();
	REQUIRE(*tt1 == *tt2);
	delete tt1;
	delete tt2;
}