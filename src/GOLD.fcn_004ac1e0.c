/* ADDRESS: GOLD 0x004ac1e0 */
// fcn_004ac1e0 — if((unsigned short)a < 0x33) return 0x5ed1e8 + (a&0xffff)*0x30; return 0.

int __cdecl fcn_004ac1e0(int a)
{
	unsigned short i;
	i = (unsigned short) a;
	if (i >= 0x33) {
		return 0;
	}
	return 0x5ed1e8 + (int) i * 0x30;
}
