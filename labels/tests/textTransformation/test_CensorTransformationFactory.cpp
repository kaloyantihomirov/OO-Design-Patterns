#include "catch_amalgamated.hpp"

#include "CensorTransformationFactory.h"

TEST_CASE("CensorTransformationFactory utilises flyweight when l(censorWord) <= threshold")
{
	CensorTransformationFactory factory;

	SECTION("When creating a censor transformation with a word of length 4 or less, it should return a cached instance")
	{
		auto censor1 = factory.createCensorTransformation("test");
		auto censor2 = factory.createCensorTransformation("test");
		REQUIRE(censor1 == censor2);
	}
	SECTION("When creating a censor transformation with a word of length 5 or more, it should return a new instance")
	{
		auto censor1 = factory.createCensorTransformation("testing");
		auto censor2 = factory.createCensorTransformation("testing");
		REQUIRE(censor1 != censor2);
	}
	SECTION("When creating two transformations t1 and t2 with words of length l1 and l2 s. t. l1 <= threshold and l2 > threshold, it should properly handle it")
	{
		auto censor1 = factory.createCensorTransformation("test");
		auto censor2 = factory.createCensorTransformation("testing");
		auto censor3 = factory.createCensorTransformation("test");
		REQUIRE(censor1 != censor2);
		REQUIRE(censor1 == censor3);
	}
}

