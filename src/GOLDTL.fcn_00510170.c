extern char* g_90e094;
extern char* g_868050;

// FUNCTION: GOLD 0x0050ccd0
// SIZE: 102
// FUNCTION: GOLDTL 0x510170
// SIZE: 102

int __cdecl fcn_00510170(char* a)
{
	char* p;
	int i;

	if (a[0x1b1] == 0) {
		return 0;
	}
	p = g_90e094;
	for (i = 0; i < 0x100; i++) {
		if (*p != 0 && g_868050[(unsigned char) *p * 0x24d] == 4 &&
		    *(int*) (p + 0x65) == *(int*) (a + 4)) {
			return 0;
		}
		p += 0xa9;
	}
	return 1;
}
