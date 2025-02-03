#include <stdexcept>

#include "CyclicTransformationDecorator.h"

CyclicTransformationDecorator::CyclicTransformationDecorator(
	std::shared_ptr<Label> label,
	const std::vector<std::shared_ptr<TextTransformation>>& transformations)
	: LabelDecoratorBase(label)
{
	if (transformations.empty())
	{
		throw std::invalid_argument("No transformations provided");
	}

	for (const auto& t : transformations)
	{
		this->transformations.push(t);
	}
}

std::string CyclicTransformationDecorator::getText() const
{
	std::string text = label->getText();
	std::shared_ptr<TextTransformation> t = transformations.front();

	transformations.pop();
	transformations.push(t);

	return t->transform(text);
}