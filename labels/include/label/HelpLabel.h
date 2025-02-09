#pragma once

#include "LabelAbstraction.h"

class HelpLabel : public LabelAbstraction
{
	std::string helpText;
public:
	HelpLabel(std::unique_ptr<ILabel> l, const std::string& helpText);
	std::string getHelpText() const override;
};
