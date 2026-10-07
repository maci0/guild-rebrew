// FUNCTION: GOLD 0x004bc670
// FUNCTION: GOLDTL 0x4bcc50

char* __cdecl fcn_004bcc50(char* a1, int a2)
{
	char* p;
	int i;

	for (i = 0, p = a1; i < 0x40; i++, p += 0x18) {
		if (p[0xd] != (char) 0xff) {
			if (*(int*) p == a2) {
				return a1 + i * 0x18;
			}
		}
	}
	return 0;
}
