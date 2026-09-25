// FUNCTION: GOLDTL 0x42b180
// SIZE: 61

extern int* g_6b7f50[16];
int __cdecl fcn_0042b120(char*);

int __cdecl fcn_0042b180(char* a1)
{
	int i;
	int j;

	i = fcn_0042b120(a1);
	if (i >= 0 && *(int*) (a1 + 0x14) < *(int*) (a1 + 0x18)) {
		for (j = 0; j < *(int*) (a1 + 0x18); j++) {
			if (g_6b7f50[i][j] == 0) {
				return j;
			}
		}
	}
	return -1;
}
