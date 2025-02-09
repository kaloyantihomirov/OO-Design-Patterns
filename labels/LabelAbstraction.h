#pragma once

#include <memory>

#include "Label.h"

class LabelAbstraction
{
	std::unique_ptr<ILabel> label;
public:
	LabelAbstraction(std::unique_ptr<ILabel> l);
	virtual std::string getText() const;
	virtual std::string getHelpText() const;
	virtual ~LabelAbstraction() = default;
};
