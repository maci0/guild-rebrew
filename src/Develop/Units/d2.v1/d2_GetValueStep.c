/* ADDRESS: GOLDTL 0x004722c0 */
int __cdecl d2_GetValueStep(char* element)
{
	int step;
	int value_range;

	step = 1;
	value_range = *(int*) (element + 0x18) - *(int*) (element + 0x1c);
	if (value_range >= 125000) {
		step = 10000;
	} else if (value_range >= 100000) {
		step = 5000;
	} else if (value_range >= 75000) {
		step = 4000;
	} else if (value_range >= 50000) {
		step = 3000;
	} else if (value_range >= 37500) {
		step = 2000;
	} else if (value_range >= 25000) {
		step = 1500;
	} else if (value_range >= 12500) {
		step = 1000;
	} else if (value_range >= 5000) {
		step = 500;
	} else if (value_range >= 2500) {
		step = 200;
	} else if (value_range >= 1000) {
		step = 100;
	} else if (value_range >= 250) {
		step = 50;
	} else if (value_range >= 100) {
		step = 10;
	}
	return step;
}
