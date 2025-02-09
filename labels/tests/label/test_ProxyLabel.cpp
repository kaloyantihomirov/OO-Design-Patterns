#include "catch_amalgamated.hpp"

#include "ProxyLabel.h"

TEST_CASE("ProxyLabel lazy initialization")
{
    std::istringstream fakeInput("Hello\n");
    std::ostringstream fakeOutput;

    ProxyLabel proxy(5, fakeInput, fakeOutput);

    std::string text = proxy.getText();
    REQUIRE(text == "Hello");

    std::string outputStr = fakeOutput.str();
    REQUIRE(outputStr.find("Please, enter label value: ") != std::string::npos);
}

TEST_CASE("ProxyLabel returns cached value before timeout")
{
    std::istringstream fakeInput("CachedLabel\n");
    std::ostringstream fakeOutput;

    ProxyLabel proxy(5, fakeInput, fakeOutput);

    REQUIRE(proxy.getText() == "CachedLabel");

    for (int i = 0; i < 3; i++) 
    {
        REQUIRE(proxy.getText() == "CachedLabel");
    }

    std::string outputStr = fakeOutput.str();
    REQUIRE(outputStr.find("Do you want to update label text?") == std::string::npos);
}

TEST_CASE("ProxyLabel update timeout: user declines update")
{
    std::istringstream fakeInput("Initial\nn\n");
    std::ostringstream fakeOutput;

    ProxyLabel proxy(3, fakeInput, fakeOutput);

    REQUIRE(proxy.getText() == "Initial");

    REQUIRE(proxy.getText() == "Initial");
    REQUIRE(proxy.getText() == "Initial");

    REQUIRE(proxy.getText() == "Initial");

    std::string outputStr = fakeOutput.str();
    REQUIRE(outputStr.find("Do you want to update label text?") != std::string::npos);
}

TEST_CASE("ProxyLabel update timeout: user accepts update")
{
    std::istringstream fakeInput("OldValue\ny\nNewValue\n");
    std::ostringstream fakeOutput;

    ProxyLabel proxy(3, fakeInput, fakeOutput);

    REQUIRE(proxy.getText() == "OldValue");
    REQUIRE(proxy.getText() == "OldValue");
    REQUIRE(proxy.getText() == "OldValue");

    REQUIRE(proxy.getText() == "NewValue");
    REQUIRE(proxy.getText() == "NewValue");
}
