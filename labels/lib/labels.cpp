#include <iostream>
#include <memory>
#include <vector>

#include "LabelPrinter.h"
#include "SimpleLabel.h"
#include "RichLabel.h"
#include "CapitaliseTransformation.h"
#include "TextTransformationDecorator.h"
#include "NormaliseSpace.h"
#include "RightTrim.h"
#include "Censor.h"
#include "CompositeTransformation.h"
#include "Decorate.h"
#include "Replace.h"

#include "catch_amalgamated.hpp"
#include "HelpLabel.h"
#include "LeftTrim.h"
#include "ProxyLabel.h"

void testCensor()
{
	std::shared_ptr<Label> sl = std::make_shared<SimpleLabel>("usi usi usiusiusi usA usxDA");
	std::shared_ptr<TextTransformation> rplc = std::make_shared<Replace>("usi", "KOKI4A");

	std::shared_ptr<Label> ttd = std::make_shared<TextTransformationDecorator>(sl, rplc);

	std::cout << ttd->getText() << "|||||\n";
}

void testDecorators()
{
	std::shared_ptr<Label> sp = std::make_shared<SimpleLabel>("i   iaM a very simple label@      ");
	std::shared_ptr<Label> rl = std::make_shared<RichLabel>("RICHNESA@14");

	std::cout << sp->getText() << "|||||||\n";
	LabelPrinter::print(*sp);
	LabelPrinter::print(*rl);

	std::shared_ptr<TextTransformation> ct = std::make_shared<CapitaliseTransformation>();
	std::shared_ptr<TextTransformation> nrm = std::make_shared<NormaliseSpace>();

	std::shared_ptr<Label> ttd = std::make_shared<TextTransformationDecorator>(sp, ct);
	//ttd = std::make_shared<TextTransformationDecorator>(ttd, nrm);
	auto c = std::make_shared<Censor>("aM");

	std::cout << "Transformed: " << ttd->getText() << "||||\n";

	ttd = std::make_shared<TextTransformationDecorator>(ttd, std::make_shared<RightTrim>());
	ttd = std::make_shared<TextTransformationDecorator>(ttd, c);
	std::cout << "Transformed: " << ttd->getText() << "||||\n";
	std::cout << "\n\n";
}

void testCompositeTransformation()
{
	std::shared_ptr<TextTransformation> capitalise = std::make_shared<CapitaliseTransformation>();
	std::shared_ptr<TextTransformation> decorate = std::make_shared<Decorate>();
	std::shared_ptr<TextTransformation> replace = std::make_shared<Replace>("abc", "def");
	std::shared_ptr<TextTransformation> normaliseSpace = std::make_shared<NormaliseSpace>();

	std::shared_ptr<Label> sl = std::make_shared<SimpleLabel>("abc  def");

	std::vector<std::shared_ptr<TextTransformation>> trans1;
	trans1.push_back(capitalise);
	trans1.push_back(decorate);
	trans1.push_back(replace);

	std::vector<std::shared_ptr<TextTransformation>> trans2;
	trans2.push_back(replace);
	trans2.push_back(capitalise);
	trans2.push_back(decorate);

	std::shared_ptr<TextTransformation> comp1 = std::make_shared<CompositeTransformation>(trans1);
	std::shared_ptr<TextTransformation> comp2 = std::make_shared<CompositeTransformation>(trans2);

	//sl = std::make_shared<TextTransformationDecorator>(sl, comp2);
	//sl = std::make_shared<TextTransformationDecorator>(sl, comp1);

	std::vector<std::shared_ptr<TextTransformation>> trans3;
	trans3.push_back(comp1);
	trans3.push_back(normaliseSpace);

	std::shared_ptr<TextTransformation> comp3 = std::make_shared<CompositeTransformation>(trans3);

	sl = std::make_shared<TextTransformationDecorator>(sl, comp3);

	std::cout << sl->getText() << "\n";
}

void removeDecorator()
{
	std::shared_ptr<TextTransformation> rplc = std::make_shared<Censor>("abc");
	std::shared_ptr<TextTransformation> ltr = std::make_shared<LeftTrim>();
	std::shared_ptr<TextTransformation> nrm = std::make_shared<NormaliseSpace>();
	std::shared_ptr<TextTransformation> notApplied = std::make_shared<RightTrim>();

	std::shared_ptr<Label> lbl = std::make_shared<SimpleLabel>(" abc  daf");

	lbl = std::make_shared<TextTransformationDecorator>(lbl, rplc);
	lbl = std::make_shared<TextTransformationDecorator>(lbl, ltr);
	lbl = std::make_shared<TextTransformationDecorator>(lbl, nrm);

	//std::shared_ptr<LabelDecoratorBase> dummy = std::make_shared<TextTransformationDecorator>(lbl, notApplied);
	//std::shared_ptr<LabelDecoratorBase> dummy = std::make_shared<TextTransformationDecorator>(lbl, rplc);
	std::shared_ptr<LabelDecoratorBase> dummy = std::make_shared<TextTransformationDecorator>(lbl, nrm);

	lbl = LabelDecoratorBase::removeDecoratorFrom(lbl, dummy);

	std::cout << lbl->getText() << "\n";
}

void testHelpLabel()
{
	std::unique_ptr<ILabel> simple = std::make_unique<SimpleLabel>("Hello World");
	std::unique_ptr<ILabel> rl = std::make_unique<RichLabel>("rich", "Ariel", 14, ColourRGB(0, 0, 0));
	std::unique_ptr<ILabel> cl = std::make_unique<ProxyLabel>(5);

	HelpLabel helpLabel(std::move(simple), "This label displays a greeting.");
	HelpLabel helpLabel2(std::move(rl), "This is a rich label, displaying a black text.");
	HelpLabel helpLabel3(std::move(cl), "This is a custom proxy label.");

	LabelPrinter::printWithHelpText(helpLabel);
	std::cout << "\n";
	LabelPrinter::printWithHelpText(helpLabel2);
	std::cout << "\n";
	LabelPrinter::printWithHelpText(helpLabel3);
}

int main(int argc, char* argv[])
{
	//testCompositeTransformation();
	//testHelpLabel();
	removeDecorator();

	int result = Catch::Session().run(argc, argv);
	return result;
}


