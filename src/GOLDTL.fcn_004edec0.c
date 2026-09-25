// FUNCTION: GOLD 0x004ec140
// SIZE: 400
// FUNCTION: GOLDTL 0x004edec0
// SIZE: 400

// SIZE 0x18
typedef struct {
	int a;
	char b;
	char c;
	char d;
	char e;
	char k;
	char pad9[3];
	int f;
	int g;
	int h;
} Rec;

extern int g_772f78;
extern int g_772f7c;
extern int g_772f80;
extern int g_772f84;
extern int g_772f88;
extern short g_772f8c;
extern Rec g_772f90[3];

int __cdecl ls_ReadVfsDataChecked(void* p, int size, int n, void* file);
void __cdecl fcn_004ecaa0(int v);

int __cdecl fcn_004edec0(void* file)
{
	int i;

	if (!ls_ReadVfsDataChecked(&g_772f78, 4, 1, file))
		return 0;
	if (!ls_ReadVfsDataChecked(&g_772f7c, 4, 1, file))
		return 0;
	if (!ls_ReadVfsDataChecked(&g_772f80, 4, 1, file))
		return 0;
	if (!ls_ReadVfsDataChecked(&g_772f84, 4, 1, file))
		return 0;
	if (!ls_ReadVfsDataChecked(&g_772f88, 4, 1, file))
		return 0;
	if (!ls_ReadVfsDataChecked(&g_772f8c, 2, 1, file))
		return 0;
	for (i = 0; i < 3; i++) {
		if (!ls_ReadVfsDataChecked(&g_772f90[i].a, 4, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].g, 4, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].h, 4, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].b, 1, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].c, 1, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].d, 1, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].e, 1, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].k, 1, 1, file))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_772f90[i].f, 4, 1, file))
			return 0;
	}
	fcn_004ecaa0(0);
	return 1;
}
