#include "LabelDecoratorBase.h"

LabelDecoratorBase::LabelDecoratorBase(std::shared_ptr<Label> label) 
	: Label(""), label(label)
{
}