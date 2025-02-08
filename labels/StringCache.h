#pragma once

#include <iostream>
#include <string>

class StringCache
{
	std::string cache;
	bool initialised = false;
	std::istream& in;
public:
	StringCache(std::istream& = std::cin);
	std::string getText();
};