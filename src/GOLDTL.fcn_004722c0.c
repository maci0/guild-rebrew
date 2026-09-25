// FUNCTION: GOLDTL 0x4722c0
// SIZE: 184
int __cdecl fcn_004722c0(char* p)
{
	int r;
	int d;

	r = 1;
	d = *(int*) (p + 0x18) - *(int*) (p + 0x1c);
	if (d >= 125000) {
		r = 10000;
	} else if (d >= 100000) {
		r = 5000;
	} else if (d >= 75000) {
		r = 4000;
	} else if (d >= 50000) {
		r = 3000;
	} else if (d >= 37500) {
		r = 2000;
	} else if (d >= 25000) {
		r = 1500;
	} else if (d >= 12500) {
		r = 1000;
	} else if (d >= 5000) {
		r = 500;
	} else if (d >= 2500) {
		r = 200;
	} else if (d >= 1000) {
		r = 100;
	} else if (d >= 250) {
		r = 50;
	} else if (d >= 100) {
		r = 10;
	}
	return r;
}
