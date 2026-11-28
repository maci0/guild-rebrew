
// fcn_004ac1e0 — if((unsigned short)a < 0x33) return 0x664480 + (a&0xffff)*0x30; return 0.

/* ADDRESS: GOLDTL 0x004ac300 */
/* ADDRESS: GOLDDE 0x0049a640 */
int __cdecl gm_GetBardEventEntry(int a)
{
	unsigned short i;
	i = (unsigned short) a;
	if (i >= 0x33) {
		return 0;
	}
	return 0x664480 + (int) i * 0x30;
}
