#include "HelpLabel.h"

HelpLabel::HelpLabel(std::unique_ptr<ILabel> l, const std::string& helpText)
	: LabelAbstraction(std::move(l)), helpText(helpText)
{
}

std::string HelpLabel::getHelpText() const
{
	return helpText;
}

