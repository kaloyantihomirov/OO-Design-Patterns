#include <iostream>

#include "ProxyLabel.h"
#include "SimpleLabel.h"

ProxyLabel::ProxyLabel(int timeout, std::istream& in, std::ostream& out) : realLabel(nullptr), requestCount(0), timeout(timeout),
	in(in), out(out)
{
}

std::string ProxyLabel::getText()
{
	if (!realLabel)
	{
		std::string value;
		out << "Please, enter label value: ";
		std::getline(in, value);
		realLabel = std::make_unique<SimpleLabel>(value);
		requestCount = 1;
		return realLabel->getText();
	}

	requestCount++;

	if (requestCount > timeout)
	{
		out << "Label text requested " << requestCount
			<< " times. Do you want to update label text? (y/n): ";
		char response;
		in >> response;
		in.ignore(); 
		if (response == 'y' || response == 'Y')
		{
			out << "Enter new label value: ";
			std::string newValue;
			std::getline(in, newValue);

			realLabel = std::make_unique<SimpleLabel>(newValue);
		}

		requestCount = 0;
	}

	return realLabel->getText();
}