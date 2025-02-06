#include "catch_amalgamated.hpp"
#include "fakeit.hpp"

#include "CompositeTransformation.h"

using namespace fakeit;

TEST_CASE("CompositeTransformation calls each transformation in sequence")
{
    Mock<TextTransformation> mock1;
    When(Method(mock1, transform)).AlwaysDo([](const std::string& text) {
        return text + "1";
        });

    Mock<TextTransformation> mock2;
    When(Method(mock2, transform)).AlwaysDo([](const std::string& text) {
        return text + "2";
        });

    auto sp1 = std::shared_ptr<TextTransformation>(&mock1.get(), [](TextTransformation*) {});
    auto sp2 = std::shared_ptr<TextTransformation>(&mock2.get(), [](TextTransformation*) {});

    std::vector<std::shared_ptr<TextTransformation>> transformations1;
    transformations1.push_back(sp1);
    transformations1.push_back(sp2);

    std::vector<std::shared_ptr<TextTransformation>> transformations2;
    transformations2.push_back(sp2);
    transformations2.push_back(sp1);

    CompositeTransformation composite1(transformations1);
    CompositeTransformation composite2(transformations2);

    std::string input = "Test";
    REQUIRE(composite1.transform(input) == "Test12");
    REQUIRE(composite2.transform(input) == "Test21");

    Verify(Method(mock1, transform)).Exactly(2);
    Verify(Method(mock2, transform)).Exactly(2);
}

TEST_CASE("CompositeTransformation returns input unchanged with no transformations")
{
    std::vector<std::shared_ptr<TextTransformation>> emptyTransformations;
    CompositeTransformation composite(emptyTransformations);
    std::string text = "sample text";
    REQUIRE(composite.transform(text) == text);
}

TEST_CASE("CompositeTransformation applies a single transformation correctly")
{
    Mock<TextTransformation> mock1;

    When(Method(mock1, transform)).AlwaysDo([](const std::string& text)
    {
            return text + "_end";
    });

    auto sp = std::shared_ptr<TextTransformation>(&mock1.get(), [](TextTransformation*) { });
    std::vector<std::shared_ptr<TextTransformation>> transformations;
    transformations.push_back(sp);

    std::string text = "koki";
    std::string expected = "koki_end";

    CompositeTransformation ct(transformations);

    REQUIRE(ct.transform(text) == expected);
    Verify(Method(mock1, transform)).Once();
}



