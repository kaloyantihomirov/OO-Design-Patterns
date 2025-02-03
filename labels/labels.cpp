#include <iostream>
#include <memory>

#include "LabelPrinter.h"
#include "SimpleLabel.h"
#include "RichLabel.h"
#include "CapitaliseTransformation.h"
#include "TextTransformationDecorator.h"
#include "NormaliseSpace.h"

int main()
{
    LabelPrinter lp;
    auto sp = std::make_shared<SimpleLabel>("i   iaM a very simple label@");
    auto rl = std::make_shared<RichLabel>("RICHNESA@14");

    lp.print(*sp); 
    lp.print(*rl);

    auto ct = std::make_shared<CapitaliseTransformation>();
	auto nrm = std::make_shared<NormaliseSpace>();

    auto ttd = std::make_shared<TextTransformationDecorator>(sp, ct);
	ttd = std::make_shared<TextTransformationDecorator>(ttd, nrm);

    std::cout << "Transformed: " << ttd->getText() << std::endl;

    return 0;
}
