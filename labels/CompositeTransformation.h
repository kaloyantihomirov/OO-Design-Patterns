#pragma once

#include <vector>
#include <memory>

#include "TextTransformation.h"

class CompositeTransformation : public TextTransformation
{
	std::vector<std::shared_ptr<TextTransformation>> transformations;
public:
	CompositeTransformation(const std::vector<std::shared_ptr<TextTransformation>>& transformations);
	std::string transform(const std::string& text) const override;
	bool operator==(const TextTransformation& other) const override;
};