#pragma once

#include "TextTransformation.h"

class RightTrim : public TextTransformation
{
public:
	std::string transform(const std::string& text) const override;

	bool operator==(const TextTransformation&) const override;
};