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

std::shared_ptr<Label> LabelDecoratorBase::removeDecoratorFrom(
    std::shared_ptr<Label> label,
    std::shared_ptr<LabelDecoratorBase> decoratorToRemove)
{
    if (!label)
    {
        return label;
    }

    auto decorator = std::dynamic_pointer_cast<LabelDecoratorBase>(label);

    if (decorator)
    {
        return decorator->removeDecorator(decoratorToRemove);
    }
    else
    {
        return label;
    }
}

//D1->D2->SL

std::shared_ptr<Label> LabelDecoratorBase::removeDecorator(
    std::shared_ptr<LabelDecoratorBase> decoratorToRemove)
{
    if (*this == *decoratorToRemove)
    {
        return label;
    }
    else
    {
        auto innerDecorator = std::dynamic_pointer_cast<LabelDecoratorBase>(label);

        if (innerDecorator)
        {
            label = innerDecorator->removeDecorator(decoratorToRemove);
        }

        //to ensure that the returned pointer shares the same reference count (control block)
        //as the pointer that originally owns the object (to avoid double deletion or premature deletion)
        return std::static_pointer_cast<Label>(shared_from_this());
    }
}