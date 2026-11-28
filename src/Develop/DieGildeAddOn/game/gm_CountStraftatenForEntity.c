/* Count slots [p]==1 with [p-0xf]==a. */

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004f39b0 */
int __cdecl gm_CountStraftatenForEntity(int a)
{
	int p;
	int n;

	n = 0;
	for (p = 0x91f725; p < 0x925125; p += 0x2d) {
		if (*(int*) (p - 0xf) == a && *(int*) p == 1) {
			n++;
		}
	}
	return n;
}
#else
/* ADDRESS: GOLDTL 0x004f5da0 */
/* ADDRESS: GOLDDE 0x004e1b80 */
int __cdecl gm_CountStraftatenForEntity(int a)
{
	int p;
	int n;
	n = 0;
	for (p = 0x9a3825; p < 0x9a9225; p += 0x2d) {
		if (*(int*) (p - 0xf) == a && *(int*) p == 1) {
			n++;
		}
	}
	return n;
}
#endif
