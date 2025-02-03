#include "TextTransformationDecorator.h"

TextTransformationDecorator::TextTransformationDecorator(
	std::shared_ptr<Label> label,
	std::shared_ptr<TextTransformation> textTransformation)
	: LabelDecoratorBase(label), textTransformation(textTransformation)
{
}

std::string TextTransformationDecorator::getText() const
{
	return textTransformation->transform(label->getText());
}