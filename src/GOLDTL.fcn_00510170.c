extern unsigned char* g_90e094;
extern unsigned char* g_868050;

/* ADDRESS: GOLD 0x0050ccd0 */
/* ADDRESS: GOLDTL 0x00510170 */

int __cdecl fcn_00510170(char* a)
{
	char* p;
	int i;

	if (a[0x1b1] == 0) {
		return 0;
	}
	p = ((char*)g_90e094);
	for (i = 0; i < 0x100; i++) {
		if (*p != 0 && ((char*)g_868050)[(unsigned char) *p * 0x24d] == 4 &&
		    *(int*) (p + 0x65) == *(int*) (a + 4)) {
			return 0;
		}
		p += 0xa9;
	}
	return 1;
}
