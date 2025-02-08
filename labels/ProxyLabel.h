#pragma once

#include "Label.h"
#include "SimpleLabel.h"

class ProxyLabel : public ILabel
{
	std::unique_ptr<Label> realLabel;
	int requestCount;
	int timeout;

	std::istream& in;
	std::ostream& out;
public:
	ProxyLabel(int timeout = 5);

	std::string getText() override;
};
