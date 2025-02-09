#include <iostream>

#include "LabelPrinter.h"

void LabelPrinter::print(ILabel& l)
{
	std::cout << "Here is a label: " << l.getText() << "\n";
}

void LabelPrinter::printWithHelpText(const LabelAbstraction& l)
{
	std::cout << "Label: " << l.getText() << "\n";
	std::cout << "Help: " << l.getHelpText() << "\n";
}
