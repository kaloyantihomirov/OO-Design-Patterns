#include "DoubleNumsHelper.h"

#include <limits>

//only interested in upper bound overflow as negative numbers are handled before the overflow check
bool DoubleNumsHelper::willAdditionOverflow(double x, double y)
{
	constexpr double dblMax = std::numeric_limits<double>::max();

	return x > 0 && y > 0 && x > dblMax - y;

}
