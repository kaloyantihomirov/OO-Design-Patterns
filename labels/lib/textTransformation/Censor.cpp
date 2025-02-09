#include "Censor.h"

Censor::Censor(const std::string& wordToCensor, char replaceWith) 
	: wordToCensor(wordToCensor),
	  replaceWith(replaceWith)
{
}

std::string Censor::transform(const std::string& text) const
{
	if (wordToCensor.empty())
	{
		return text;
	}

	std::string result = text;
	size_t pos = 0;
	const size_t wordToCensorLength = wordToCensor.length();

	while ((pos = result.find(wordToCensor, pos)) != std::string::npos)
	{
		result.replace(pos, wordToCensorLength, std::string(wordToCensorLength, replaceWith));
		pos += wordToCensorLength;
	}

	return result;
}

bool Censor::operator==(const TextTransformation& other) const
{
	const Censor* otherCensor = dynamic_cast<const Censor*>(&other);

	if (!otherCensor)
	{
		return false;
	}

	return wordToCensor == otherCensor->wordToCensor &&
		replaceWith == otherCensor->replaceWith;
}