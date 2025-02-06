#include "catch_amalgamated.hpp"

#include "Replace.h"

TEST_CASE("Replace returns empty string when empty input")
{
	Replace r("abrakadabra", "boom");
	REQUIRE(r.transform("").empty());
}

