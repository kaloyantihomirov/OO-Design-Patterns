#pragma once

#include <string>

#include "ColourRGB.h"

namespace TextDefaults
{
	const ColourRGB DefaultColour(0, 0, 0);
	constexpr const char* DefaultFontName = "Ariel";
	constexpr int DefaultFontSize = 12;
}

struct TextStyle
{
	ColourRGB colour;
	std::string fontName;
	int fontSize;

	TextStyle(const std::string& fontName = TextDefaults::DefaultFontName,
		      int fontSize = TextDefaults::DefaultFontSize,
		      ColourRGB colour = TextDefaults::DefaultColour);

	void setFontSize(int newFontSize);
};