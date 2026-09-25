// FUNCTION: GOLD 0x00440140
// SIZE: 47
void __cdecl fcn_00440140(char* a)
{
	int i;
	int j;
	char* p;

	a[0x1c70] |= 1;
	p = a + 0x13f;
	for (j = 0; j < 8; j++) {
		for (i = 0; i < 8; i++) {
			*p = (char) 0xff;
			p += 0x64;
		}
	}
}
