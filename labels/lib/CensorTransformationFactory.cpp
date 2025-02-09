#include "CensorTransformationFactory.h"

std::shared_ptr<TextTransformation> CensorTransformationFactory::createCensorTransformation(const std::string& censorWord)
{
	if (censorWord.length() <= 4)
	{
		if (cache.contains(censorWord))
		{
			return cache[censorWord];
		}
		else
		{
			return cache[censorWord] = std::make_shared<Censor>(censorWord);
		}
	}
	else
	{
		return std::make_shared<Censor>(censorWord);
	}
}