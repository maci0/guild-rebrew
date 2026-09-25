// FUNCTION: GOLDTL 0x004edd30
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

unsigned int __cdecl fcn_00430910(void* p, int size, int n, void* file);

int __cdecl fcn_004edd30(void* file)
{
	int i;

	if (fcn_00430910(&g_772f78, 4, 1, file) <= 0)
		return 0;
	if (fcn_00430910(&g_772f7c, 4, 1, file) <= 0)
		return 0;
	if (fcn_00430910(&g_772f80, 4, 1, file) <= 0)
		return 0;
	if (fcn_00430910(&g_772f84, 4, 1, file) <= 0)
		return 0;
	if (fcn_00430910(&g_772f88, 4, 1, file) <= 0)
		return 0;
	if (fcn_00430910(&g_772f8c, 2, 1, file) <= 0)
		return 0;
	for (i = 0; i < 3; i++) {
		if (fcn_00430910(&g_772f90[i].a, 4, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].g, 4, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].h, 4, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].b, 1, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].c, 1, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].d, 1, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].e, 1, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].k, 1, 1, file) <= 0)
			return 0;
		if (fcn_00430910(&g_772f90[i].f, 4, 1, file) <= 0)
			return 0;
	}
	return 1;
}
