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

        bool operator==(const TextTransformation& other) const override { return true;  }
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

TEST_CASE("CompositeTransformation equality operator returns true for composites with identical transformation sequences")
{
	/* The situation is a bit tricky. If we have a composite transformation that consists of only one
     * "simple" transformation, should we then consider the two transformations (the composite one
     * and the single "simple" one it consists of) equal, based solely on the fact that they yield
     * the same result for any input? In the solution I propose, we consider two composite transformations
     * equal if and only if both are *composite* and their constituent transformations are equal
     * in the sense of operator==.
     */

    Mock<TextTransformation> mock1a;
    When(Method(mock1a, operator==)).AlwaysReturn(true);
    Mock<TextTransformation> mock2a;
    When(Method(mock2a, operator==)).AlwaysReturn(true);

    auto spMock1a = std::shared_ptr<TextTransformation>(&mock1a.get(), [](TextTransformation*) {});
    auto spMock2a = std::shared_ptr<TextTransformation>(&mock2a.get(), [](TextTransformation*) {});

    std::vector<std::shared_ptr<TextTransformation>> transformations1;
    transformations1.push_back(spMock1a);
    transformations1.push_back(spMock2a);

    std::shared_ptr<TextTransformation> composite1 = std::make_shared<CompositeTransformation>(transformations1);

    Mock<TextTransformation> mock1b;
    When(Method(mock1b, operator==)).AlwaysReturn(true);
    Mock<TextTransformation> mock2b;
    When(Method(mock2b, operator==)).AlwaysReturn(true);

    auto spMock1b = std::shared_ptr<TextTransformation>(&mock1b.get(), [](TextTransformation*) {});
    auto spMock2b = std::shared_ptr<TextTransformation>(&mock2b.get(), [](TextTransformation*) {});

    std::vector<std::shared_ptr<TextTransformation>> transformations2;
    transformations2.push_back(spMock1b);
    transformations2.push_back(spMock2b);

    std::shared_ptr<TextTransformation> composite2 = std::make_shared<CompositeTransformation>(transformations2);

    REQUIRE(*composite1 == *composite2);
}

TEST_CASE("CompositeTransformation equality operator returns false for composites with different transformation sequences")
{
    Mock<TextTransformation> mock1a;
    When(Method(mock1a, operator==)).AlwaysReturn(true);
    Mock<TextTransformation> mock2a;
    When(Method(mock2a, operator==)).AlwaysReturn(false);

    auto spMock1a = std::shared_ptr<TextTransformation>(&mock1a.get(), [](TextTransformation*) {});
    auto spMock2a = std::shared_ptr<TextTransformation>(&mock2a.get(), [](TextTransformation*) {});

    std::vector<std::shared_ptr<TextTransformation>> transformations1;
    transformations1.push_back(spMock1a);
    transformations1.push_back(spMock2a);

    std::shared_ptr<TextTransformation> composite1 = std::make_shared<CompositeTransformation>(transformations1);

    Mock<TextTransformation> mock1b;
    When(Method(mock1b, operator==)).AlwaysReturn(true);
    Mock<TextTransformation> mock2b;
    When(Method(mock2b, operator==)).AlwaysReturn(false);

    auto spMock1b = std::shared_ptr<TextTransformation>(&mock1b.get(), [](TextTransformation*) {});
    auto spMock2b = std::shared_ptr<TextTransformation>(&mock2b.get(), [](TextTransformation*) {});

    std::vector<std::shared_ptr<TextTransformation>> transformations2;
    transformations2.push_back(spMock1b);
    transformations2.push_back(spMock2b);

    std::shared_ptr<TextTransformation> composite2 = std::make_shared<CompositeTransformation>(transformations2);

    REQUIRE_FALSE(*composite1 == *composite2);
}

TEST_CASE("CompositeTransformation equality operator returns false for composites with different sizes")
{
    Mock<TextTransformation> mock;
    When(Method(mock, operator==)).AlwaysReturn(true);

    auto spMock = std::shared_ptr<TextTransformation>(&mock.get(), [](TextTransformation*) {});

    std::vector<std::shared_ptr<TextTransformation>> trans1;
    trans1.push_back(spMock);
    std::shared_ptr<TextTransformation> comp1 = std::make_shared<CompositeTransformation>(trans1);

    std::vector<std::shared_ptr<TextTransformation>> trans2;
    trans2.push_back(spMock);
    trans2.push_back(spMock);
    std::shared_ptr<TextTransformation> comp2 = std::make_shared<CompositeTransformation>(trans2);

    REQUIRE_FALSE(*comp1 == *comp2);
}
