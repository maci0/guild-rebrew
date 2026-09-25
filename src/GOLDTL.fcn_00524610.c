extern int g_6a23ac;
extern char g_869480[0x300][0x300];
extern char g_90e0a0[0x300][0x300];

// FUNCTION: GOLDTL 0x524610
// SIZE: 208

int __cdecl ls_ReadVfsDataChecked(void*, int, int, int);

int __cdecl fcn_00524610(int x)
{
	int n;
	int i;
	int j;

	if (g_6a23ac < 0x1003a) {
		n = 0x100;
	} else {
		n = g_6a23ac < 0x10042 ? 0x200 : 0x300;
	}
	for (j = 0; j < n; j++) {
		for (i = 0; i < n; i++) {
			if (ls_ReadVfsDataChecked(&g_869480[j][i], 1, 1, x) == 0) {
				return 0;
			}
		}
	}
	if (g_6a23ac >= 0x10036) {
		for (j = 0; j < n; j++) {
			for (i = 0; i < n; i++) {
				if (ls_ReadVfsDataChecked(&g_90e0a0[j][i], 1, 1, x) == 0) {
					return 0;
				}
			}
		}
	}
	return 1;
}
