#include "LabelFactory.h"

#include "HelpLabel.h"
#include "ProxyLabel.h"
#include "RichLabel.h"
#include "SimpleLabel.h"

std::unique_ptr<ILabel> LabelFactory::createSimpleLabel(const std::string& value)
{
	return std::make_unique<SimpleLabel>(value);
}

std::unique_ptr<ILabel> LabelFactory::createRichLabel(const std::string& value, const std::string& fontName, int fontSize, uint8_t red, uint8_t green, uint8_t blue)
{
	return std::make_unique<RichLabel>(value, fontName, fontSize, ColourRGB(red, green, blue));
}

std::unique_ptr<ILabel> LabelFactory::createProxyLabel(int timeout)
{
	return std::make_unique<ProxyLabel>(timeout);
}

std::unique_ptr<LabelAbstraction> LabelFactory::createHelpLabel(std::unique_ptr<Label> l, const std::string& helpText)
{
	return std::make_unique<HelpLabel>(std::move(l), helpText);
}



