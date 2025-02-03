#include "RightTrim.h"

std::string RightTrim::transform(const std::string& text) const
{
	if (text.empty()) return text;

	size_t i = text.size();
	while (i > 0 && std::isspace(text[i - 1])) --i;
	return text.substr(0, i);
}