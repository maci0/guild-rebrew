// FUNCTION: GOLD 0x00520230
// FUNCTION: GOLDTL 0x005251c0

// SIZE 0x8
typedef struct {
	int a;
	int b;
} Pair;

// SIZE 0x44
typedef struct {
	int count;
	Pair pairs[8];
} Group;

extern char g_7728d4;
extern int g_67fca0;
extern int g_67fca8;
extern int g_67fcac;
extern int g_67fcb4;
extern char g_1007ba0[];
extern char g_1007bc0[];

int __cdecl ls_ReadVfsDataChecked(void* p, int size, int n, void* file);
void __cdecl fcn_004b1e60(void);

int __cdecl fcn_005251c0(void* file)
{
	int v;
	int i;
	int k;

	if (!ls_ReadVfsDataChecked(&(*(unsigned char*)&g_7728d4), 1, 1, file))
		return 0;
	fcn_004b1e60();
	if (!ls_ReadVfsDataChecked(&v, 4, 1, file))
		return 0;
	g_67fca8 = g_67fca0 + v;
	if (!ls_ReadVfsDataChecked(&v, 4, 1, file))
		return 0;
	g_67fcb4 = g_67fcac + v;
	for (i = 0; i < 16; i++) {
		if (!ls_ReadVfsDataChecked(&((unsigned char*)g_1007ba0)[i], 1, 1, file))
			return 0;
	}
	for (i = 0; i < 4; i++) {
		if (!ls_ReadVfsDataChecked(&((Group*)g_1007bc0)[i].count, 4, 1, file))
			return 0;
		for (k = 0; k < 8; k++) {
			if (!ls_ReadVfsDataChecked(&((Group*)g_1007bc0)[i].pairs[k].a, 4, 1, file))
				return 0;
			if (!ls_ReadVfsDataChecked(&((Group*)g_1007bc0)[i].pairs[k].b, 4, 1, file))
				return 0;
		}
	}
	return 1;
}
