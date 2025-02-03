#include <stdexcept>

#include "LabelDecoratorBase.h"

LabelDecoratorBase::LabelDecoratorBase(std::shared_ptr<Label> label) 
	: Label("")
{
	if (!label)
	{
		throw std::invalid_argument("Label cannot be nullptr");
	}

	this->label = label;
}