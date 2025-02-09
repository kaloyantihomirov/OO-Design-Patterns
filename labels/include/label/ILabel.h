#pragma once

#include <string>

class ILabel
{
public:
	virtual std::string getText() = 0;
	virtual ~ILabel() = default;
};