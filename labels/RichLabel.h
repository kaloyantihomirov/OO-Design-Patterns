#pragma once

#include "Label.h"
#include "ColourRGB.h"
#include "TextStyle.h"

class RichLabel : public Label
{
public:
	TextStyle textStyle;

	RichLabel(const std::string& value);
	RichLabel(const std::string& value, const TextStyle& textStyle);
	RichLabel(const std::string& value,
		      const std::string& fontName,
		      int fontSize,
		      const ColourRGB& colour);

	std::string getText() const override;
};