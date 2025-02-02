#include <iostream>

#include "LabelPrinter.h"

void LabelPrinter::print(const Label& l)
{
	std::cout << "Here is a label: " << l.getText() << "\n";
}