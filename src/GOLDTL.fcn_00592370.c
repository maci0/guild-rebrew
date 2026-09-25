// FUNCTION: GOLDTL 0x00592370
// SIZE: 136

// SIZE 0xc
typedef struct {
	int a;
	int b;
	int c;
} Slot;

extern Slot g_779d00[];

int __cdecl ls_ReadVfsDataChecked(void*, int, int, int);

int __cdecl fcn_00592370(int fh)
{
	int n;
	int i;

	n = 0;
	if (ls_ReadVfsDataChecked(&n, 4, 1, fh) == 0) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		if (ls_ReadVfsDataChecked(&g_779d00[i].a, 1, 1, fh) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(&g_779d00[i].b, 4, 1, fh) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(&g_779d00[i].c, 4, 1, fh) == 0) {
			return 0;
		}
	}
	return 1;
}
