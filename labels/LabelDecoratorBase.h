#pragma once

#include <memory>

#include "Label.h"

class LabelDecoratorBase : public Label, public std::enable_shared_from_this<LabelDecoratorBase>
{
protected:
	std::shared_ptr<Label> label;
public:
	LabelDecoratorBase(std::shared_ptr<Label> label);

	static std::shared_ptr<Label> removeDecoratorFrom(
		std::shared_ptr<Label> label,
		std::shared_ptr<LabelDecoratorBase> decoratorToRemove);
	std::shared_ptr<Label> removeDecorator(std::shared_ptr<LabelDecoratorBase> decoratorToRemove);

	virtual bool operator==(const LabelDecoratorBase& other) const = 0;

	virtual ~LabelDecoratorBase() = default;
};