// FUNCTION: GOLD 0x004bc640
// SIZE: 45
// FUNCTION: GOLDTL 0x4bcc20
// SIZE: 45

char* __cdecl fcn_004bcc20(char* a1, int a2)
{
	char* p;
	int i;

	for (i = 0, p = a1 + 0x14; i < 0x40; i++, p += 0x18) {
		if (p[-7] != (char) 0xff) {
			if (*(int*) p == a2) {
				return a1 + i * 0x18;
			}
		}
	}
	return 0;
}
