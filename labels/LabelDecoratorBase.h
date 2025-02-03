#pragma once

#include <memory>

#include "Label.h"

class LabelDecoratorBase : public Label
{
protected:
	std::shared_ptr<Label> label;
public:
	LabelDecoratorBase(std::shared_ptr<Label> label);
	virtual ~LabelDecoratorBase() = default;
};