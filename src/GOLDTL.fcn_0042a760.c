// FUNCTION: GOLD 0x0042bca0
// SIZE: 95
// FUNCTION: GOLDTL 0x42a760
// SIZE: 95

extern int g_6b7f90;
extern char* g_6b7ed0[16];
extern int* g_6b7f10[16];
int __cdecl fcn_0042a6a0(int);

int __cdecl fcn_0042a760(void)
{
	int r = 0;
	int i;
	int j;

	if (g_6b7f90 != 0) {
		for (i = 0; i < 0x10; i++) {
			if (g_6b7ed0[i] != 0) {
				for (j = 0; j < *(int*) (g_6b7ed0[i] + 0x18); j++) {
					if (g_6b7f10[i][j] != 0 && fcn_0042a6a0(g_6b7f10[i][j]) == -1) {
						r = -1;
					}
				}
			}
		}
	} else {
		r = -1;
	}
	return r;
}
