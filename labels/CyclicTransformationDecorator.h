#pragma once

#include <queue>

#include "LabelDecoratorBase.h"
#include "TextTransformation.h"

class CyclicTransformationDecorator : public LabelDecoratorBase
{
	mutable std::queue<std::shared_ptr<TextTransformation>> transformations;
public:
	CyclicTransformationDecorator(
		std::shared_ptr<Label> label,
		const std::vector<std::shared_ptr<TextTransformation>>& transformations);

	std::string getText() const override;

	bool operator==(const LabelDecoratorBase& other) const override;
};