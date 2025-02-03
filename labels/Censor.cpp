#include "Censor.h"

Censor::Censor(const std::string& wordToCensor, char replaceWith) 
	: wordToCensor(wordToCensor),
	  replaceWith(replaceWith)
{
}

std::string Censor::transform(const std::string& text) const
{
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