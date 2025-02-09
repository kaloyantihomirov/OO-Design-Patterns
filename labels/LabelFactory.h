#pragma once

#include <memory>
#include "ILabel.h"
#include "LabelAbstraction.h"

class LabelFactory
{
public:
	std::unique_ptr<ILabel> createSimpleLabel(const std::string& value);
	std::unique_ptr<ILabel> createRichLabel(const std::string& value, 
		const std::string& fontName, 
		int fontSize, 
		uint8_t red, 
		uint8_t green, 
		uint8_t blue);
	std::unique_ptr<ILabel> createProxyLabel(int timeout = 5);
	std::unique_ptr<LabelAbstraction> createHelpLabel(std::unique_ptr<Label> l, const std::string& helpText);

};
