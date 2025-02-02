#include <format>

#include "RichLabel.h"

RichLabel::RichLabel(const std::string& value) : Label(value)
{
}

RichLabel::RichLabel(const std::string& value, const TextStyle& ts) : Label(value), ts(ts)
{
}

RichLabel::RichLabel(const std::string& value,
	const std::string& fontName,
	int fontSize,
	const ColourRGB& colour) : Label(value), ts(fontName, fontSize, colour)
{
}

std::string RichLabel::getText() const
{
	return std::format("$$$ {} $$$, colourRGB = ({},{},{}), font = {{ {}, {} pt }}",
		value, ts.colour.r, ts.colour.g, ts.colour.r, ts.fontName, ts.fontSize);
}