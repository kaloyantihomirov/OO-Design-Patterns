#include "Decorate.h"

std::string Decorate::transform(const std::string& text) const
{
	return std::string("-={ ") + text + " }=-";
}

bool Decorate::operator==(const TextTransformation& other) const
{
	const Decorate* ptr = dynamic_cast<const Decorate*>(&other);

	return ptr;
}
