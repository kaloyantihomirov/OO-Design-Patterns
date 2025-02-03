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

int main()
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
	testCensor();
    return 0;
}
