int __cdecl gm_GetBardEventEntry(int a);

/* ADDRESS: GOLDTL 0x004ac2c0 */
/* ADDRESS: GOLDDE 0x0049a600 */
unsigned short __cdecl d2_GetBardPoemTextId(int a0, int a1)
{
	unsigned short v;
	int r;

	v = (unsigned short) a1;
	if (v >= 9) {
		v = 9;
	}
	r = gm_GetBardEventEntry(a0);
	if (r != 0) {
		if (*(int *) (r + 8) == 0) {
			return v + 0x1e2b;
		}
		return v + 0x1e35;
	}
	return (unsigned short) a1;
}
