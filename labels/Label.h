#pragma once

#include <string>

class Label
{
protected:
	std::string value;
public:
	Label(const std::string&);
	virtual std::string getText() const = 0;
	virtual ~Label() = default;
};
