// FUNCTION: GOLD 0x00468850
// SIZE: 34
// fcn_00468850 — first i with [p+4] nonzero (p from [0xf8f080], +0x2ec).

int __cdecl fcn_00468850(void)
{
	int i;
	char* p;
	p = *(char**) 0xf8f080;
	for (i = 0; i < 0x300; i++) {
		if (*(int*) (p + 4) != 0) {
			return i;
		}
		p += 0x2ec;
	}
	return -1;
}
