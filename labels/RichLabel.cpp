#include <format>

#include "RichLabel.h"

RichLabel::RichLabel(const std::string& value) : Label(value)
{
}

RichLabel::RichLabel(const std::string& value, const TextStyle& textStyle) : Label(value), textStyle(textStyle)
{
}

RichLabel::RichLabel(const std::string& value,
	const std::string& fontName,
	int fontSize,
	const ColourRGB& colour) : Label(value), textStyle(fontName, fontSize, colour)
{
}

std::string RichLabel::getText()
{
	return std::format("$$$ {} $$$, colourRGB = ({},{},{}), font = {{ {}, {} pt }}",
		value, 
		textStyle.colour.r,
		textStyle.colour.g,
		textStyle.colour.b,
		textStyle.fontName,
		textStyle.fontSize);
}