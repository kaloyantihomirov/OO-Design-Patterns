#include <stdexcept>
#include <random>

#include "RandomTransformationDecorator.h"

RandomTransformationDecorator::RandomTransformationDecorator(
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
	}

	this->transformations = transformations;
}

std::string RandomTransformationDecorator::getText() const
{
	std::string text = label->getText();

	static std::random_device rd;
	static std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(0, transformations.size() - 1);
	int index = dist(engine);

	return transformations[index]->transform(text);
}

bool RandomTransformationDecorator::operator==(const LabelDecoratorBase& other) const
{
	throw std::logic_error("The method or operation is not implemented.");
}