#include "catch_amalgamated.hpp"

#include "Decorate.h"

TEST_CASE("Decorate transformation decorates text correctly")
{
	Decorate decorate;
	std::string res = decorate.transform("abc");
	REQUIRE(res == "-={ abc }=-");
}

TEST_CASE("Decorate transformation decorates empty text correctly")
{
	Decorate decorate;
	std::string res = decorate.transform("");
	REQUIRE(res == "-={  }=-");
}

TEST_CASE("Every two decorate transformations are considered equal")
{
	TextTransformation* tt1 = new Decorate();
	TextTransformation* tt2 = new Decorate();
	REQUIRE(*tt1 == *tt2);
	delete tt1;
	delete tt2;
}
