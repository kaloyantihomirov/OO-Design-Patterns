#pragma once

#include "Label.h"
#include "LabelAbstraction.h"

class LabelPrinter
{
public:
	static void print(ILabel&);
	static void printWithHelpText(const LabelAbstraction& l);
};