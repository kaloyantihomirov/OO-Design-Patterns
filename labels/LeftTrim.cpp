#include "LeftTrim.h"

std::string LeftTrim::transform(const std::string& text) const
{
	if (text.empty()) return text;

	size_t i = 0;
	while (i < text.size() && std::isspace(text[i])) ++i;
	return text.substr(i);
}