#include "CapitaliseTransformation.h"
#include "TextUtil.h"

std::string CapitaliseTransformation::transform(const std::string& text) const
{
	if (text.empty() || !TextUtil::isLetterLowercase(text[0])) return text;

	return TextUtil::toUppercase(text[0]) + text.substr(1);
}

bool CapitaliseTransformation::operator==(const TextTransformation& other) const
{
	const CapitaliseTransformation* ptr = dynamic_cast<const CapitaliseTransformation*>(&other);

	return ptr;
}
