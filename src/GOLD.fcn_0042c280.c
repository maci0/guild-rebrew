extern int* g_6b7ed0[16];
extern int* g_6b7f10[16];
/* ADDRESS: GOLD 0x0042c280 */

int __cdecl fcn_0042c280(int key)
{
	int i;
	int j;

	for (i = 0; i < 0x10; i++) {
		if (g_6b7ed0[i] != 0) {
			for (j = 0; j < g_6b7ed0[i][6]; j++) {
				if (g_6b7f10[i][j] == key) {
					return j;
				}
			}
		}
	}
	return -1;
}
