#pragma once

#include "TextTransformation.h"

class Censor : public TextTransformation
{
	std::string wordToCensor;
	char replaceWith;
public:
	Censor(const std::string& wordToCensor, char replaceWith = '*');
	std::string transform(const std::string& text) const override;
	bool operator==(const TextTransformation& other) const override;
};