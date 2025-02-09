#pragma once

#include <string>

#include "TextTransformation.h"

class Replace : public TextTransformation
{
	std::string replaceWhat;
	std::string replaceWithWhat;
public:
	Replace(const std::string& replaceWhat, const std::string& replaceWithWhat);
	std::string transform(const std::string& text) const override;
	bool operator==(const TextTransformation& other) const override;
};