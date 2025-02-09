#include "catch_amalgamated.hpp"

#include "Replace.h"

TEST_CASE("Replace correctly replaces replaceWhat with replaceWith")
{
	Replace r("aba", "dada");

	SECTION("one occurrence")
	{
		std::string text = "aba abi abub";
		REQUIRE(r.transform(text) == "dada abi abub");
	}
	SECTION("more occurrences")
	{
		std::string text = "abaabaaba";
		REQUIRE(r.transform(text) == "dadadadadada");
	}
}

TEST_CASE("Replace returns input if replaceWhat is empty")
{
	Replace r("", "something");
	std::string text = "Abu Dhabi";
	REQUIRE(r.transform(text) == text);
}

TEST_CASE("Replace cuts replaceWhat from input when replaceWithWhat is empty")
{
	Replace r("aa", "");

	std::string text = "aaMy favourite person is my mother.";
	REQUIRE(r.transform(text) == "My favourite person is my mother.");
}

TEST_CASE("Replace returns empty string when empty input")
{
	Replace r("abrakadabra", "boom");
	REQUIRE(r.transform("").empty());
}

TEST_CASE("Replace works when occurrence is at the beginning")
{
	Replace r("cats", "dogs");
	std::string text = "cats are my favourite animals";
	std::string expected = "dogs are my favourite animals";
	REQUIRE(r.transform(text) == expected);
}

TEST_CASE("Replace works when occurrence is at the end")
{
	Replace r("winter", "summer");
	std::string text = "my favourite season is winter";
	std::string expected = "my favourite season is summer";
	REQUIRE(r.transform(text) == expected);
}

TEST_CASE("Replace returns input when replaceWhat is not found")
{
	Replace r("winter", "summer");
	std::string text = "i need to get back in the gym";
	REQUIRE(r.transform(text) == text);
}

TEST_CASE("Replace equality operator works")
{
	TextTransformation* tt1 = new Replace("aa", "bb");
	TextTransformation* tt2 = nullptr;

	SECTION("when both replace transformations have equal replaceWhat and replaceWithWhat words")
	{
		tt2 = new Replace("aa", "bb");
		REQUIRE(*tt1 == *tt2);
	}
	SECTION("when replace transformations have different replaceWhat words")
	{
		tt2 = new Replace("bb", "ask");
		REQUIRE_FALSE(*tt1 == *tt2);
	}
	SECTION("when replace transformations have different replaceWithWhat symbols")
	{
		tt2 = new Replace("aa", "b");
		REQUIRE_FALSE(*tt1 == *tt2);
	}

	delete tt2;
	delete tt1;
}