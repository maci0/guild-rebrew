/* ADDRESS: GOLDTL 0x00456df0 */
void __cdecl fcn_00456df0(char* a)
{
	int i;

	if ((a[0x215] & 1) != 0 && *(char**) (a + 0x1ec) != 0) {
		for (i = 0; i < 4; i++) {
			if (*(int*) (*(char**) (a + 0x1ec) + i * 0x9c + 0x1384) != 0) {
				*(int*) (*(char**) (a + 0x1ec) + i * 0x9c + 0x13a0) = 0;
				*(int*) (*(char**) (a + 0x1ec) + i * 0x9c + 0x13a4) = 0;
				*(int*) (*(char**) (a + 0x1ec) + i * 0x9c + 0x13a8) = 0;
			}
		}
	}
}
