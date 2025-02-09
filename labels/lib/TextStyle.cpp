#include "TextStyle.h"

TextStyle::TextStyle(const std::string& fontName,
	int fontSize,
	ColourRGB colour) : fontName(fontName), colour(colour)
{
	setFontSize(fontSize);
}

void TextStyle::setFontSize(int newFontSize)
{
	if (newFontSize <= 0)
	{
		newFontSize = TextDefaults::DefaultFontSize;
	}

	fontSize = newFontSize;
}