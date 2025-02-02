#include "LabelPrinter.h"
#include "SimpleLabel.h"
#include "RichLabel.h"

int main()
{
	LabelPrinter lp;
	SimpleLabel sp("@i am a very simple label@");
	RichLabel rl("RICHNESA@14");


	lp.print(sp);
	lp.print(rl);
	return 0;
}