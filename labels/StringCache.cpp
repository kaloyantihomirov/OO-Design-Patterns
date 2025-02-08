#include "StringCache.h"

StringCache::StringCache(std::istream& in) : in(in)
{
}

std::string StringCache::getText() 
{
	if (!initialised)
	{
		std::cout << "Enter label text: ";
		std::getline(in, cache);
		initialised = true;
		return cache;
	}

	return cache;
}

