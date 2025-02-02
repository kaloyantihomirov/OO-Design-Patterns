#pragma once

#include "Label.h"

class SimpleLabel : public Label
{
public:
	SimpleLabel(const std::string&);
	std::string getText() const override;
};