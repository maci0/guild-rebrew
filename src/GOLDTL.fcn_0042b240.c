extern int* g_6b7ed0[16];
extern int* g_6b7f10[16];
// FUNCTION: GOLDTL 0x42b240

int __cdecl fcn_0042b240(int id)
{
	int i;
	int j;

	for (i = 0; i < 16; i++) {
		if (g_6b7ed0[i] != 0) {
			for (j = 0; j < g_6b7ed0[i][6]; j++) {
				if (g_6b7f10[i][j] == id) {
					return i;
				}
			}
		}
	}
	return -1;
}
