#pragma once

#include "Label.h"

class ProxyLabel : public Label
{
	mutable std::unique_ptr<Label> realLabel;
	mutable std::string cache;
	mutable bool initialised;
	mutable int requestCount;
	int timeout;
public:
	ProxyLabel(int timeout = 5);

	std::string getText() const override;
};