// FUNCTION: GOLD 0x00411bb0
// SIZE: 38
// fcn_00411bb0 — first double-zero slot in 0xfd7f74..0xfe7774 (stride 0x3e0), else -1.

int __cdecl fcn_00411bb0(void)
{
	int i;
	for (i = 0; 0xfd7f75 + i * 0x3e0 < 0xfe7775; i++) {
		char* p;
		p = (char*) (0xfd7f75 + i * 0x3e0);
		if (*(char*) (p - 1) == 0 && *p == 0) {
			return i;
		}
	}
	return -1;
}
