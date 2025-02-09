#pragma once

#include <queue>

#include "LabelDecoratorBase.h"
#include "TextTransformation.h"

class CyclicTransformationDecorator : public LabelDecoratorBase
{
	std::vector<std::shared_ptr<TextTransformation>> transformations;
	size_t indexator;
public:
	CyclicTransformationDecorator(
		std::shared_ptr<Label> label,
		const std::vector<std::shared_ptr<TextTransformation>>& transformations);

	std::string getText() override;

	bool operator==(const LabelDecoratorBase& other) const override;
};