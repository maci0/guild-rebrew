// FUNCTION: GOLDTL 0x41e4d0

void __cdecl fcn_0041e4d0(int* p, int* cnt, int* s0, int* s1, unsigned int* avg)
{
	int c;
	int a;
	int b;
	unsigned int d;

	c = 0;
	a = 0;
	b = 0;
	d = 0;
	for (; p != 0; p = (int*) p[3]) {
		c++;
		a += p[0];
		b += p[1];
		d += p[2];
	}
	if (c > 0) {
		d /= c;
	}
	if (cnt != 0) {
		*cnt = c;
	}
	if (s0 != 0) {
		*s0 = a;
	}
	if (s1 != 0) {
		*s1 = b;
	}
	if (avg != 0) {
		*avg = d;
	}
}
