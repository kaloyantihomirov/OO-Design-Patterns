#include "Decorate.h"

std::string Decorate::transform(const std::string& text) const
{
	return std::string("-={ ") + text + " }=-";
}