/* ADDRESS: GOLD 0x005c0a00 */
// fcn_005c0a00 — zero pairs over 0x62d150..0x62d1f0 stride 0x14.

void __cdecl fcn_005c0a00(void)
{
	int p;
	for (p = 0x62d150; p < 0x62d1f0; p += 0x14) {
		*(int*) (p - 4) = 0;
		*(int*) p = 0;
	}
}
