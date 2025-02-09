#include "LabelAbstraction.h"

LabelAbstraction::LabelAbstraction(std::unique_ptr<ILabel> l) : label(std::move(l))
{
}

std::string LabelAbstraction::getText() const
{
	return label->getText();
}

std::string LabelAbstraction::getHelpText() const
{
	return "";
}