#include "catch_amalgamated.hpp"

#include "Censor.h"

TEST_CASE("Censor works correctly and censors a word by replacing its characters with a given symbol")
{
	Censor tt("gerb", '*');
	std::string res = tt.transform("gerb anakonda gulub den");
	REQUIRE(res == "**** anakonda gulub den");
}

TEST_CASE("Censor default replaceWith symbol is correctly set to star")
{
	Censor tt("alabala");
	std::string res = tt.transform("alabala qgodi maslini");
	REQUIRE(res == "******* qgodi maslini");
}

TEST_CASE("Censor does nothing when word is not present")
{
	Censor tt("fmi", '*');
	std::string text = "fkf fhf ff mu  fmI";
	std::string res = tt.transform(text);
	REQUIRE(res == text);
}

TEST_CASE("Censor censors all occurrences")
{
	Censor tt("bad", '*');
	std::string res = tt.transform("bad sentence with bad words and flying bats");
	REQUIRE(res == "*** sentence with *** words and flying bats");
}

TEST_CASE("Censor handles empty input")
{
	Censor tt("koki", '*');
	std::string res = tt.transform("");
	REQUIRE(res.empty());
}

TEST_CASE("Censor handles empty censor word")
{
	Censor tt("", '*');
	std::string res = tt.transform("sample text");
	REQUIRE(res == "sample text");
}

TEST_CASE("Censor handles overlapping occurrences")
{
	Censor tt("aa", '*');
	std::string res = tt.transform("aaa");
	REQUIRE(res == "**a");
}

TEST_CASE("Censor equality operator works")
{
	TextTransformation* tt1 = new Censor("aa", '*');
	TextTransformation* tt2 = nullptr;

	SECTION("when both censor transformations have equal censorWords and replaceWith symbols")
	{
		tt2 = new Censor("aa", '*');
		REQUIRE(*tt1 == *tt2);
	}
	SECTION("when censor transformations have different censorWords")
	{
        tt2 = new Censor("bb", '*');
		REQUIRE_FALSE(*tt1 == *tt2);
	}
	SECTION("when censor transformations have different replaceWith symbols")
	{
		tt2 = new Censor("a", '#');
		REQUIRE_FALSE(*tt1 == *tt2);
	}

	delete tt2;
	delete tt1;
}