#include "catch_amalgamated.hpp"

#include "LeftTrim.h"

TEST_CASE("LeftTrim trims all whitespaces in beginning")
{
	LeftTrim lt;
	REQUIRE(lt.transform("    sample text") == "sample text");
}

TEST_CASE("LefTrim returns same string when first symbols not whitespace")
{
	LeftTrim lt;
	std::string text = "sample text";
	REQUIRE(lt.transform(text) == text);
}

TEST_CASE("LeftTrim returns empty string when empty input")
{
	LeftTrim lt;
	REQUIRE(lt.transform("").empty());
}

TEST_CASE("LeftTrim returns empty string when input is all whitespace")
{
	LeftTrim lt;
	REQUIRE(lt.transform("           ").empty());
}

TEST_CASE("LeftTrim trims various types of whitespace")
{
	LeftTrim lt;
	std::string text = "\t\n \n   some text";
	REQUIRE(lt.transform(text) == "some text");
}

TEST_CASE("LeftTrim does not remove trailing whitespace")
{
	LeftTrim lt;
	std::string text = "some text           \t \n";
	REQUIRE(lt.transform(text) == text);
}

TEST_CASE("Every two left trim transformations are considered equal")
{
	TextTransformation* tt1 = new LeftTrim();
	TextTransformation* tt2 = new LeftTrim();
	REQUIRE(*tt1 == *tt2);
	delete tt1;
	delete tt2;
}