#pragma once

#include <string>

class Label
{
public:
	std::string value;

	Label(const std::string&);
	virtual std::string getText() const = 0;
	~Label() = default;
};
