// FUNCTION: GOLDTL 0x57fc80
// SIZE: 93

int __cdecl fcn_0057fc80(void)
{
	unsigned short* p;
	unsigned short k;
	int v;
	int m;

	p = *(unsigned short**) 0x7746cc;
	if (p != 0) {
		k = *p;
		v = k;
		if (v >= 0x92 && v <= 0x97) {
			m = *(int*) (*(int*) 0x665f08 + 0x38);
			if (m == 0) {
				return k == 0x92 ? 0 : 3;
			}
			if (m == 1) {
				return k == 0x95 ? 1 : 4;
			}
			if (m == 2) {
				return m;
			}
		}
	}
	return -1;
}
