#include "catch_amalgamated.hpp"

#include "RightTrim.h"

TEST_CASE("RightTrim trims all whitespaces at the end")
{
    RightTrim rt;
    REQUIRE(rt.transform("sample text    ") == "sample text");
}

TEST_CASE("RightTrim returns same string when last symbols are not whitespace")
{
    RightTrim rt;
    std::string text = "     sample  text";
    REQUIRE(rt.transform(text) == text);
}

TEST_CASE("RightTrim returns empty string when input is empty")
{
    RightTrim rt;
    REQUIRE(rt.transform("").empty());
}

TEST_CASE("RightTrim returns empty string when input is all whitespace")
{
    RightTrim rt;
    REQUIRE(rt.transform("           ").empty());
}

TEST_CASE("RightTrim trims various types of whitespace")
{
    RightTrim rt;
    std::string text = "some text\t\n \n   ";
    REQUIRE(rt.transform(text) == "some text");
}

TEST_CASE("RightTrim does not remove leading whitespace")
{
    RightTrim rt;
    std::string text = "\t \n           some text";
    REQUIRE(rt.transform(text) == text);
}

TEST_CASE("Every two right trim transformations are considered equal")
{
    TextTransformation* tt1 = new RightTrim();
    TextTransformation* tt2 = new RightTrim();
    REQUIRE(*tt1 == *tt2);
    delete tt1;
    delete tt2;
}
