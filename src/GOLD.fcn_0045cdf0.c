/* ADDRESS: GOLD 0x0045cdf0 */
/* GOLD twin of GOLDTL fcn_00456df0: entity slots at 0x754, 0x80 bytes each
 * (GOLDTL 0x1384, 0x9c); flag bit 4 of byte 0x211 (GOLDTL bit 1 of 0x215). */
void __cdecl fcn_0045cdf0(char* a)
{
	int i;

	if ((a[0x211] & 4) != 0 && *(char**) (a + 0x1ec) != 0) {
		for (i = 0; i < 4; i++) {
			if (*(int*) (*(char**) (a + 0x1ec) + i * 0x80 + 0x754) != 0) {
				*(int*) (*(char**) (a + 0x1ec) + i * 0x80 + 0x76c) = 0;
				*(int*) (*(char**) (a + 0x1ec) + i * 0x80 + 0x770) = 0;
				*(int*) (*(char**) (a + 0x1ec) + i * 0x80 + 0x774) = 0;
			}
		}
	}
}
