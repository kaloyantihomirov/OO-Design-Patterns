#include <stdexcept>

#include "TextTransformationDecorator.h"

TextTransformationDecorator::TextTransformationDecorator(
	std::shared_ptr<Label> label,
	std::shared_ptr<TextTransformation> textTransformation)
	: LabelDecoratorBase(label)
{
	if (!textTransformation)
	{
		throw std::invalid_argument("TextTransformation cannot be nullptr");
	}

	this->textTransformation = textTransformation;
}

std::string TextTransformationDecorator::getText() const
{
	return textTransformation->transform(label->getText());
}

bool TextTransformationDecorator::operator==(const LabelDecoratorBase& other) const
{
	const TextTransformationDecorator* otherDecorator =
		dynamic_cast<const TextTransformationDecorator*>(&other);

	if (!otherDecorator)
	{
		return false;
	}

	return (*textTransformation == *(otherDecorator->textTransformation));
}