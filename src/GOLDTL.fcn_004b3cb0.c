/* ADDRESS: GOLDTL 0x00680bd4 */
extern char g_680bd4[];
/* ADDRESS: GOLD 0x00601f6c */
extern char g_680bd4[];
/* ADDRESS: GOLD 0x004b3b40 */
/* ADDRESS: GOLDTL 0x004b3cb0 */

int __cdecl fcn_004b3cb0(int a1)
{
	int count;
	int p;

	if (a1 < 0 || a1 > 5) {
		return -1;
	}
	count = 0;
	for (p = (int) g_680bd4; p < (int) g_680bd4 + 0x540; p += 0x1c) {
		if (*(int*) p == a1) {
			count++;
		}
	}
	return count;
}
