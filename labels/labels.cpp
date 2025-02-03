#include "LabelPrinter.h"
#include "SimpleLabel.h"
#include "RichLabel.h"

int main()
{
	LabelPrinter lp;
	SimpleLabel sp("@i am a very simple label@");
	RichLabel rl("RICHNESA@14");
	rl.textStyle.colour = ColourRGB(0, 0, 0);
	rl.textStyle.fontSize = 14;
	rl.textStyle.fontName = "Times New Roman";
	rl.value = "RICHNESS%$@";

	lp.print(sp);
	lp.print(rl);
	return 0;
}