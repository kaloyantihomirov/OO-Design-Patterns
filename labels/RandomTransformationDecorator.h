#pragma once

#include <vector>

#include "LabelDecoratorBase.h"
#include "TextTransformation.h"

class RandomTransformationDecorator : public LabelDecoratorBase
{
	std::vector<std::shared_ptr<TextTransformation>> transformations;
public:
	RandomTransformationDecorator(
		std::shared_ptr<Label> label,
		const std::vector<std::shared_ptr<TextTransformation>>& transformations);

	std::string getText() override;

	bool operator==(const LabelDecoratorBase& other) const override;
};