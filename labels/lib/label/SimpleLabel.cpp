#include "SimpleLabel.h"

SimpleLabel::SimpleLabel(const std::string& value) : Label(value)
{
}

std::string SimpleLabel::getText()  
{
	return this->value;
}