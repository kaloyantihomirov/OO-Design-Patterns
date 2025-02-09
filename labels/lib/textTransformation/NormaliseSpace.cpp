#include "NormaliseSpace.h"

std::string NormaliseSpace::transform(const std::string& text) const
{
	if (text.empty()) return text;

	std::string result;
	result.reserve(text.size());
	bool lastWasSpace = false;

	for (char c : text)
	{
		if (std::isspace(c))
		{
			if (!lastWasSpace)
			{
				result.push_back(' ');
				lastWasSpace = true;
			}
		}
		else
		{
			result.push_back(c);
			lastWasSpace = false;
		}
	}

	return result;
}

bool NormaliseSpace::operator==(const TextTransformation& other) const
{
	const NormaliseSpace* ptr = dynamic_cast<const NormaliseSpace*>(&other);

	return ptr;
}
