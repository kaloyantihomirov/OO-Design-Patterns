#include <iostream>

#include "ProxyLabel.h"

ProxyLabel::ProxyLabel(int timeout) : Label(""), initialised(false), requestCount(0), timeout(timeout)
{
}

std::string ProxyLabel::getText() const
{
	if (!initialised)
	{
		std::cout << "Enter label text: ";
		std::getline(std::cin, cache);

		initialised = true;
		requestCount = 1;
		return cache;
	}

	requestCount++;

	if (requestCount >= timeout)
	{
		std::cout << "Label text requested " << requestCount << " times. Do you want to update label text? (y/n): ";
		char response;
		std::cin >> response;
		std::cin.ignore();

		if (response == 'y' || response == 'Y')
		{
			std::cout << "Enter new label text: ";
			std::getline(std::cin, cache);
		}

		requestCount = 0;
	}

	return cache;
}

