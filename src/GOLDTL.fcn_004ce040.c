// FUNCTION: GOLDTL 0x4ce040
// SIZE: 60

char* __cdecl fcn_004ce040(void)
{
	int n;
	int m;

	n = *(int*) 0x772e8c;
	m = *(int*) 0x9ba9f4;
	if (n == m) {
		return 0;
	}
	n++;
	*(int*) 0x772e8c = n;
	if (n == m) {
		return 0;
	}
	if (n == 0xf) {
		n = 0;
		*(int*) 0x772e8c = n;
	}
	return (char*) (0x9ba3a0 + n * 108);
}
