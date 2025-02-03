#pragma once

#include <string>

class TextTransformation
{
public:
	virtual std::string transform(const std::string& text) const = 0;
	virtual ~TextTransformation() = default;
};