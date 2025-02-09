#include "catch_amalgamated.hpp"

#include "fakeit.hpp"

#include "TextTransformationDecorator.h"
#include "SimpleLabel.h"

using namespace fakeit;

namespace
{
    class DummyTransformation : public TextTransformation,
								public std::enable_shared_from_this<DummyTransformation>
	{
        std::string suffix;
        bool equalReturn;
    public:
        DummyTransformation(const std::string& s, bool eq)
            : suffix(s), equalReturn(eq)
    	{
        }

        std::string transform(const std::string& text) const override
    	{
            return text + suffix;
        }

        bool operator==(const TextTransformation& other) const override
    	{
            return equalReturn;
        }
    };
}


TEST_CASE("TextTransformationDecorator calls transform on the wrapped transformation")
{
    Mock<TextTransformation> mockTrans;
    When(Method(mockTrans, transform)).AlwaysDo([](const std::string& text) {
        return text + " mocked";
        });
    auto spMock = std::shared_ptr<TextTransformation>(&mockTrans.get(), [](TextTransformation*) {});

	Mock<Label> mockLabel;
	When(Method(mockLabel, getText)).AlwaysReturn("Hello");
	auto spLabel = std::shared_ptr<Label>(&mockLabel.get(), [](Label*) {});

    TextTransformationDecorator decorator(spLabel, spMock);

    REQUIRE(decorator.getText() == "Hello mocked");
	Verify(Method(mockTrans, transform)).Once();
}

TEST_CASE("TextTransformationDecorator throws when provided a nullptr transformation")
{
    Mock<Label> mockLabel;
    auto spLabel = std::shared_ptr<Label>(&mockLabel.get(), [](Label*) {});
	REQUIRE_THROWS_AS(TextTransformationDecorator(spLabel, nullptr), std::invalid_argument);
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

    Mock<Label> mockLabel;
    When(Method(mockLabel, getText)).AlwaysReturn("Middle");
    auto label = std::shared_ptr<Label>(&mockLabel.get(), [](Label*) {});

    auto deco1 = std::make_shared<TextTransformationDecorator>(label, spPrepend);
    deco1 = std::make_shared<TextTransformationDecorator>(deco1, spAppend);

    REQUIRE(deco1->getText() == "Prefix-Middle-Suffix");

    Verify(Method(mockPrepend, transform)).Once();
    Verify(Method(mockAppend, transform)).Once();
}

/* We need to be very careful with the shared_from_this()!!!
 * It requires that the object was created inside a std::shared_ptr (typically via std::make_shared)
 * VERY IMPORTANT: DO NOT WRAP FakeIt mocks with no-op deleters for any part of code that calls
 * shared_from_this()
 */
TEST_CASE("TextTransformationDecorator correctly removes an applied decorator")
{
    Mock<TextTransformation> mtt1;
    When(Method(mtt1, transform)).AlwaysDo([](const std::string& text) {
        return text + "1";
        });
	When(Method(mtt1, operator==)).AlwaysReturn(true);
    Mock<TextTransformation> mtt2;
    When(Method(mtt2, transform)).AlwaysDo([](const std::string& text) {
        return text + "2";
        });
    When(Method(mtt2, operator==)).AlwaysReturn(false);

    Mock<Label> ml1;
    When(Method(ml1, getText)).AlwaysReturn("example text");

    auto spml1 = std::shared_ptr<Label>(&ml1.get(), [](Label*) {});
    auto spmtt1 = std::shared_ptr<TextTransformation>(&mtt1.get(), [](TextTransformation*) {});
    auto spmtt2 = std::shared_ptr<TextTransformation>(&mtt2.get(), [](TextTransformation*) {});

    std::shared_ptr<Label> ttd = std::make_shared<TextTransformationDecorator>(spml1, spmtt1);
    ttd = std::make_shared<TextTransformationDecorator>(ttd, spmtt2);

    std::shared_ptr<LabelDecoratorBase> dummy = std::make_shared<TextTransformationDecorator>(spml1, spmtt1);

    spml1 = LabelDecoratorBase::removeDecoratorFrom(ttd, dummy);

    REQUIRE(spml1->getText() == "example text2");
}

TEST_CASE("TextTransformationDecorator doesn't do anything when trying to remove a non-existing decorator")
{  
    auto spmtt1 = std::make_shared<DummyTransformation>("1", false);
    auto spmtt2 = std::make_shared<DummyTransformation>("2", false);

    auto spml1 = std::make_shared<SimpleLabel>("example text");

    std::shared_ptr<Label> ttd = std::make_shared<TextTransformationDecorator>(spml1, spmtt1);
    ttd = std::make_shared<TextTransformationDecorator>(ttd, spmtt2);

    std::shared_ptr<LabelDecoratorBase> dummy = std::make_shared<TextTransformationDecorator>(spml1, spmtt1);

    auto result = LabelDecoratorBase::removeDecoratorFrom(ttd, dummy);

    REQUIRE(result->getText() == "example text12");
}

TEST_CASE("TextTransformationDecorator delegates equality operator work to the wrapped transformation")
{
	Mock<TextTransformation> mock1;
	When(Method(mock1, transform)).AlwaysDo([](const std::string& text) {
		return text + "1";
		});
	When(Method(mock1, operator==)).AlwaysReturn(true);

	Mock<TextTransformation> mock2;
	When(Method(mock2, transform)).AlwaysDo([](const std::string& text) {
		return text + "2";
		});
	When(Method(mock2, operator==)).AlwaysReturn(true);

	auto spMock1 = std::shared_ptr<TextTransformation>(&mock1.get(), [](TextTransformation*) {});
	auto spMock2 = std::shared_ptr<TextTransformation>(&mock2.get(), [](TextTransformation*) {});

	Mock<Label> mockLabel;
	When(Method(mockLabel, getText)).AlwaysReturn("Hello");
	auto spLabel = std::shared_ptr<Label>(&mockLabel.get(), [](Label*) {});

    std::shared_ptr<LabelDecoratorBase> decorator1 = std::make_shared<TextTransformationDecorator>(spLabel, spMock1);
    std::shared_ptr<LabelDecoratorBase> decorator2 = std::make_shared<TextTransformationDecorator>(spLabel, spMock2);

    REQUIRE(decorator1 == decorator1);
}
