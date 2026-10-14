/* ADDRESS: GOLD 0x0052e1a0 */
// fcn_0052e1a0 — zero 16 dwords at 0x760640 (stride 0xc8).

void __cdecl fcn_0052e1a0(void)
{
	int p;
	for (p = 0x760640; p < 0x761f40; p += 0xc8) {
		*(int*) p = 0;
	}
}
