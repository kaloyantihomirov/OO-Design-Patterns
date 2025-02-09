#include "Replace.h"

Replace::Replace(
    const std::string& replaceWhat,
    const std::string& replaceWithWhat)
    : replaceWhat(replaceWhat), 
      replaceWithWhat(replaceWithWhat)
{
}

std::string Replace::transform(const std::string& text) const
{
    if (replaceWhat.empty()) return text; 

    std::string result;
    size_t lastPos = 0;
    size_t pos = text.find(replaceWhat, lastPos);

    while (pos != std::string::npos)
    {
        result.append(text, lastPos, pos - lastPos);
        result.append(replaceWithWhat);
        lastPos = pos + replaceWhat.size();
        pos = text.find(replaceWhat, lastPos);
    }

    result.append(text, lastPos, text.size() - lastPos);

    return result;
}

bool Replace::operator==(const TextTransformation& other) const
{
	const Replace* otherReplace = dynamic_cast<const Replace*>(&other);

	if (!otherReplace)
	{
		return false;
	}

	return replaceWhat == otherReplace->replaceWhat &&
		replaceWithWhat == otherReplace->replaceWithWhat;
}
