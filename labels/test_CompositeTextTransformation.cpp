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

TEST_CASE("CompositeTransformation equality operator works correctly") 
{
    Mock<TextTransformation> mock1a;
    When(Method(mock1a, transform)).AlwaysReturn("dummy");
    When(Method(mock1a, operator==)).AlwaysReturn(true);
    Mock<TextTransformation> mock2a;
    When(Method(mock2a, transform)).AlwaysReturn("dummy");
    When(Method(mock2a, operator==)).AlwaysReturn(true);

    auto spMock1a = std::shared_ptr<TextTransformation>(&mock1a.get(), [](TextTransformation*) {});
    auto spMock2a = std::shared_ptr<TextTransformation>(&mock2a.get(), [](TextTransformation*) {});

    std::vector<std::shared_ptr<TextTransformation>> transformations1;
    transformations1.push_back(spMock1a);
    transformations1.push_back(spMock2a);

    CompositeTransformation composite1(transformations1);

    Mock<TextTransformation> mock1b;
    When(Method(mock1b, transform)).AlwaysReturn("dummy");
    When(Method(mock1b, operator==)).AlwaysReturn(true);

    Mock<TextTransformation> mock2b;
    When(Method(mock2b, transform)).AlwaysReturn("dummy");
    When(Method(mock2b, operator==)).AlwaysReturn(true);

    auto spMock1b = std::shared_ptr<TextTransformation>(&mock1b.get(), [](TextTransformation*) {});
    auto spMock2b = std::shared_ptr<TextTransformation>(&mock2b.get(), [](TextTransformation*) {});

    std::vector<std::shared_ptr<TextTransformation>> transformations2;
    transformations2.push_back(spMock1b);
    transformations2.push_back(spMock2b);

    CompositeTransformation composite2(transformations2);

    // The operator== for CompositeTransformation should compare the sizes and then
    // call operator== on each corresponding transformation. Since all operator== calls
    // return true, the composites should compare equal.
    REQUIRE(composite1 == composite2);
}

TEST_CASE("CompositeTransformation operator== returns false for composites with different sizes", "[CompositeTransformation][Equality]") {
    // Create a mock for a single transformation.
    Mock<TextTransformation> mock;
    When(Method(mock, transform)).AlwaysReturn("dummy");
    When(Method(mock, operator==)).AlwaysReturn(true);

    auto spMock = std::shared_ptr<TextTransformation>(mock.get(), [](TextTransformation*) {});

    // Composite with one transformation.
    std::vector<std::shared_ptr<TextTransformation>> trans1;
    trans1.push_back(spMock);
    CompositeTransformation comp1(trans1);

    // Composite with two transformations.
    std::vector<std::shared_ptr<TextTransformation>> trans2;
    trans2.push_back(spMock);
    trans2.push_back(spMock);
    CompositeTransformation comp2(trans2);

    REQUIRE_FALSE(comp1 == comp2);
}

TEST_CASE("CompositeTransformation operator== returns false when one transformation differs", "[CompositeTransformation][Equality]") {
    // Create a mock for the first transformation that always returns true for equality.
    Mock<TextTransformation> mock1;
    When(Method(mock1, transform)).AlwaysReturn("dummy");
    When(Method(mock1, operator==)).AlwaysReturn(true);

    // Create two mocks for the second transformation.
    Mock<TextTransformation> mock2a;
    When(Method(mock2a, transform)).AlwaysReturn("dummy");
    When(Method(mock2a, operator==)).AlwaysReturn(true);

    Mock<TextTransformation> mock2b;
    When(Method(mock2b, transform)).AlwaysReturn("dummy");
    // For this second instance, force operator== to return false.
    When(Method(mock2b, operator==)).AlwaysReturn(false);

    auto spMock1 = std::shared_ptr<TextTransformation>(mock1.get(), [](TextTransformation*) {});
    auto spMock2a = std::shared_ptr<TextTransformation>(mock2a.get(), [](TextTransformation*) {});
    auto spMock2b = std::shared_ptr<TextTransformation>(mock2b.get(), [](TextTransformation*) {});

    std::vector<std::shared_ptr<TextTransformation>> trans1;
    trans1.push_back(spMock1);
    trans1.push_back(spMock2a);
    CompositeTransformation comp1(trans1);

    std::vector<std::shared_ptr<TextTransformation>> trans2;
    trans2.push_back(spMock1);
    trans2.push_back(spMock2b);
    CompositeTransformation comp2(trans2);

    REQUIRE_FALSE(comp1 == comp2);
}
