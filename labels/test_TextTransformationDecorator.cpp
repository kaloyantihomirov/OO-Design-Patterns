#include "catch_amalgamated.hpp"

#include "fakeit.hpp"

#include "TextTransformationDecorator.h"
#include "SimpleLabel.h"

using namespace fakeit;

TEST_CASE("TextTransformationDecorator calls transform on the wrapped transformation")
{
    Mock<TextTransformation> mockTrans;
    When(Method(mockTrans, transform)).AlwaysDo([](const std::string& text) {
        return text + " mocked";
        });

    auto spMock = std::shared_ptr<TextTransformation>(&mockTrans.get(), [](TextTransformation*) {});
    auto label = std::make_shared<SimpleLabel>("Hello");
    TextTransformationDecorator decorator(label, spMock);

    REQUIRE(decorator.getText() == "Hello mocked");
	Verify(Method(mockTrans, transform)).Once();
}

TEST_CASE("TextTransformationDecorator throws when provided a nullptr transformation")
{
    auto label = std::make_shared<SimpleLabel>("Hello");
    REQUIRE_THROWS_AS(TextTransformationDecorator(label, nullptr), std::invalid_argument);
}

TEST_CASE("Chained decorators call each mock transformation in sequence")
{
    Mock<TextTransformation> mockPrepend;
    When(Method(mockPrepend, transform)).AlwaysDo([](const std::string& text) {
        return std::string("Prefix-") + text;
        });

    Mock<TextTransformation> mockAppend;
    When(Method(mockAppend, transform)).AlwaysDo([](const std::string& text) {
        return text + "-Suffix";
        });

    auto spPrepend = std::shared_ptr<TextTransformation>(&mockPrepend.get(), [](TextTransformation*) {});
    auto spAppend = std::shared_ptr<TextTransformation>(&mockAppend.get(), [](TextTransformation*) {});

    auto label = std::make_shared<SimpleLabel>("Middle");

    auto deco1 = std::make_shared<TextTransformationDecorator>(label, spPrepend);
    deco1 = std::make_shared<TextTransformationDecorator>(deco1, spAppend);

    REQUIRE(deco1->getText() == "Prefix-Middle-Suffix");

    Verify(Method(mockPrepend, transform)).Once();
    Verify(Method(mockAppend, transform)).Once();
}
