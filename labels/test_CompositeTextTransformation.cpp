#include "catch_amalgamated.hpp"
#include "fakeit.hpp"

#include "CompositeTransformation.h"

using namespace fakeit;

//visible only in current translation unit (can be used as alternative of FakeIt which I used
//as a mocking framework)
namespace
{
    class DummyTransformation : public TextTransformation
    {
    public:
        std::string transform(const std::string& text) const override
        {
            return text;
        }
    };
}

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

TEST_CASE("CompositeTransformation applies transformations in correct order when 3 transformations available")
{
    Mock<TextTransformation> mock1;
    When(Method(mock1, transform)).AlwaysDo([](const std::string& text) {
        return text + "1";
        });

    Mock<TextTransformation> mock2;
    When(Method(mock2, transform)).AlwaysDo([](const std::string& text) {
        return text + "2";
        });

    Mock<TextTransformation> mock3;
    When(Method(mock3, transform)).AlwaysDo([](const std::string& text) {
        return text + "3";
        });

    auto sp1 = std::shared_ptr<TextTransformation>(&mock1.get(), [](TextTransformation*) {});
    auto sp2 = std::shared_ptr<TextTransformation>(&mock2.get(), [](TextTransformation*) {});
    auto sp3 = std::shared_ptr<TextTransformation>(&mock3.get(), [](TextTransformation*) {});

    std::vector<std::shared_ptr<TextTransformation>> transformations;
    transformations.push_back(sp2);
    transformations.push_back(sp1);
	transformations.push_back(sp3);

    CompositeTransformation composite(transformations);

    std::string input = "Test";
    REQUIRE(composite.transform(input) == "Test213");

    Verify(Method(mock1, transform)).Once();
    Verify(Method(mock2, transform)).Once();
    Verify(Method(mock3, transform)).Once();
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

TEST_CASE("CompositeTransformation throws exception if vector contains nullptr")
{
    std::vector<std::shared_ptr<TextTransformation>> transformations;

    SECTION("First element is nullptr")
    {
        transformations.push_back(nullptr);
        REQUIRE_THROWS_AS(CompositeTransformation(transformations), std::invalid_argument);
    }
    SECTION("Other element is nullptr")
    {
        auto j = GENERATE(15, 40, 98);

        DYNAMIC_SECTION(j << "th" << "element is nullptr (0 indexed)")
        {
            for (int i = 0; i < j; i++)
            {
                transformations.push_back(std::make_shared<DummyTransformation>());
            }
            transformations.push_back(nullptr);

            REQUIRE_THROWS_AS(CompositeTransformation(transformations), std::invalid_argument);
        }
    }
}

