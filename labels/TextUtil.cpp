#include "TextUtil.h"

bool TextUtil::isLetterLowercase(char c)
{
	return c >= 'a' && c <= 'z';
}

char TextUtil::toUppercase(char c)
{
	return isLetterLowercase(c) ? c - 'a' + 'A' : c;
}