#pragma once

#include <iostream>

#include "Label.h"

class ProxyLabel : public ILabel
{
	std::unique_ptr<Label> realLabel;
	int requestCount;
	int timeout;

	std::istream& in;
	std::ostream& out;
public:
	ProxyLabel(int timeout = 5, std::istream& in = std::cin, std::ostream& out = std::cout);

	std::string getText() override;
};
