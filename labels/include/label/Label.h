#pragma once

#include <string>

#include "ILabel.h"

class Label : public ILabel
{
protected:
	std::string value;
public:
	Label(const std::string&);
	virtual std::string getText() override = 0;
	virtual ~Label()  = default;
};
