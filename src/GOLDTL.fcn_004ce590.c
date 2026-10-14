/* ADDRESS: GOLDTL 0x0068b400 */
extern char g_68b400[];
/* ADDRESS: GOLD 0x0060c7a0 */
extern char g_68b400[];
/* ADDRESS: GOLD 0x004cd9d0 */
/* ADDRESS: GOLDTL 0x004ce590 */

int __cdecl fcn_004ce590(int a1)
{
	int i;
	int a;

	for (i = 0, a = (int) g_68b400; a < (int) g_68b400 + 0x398; a += 0x5c, i++) {
		if (*(int*) a == a1) {
			return (int) ((int) g_68b400 + i * 92);
		}
	}
	return 0;
}
