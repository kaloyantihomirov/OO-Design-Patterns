#include <stdexcept>

#include "CyclicTransformationDecorator.h"

CyclicTransformationDecorator::CyclicTransformationDecorator(
	std::shared_ptr<Label> label,
	const std::vector<std::shared_ptr<TextTransformation>>& transformations)
	: LabelDecoratorBase(label), indexator(0)
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

		this->transformations.push_back(t);
	}
}

std::string CyclicTransformationDecorator::getText()
{
	std::string text = label->getText();

	if (indexator >= transformations.size())
	{
		indexator = 0;
	}

	std::shared_ptr<TextTransformation> t = transformations[indexator++];
	return t->transform(text);
}

bool CyclicTransformationDecorator::operator==(const LabelDecoratorBase& other) const
{
	throw std::logic_error("The method or operation is not implemented.");
}