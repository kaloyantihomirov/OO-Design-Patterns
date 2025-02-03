#pragma once

#include "LabelDecoratorBase.h"
#include "TextTransformation.h"

class TextTransformationDecorator : public LabelDecoratorBase
{
	std::shared_ptr<TextTransformation> textTransformation;
public:
	TextTransformationDecorator(
		std::shared_ptr<Label> label,
		std::shared_ptr<TextTransformation> textTransformation);

	std::string getText() const override;

	bool operator==(const LabelDecoratorBase& other) const override;
};