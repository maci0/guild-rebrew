// FUNCTION: GOLDTL 0x4c5530
// SIZE: 74

void __cdecl fcn_004c4df0(int, int);

void __cdecl fcn_004c5530(int a1)
{
	char buf[0x9c];
	int i;
	int* p;

	buf[0] = 0x1c;
	p = (int*) (a1 + 0x38);
	for (i = 8; i != 0; i--) {
		if (*p == 0) {
			*p = -1;
		}
		p++;
	}
	fcn_004c4df0(0xf8, a1);
	fcn_004c4330(buf);
}
