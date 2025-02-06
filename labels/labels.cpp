#include <iostream>
#include <memory>

#include "LabelPrinter.h"
#include "SimpleLabel.h"
#include "RichLabel.h"
#include "CapitaliseTransformation.h"
#include "TextTransformationDecorator.h"
#include "NormaliseSpace.h"
#include "RightTrim.h"
#include "Censor.h"
#include "Replace.h"

void testCensor()
{
    std::shared_ptr<Label> sl = std::make_shared<SimpleLabel>("usi usi usiusiusi usA usxDA");
    std::shared_ptr<TextTransformation> rplc = std::make_shared<Replace>("usi", "KOKI4A");

    std::shared_ptr<Label> ttd = std::make_shared<TextTransformationDecorator>(sl, rplc);

    std::cout << ttd->getText() << "|||||\n";
}

void testDecorators()
{
    LabelPrinter lp;
    std::shared_ptr<Label> sp = std::make_shared<SimpleLabel>("i   iaM a very simple label@      ");
    std::shared_ptr<Label> rl = std::make_shared<RichLabel>("RICHNESA@14");

    std::cout << sp->getText() << "|||||||\n";
    lp.print(*sp);
    lp.print(*rl);

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

int main2()
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
    return 0;
}
