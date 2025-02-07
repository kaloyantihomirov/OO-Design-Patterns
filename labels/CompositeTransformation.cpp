#include <stdexcept>

#include "CompositeTransformation.h"

CompositeTransformation::CompositeTransformation(const std::vector<std::shared_ptr<TextTransformation>>& transformations)
	
{
	for (const auto& spt : transformations)
	{
		if (!spt)
		{
			throw std::invalid_argument("Transformation cannot be nullptr");
		}
	}

	this->transformations = transformations;
}

std::string CompositeTransformation::transform(const std::string& text) const
{
	//transformations [ pt1, pt2, pt3, pt4, ... ptn] , n >= 0
	//pti != nullptr (we throw an exception in the ctor if that is the case for some i)

	std::string res = text;
	for (const auto& pt : transformations)
	{
		res = pt->transform(res);
	}
	return res;
}

bool CompositeTransformation::operator==(const TextTransformation& other) const
{
	const CompositeTransformation* pct = dynamic_cast<const CompositeTransformation*>(&other);

	if (!pct)
	{
		return false;
	}

	if (pct->transformations.size() != this->transformations.size()) return false;

	for (size_t i = 0; i < this->transformations.size(); i++)
	{
		if (!(*(this->transformations[i]) == *pct->transformations[i])) 
		{
			return false;
		}
	}

	return true;
}