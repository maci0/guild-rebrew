/* ADDRESS: GOLDTL 0x009b0e20 */
extern char g_9b0e20[];
/* ADDRESS: GOLD 0x0092cae0 */
extern char g_9b0e20[];
/* ADDRESS: GOLD 0x004e50e0 */
/* ADDRESS: GOLDTL 0x004e6a70 */

int __cdecl fcn_004e6a70(int a1)
{
	int i;
	int a;

	i = 0;
	for (a = (int) g_9b0e20 + 0x10; a < (int) g_9b0e20 + 0x35d0; a += 0x35c, i++) {
		if (*(int*) a == a1) {
			return (int) ((int) g_9b0e20 + i * 860);
		}
	}
	return 0;
}
