#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "Censor.h"
#include "TextTransformation.h"

// When using this factory we're considering that the censor symbol is always '*'
class CensorTransformationFactory
{
    std::unordered_map<std::string, std::shared_ptr<Censor>> cache;

public:
    std::shared_ptr<TextTransformation> createCensorTransformation(const std::string& censorWord);
};