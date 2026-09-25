// FUNCTION: GOLDTL 0x42ad00
// SIZE: 95

extern char* g_6b7ed0[16];
extern int* g_6b7f50[16];
int __cdecl fcn_0042ac40(int);

int __cdecl fcn_0042ad00(void)
{
	int r = 0;
	int i;
	int j;

	if (*(int*) 0x6b7f90 != 0) {
		for (i = 0; i < 0x10; i++) {
			if (g_6b7ed0[i] != 0) {
				for (j = 0; j < *(int*) (g_6b7ed0[i] + 0x18); j++) {
					if (g_6b7f50[i][j] != 0 && fcn_0042ac40(g_6b7f50[i][j]) != 0) {
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
