// FUNCTION: GOLDTL 0x42b200
// SIZE: 59

extern int* g_6b7ed0[16];
extern int* g_6b7f50[16];

int __cdecl fcn_0042b200(int key)
{
	int i;
	int j;

	for (i = 0; i < 0x10; i++) {
		if (g_6b7ed0[i] != 0) {
			for (j = 0; j < g_6b7ed0[i][6]; j++) {
				if (g_6b7f50[i][j] == key) {
					return j;
				}
			}
		}
	}
	return -1;
}
