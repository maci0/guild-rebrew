/* ADDRESS: GOLDTL 0x0043bf20 */
void __cdecl fcn_0043bf20(char* a)
{
	int i;
	int j;
	char* p;

	a[0x8036] |= 1;
	p = a + 0x28f;
	for (j = 0; j < 8; j++) {
		for (i = 0; i < 8; i++) {
			*p = (char) 0xff;
			p += 0x1f4;
		}
	}
}
