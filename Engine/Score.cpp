#include "Score.h"

void Score::update()
{
	int subNum1;
	int subNum2;
	subNum1 = total % 1000;
	thousands = (total - subNum1) / 1000;
	subNum2 = total - (1000 * thousands);
	subNum1 = subNum2 % 100;
	hundreds = (subNum2 - subNum1) / 100;
	subNum2 = subNum2 - (100 * hundreds);
	subNum1 = subNum2 % 10;
	tens = (subNum2 - subNum1) / 10;
	subNum2 = subNum2 - (10 * tens);
	ones = subNum2;
}
