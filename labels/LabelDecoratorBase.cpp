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

// Static helper: given any label, if it is decorated,
// try to remove the decorator that equals the provided one.
std::shared_ptr<Label> LabelDecoratorBase::removeDecoratorFrom(
    std::shared_ptr<Label> label,
    std::shared_ptr<LabelDecoratorBase> decoratorToRemove)
{
    if (!label)
    {
        return label;
    }

    // Check if label is a decorator.
    auto decorator = std::dynamic_pointer_cast<LabelDecoratorBase>(label);

    if (decorator)
    {
        // Delegate to the non-static removal function.
        return decorator->removeDecorator(decoratorToRemove);
    }
    else
    {
        // Not a decorator: nothing to remove.
        return label;
    }
}

// Non-static function: try to remove the decorator from the chain.
// If the current decorator is equal to decoratorToRemove,
// return the wrapped label (thus “removing” this decorator).
// Otherwise, if the wrapped label is itself a decorator,
// delegate the removal further down the chain.
std::shared_ptr<Label> LabelDecoratorBase::removeDecorator(
    std::shared_ptr<LabelDecoratorBase> decoratorToRemove)
{
    // Check if this decorator equals the decorator we want to remove.
    if (*this == *decoratorToRemove)
    {
        // Remove this decorator by returning its subject.
        return label;
    }
    else
    {
        // Otherwise, see if the wrapped label is itself a decorator.
        auto innerDecorator = std::dynamic_pointer_cast<LabelDecoratorBase>(label);
        if (innerDecorator)
        {
            // Remove from the inner chain, and update our subject.
            label = innerDecorator->removeDecorator(decoratorToRemove);
        }
        // Return this decorator (unchanged) if we didn't remove it.
        return std::static_pointer_cast<Label>(shared_from_this());
        // Note: if you do not use enable_shared_from_this, you might simply return label.
        // But then the chain may be broken if you expected the top decorator to be retained.
    }
}