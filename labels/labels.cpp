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

int main(int argc, char* argv[])
{
	//i want to see if it's possible to pass a nullptr when in the code
	//we expect a shared_ptr to be passed (in order to throw an exception)

	//what we want to achieve

	std::shared_ptr<Label> sl = std::make_shared<SimpleLabel>("a sample  label     ");
	std::shared_ptr<TextTransformation> rplc = std::make_shared<Replace>("label", "description");
	std::shared_ptr<TextTransformation> rplc2 = std::make_shared<Replace>("SAP", "Astea");
	std::shared_ptr<TextTransformation> rtr = std::make_shared<RightTrim>();

	//sl = std::make_shared<TextTransformationDecorator>(sl, rplc);
	sl = std::make_shared<TextTransformationDecorator>(sl, rplc2);
	sl = std::make_shared<TextTransformationDecorator>(sl, rtr);

	std::cout << sl->getText() << "|||||\n";

	auto dummyLabel = std::make_shared<SimpleLabel>("");
	auto dummyDecorator = std::make_shared<TextTransformationDecorator>(
		dummyLabel, std::make_shared<RightTrim>());
	sl = LabelDecoratorBase::removeDecoratorFrom(sl, dummyDecorator);

	std::cout << sl->getText() << "|||||\n";

	sl = std::make_shared<TextTransformationDecorator>(sl, std::make_shared<RightTrim>());

	std::cout << sl->getText() << "|||||\n";

	testCompositeTransformation();

	ProxyLabel myLabel(3);

	for (int i = 0; i < 10; i++) 
	{
		std::cout << "Label: " << myLabel.getText() << std::endl;
	}

	int result = Catch::Session().run(argc, argv);
	return result;
}


