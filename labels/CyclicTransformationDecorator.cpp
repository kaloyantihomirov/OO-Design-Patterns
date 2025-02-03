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
		if (!t)
		{
			throw std::invalid_argument("Invalid transformation");
		}

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

bool CyclicTransformationDecorator::operator==(const LabelDecoratorBase& other) const
{
	throw std::logic_error("The method or operation is not implemented.");
}