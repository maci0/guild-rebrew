// FUNCTION: GOLDTL 0x00521420
// SIZE: 272

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

extern unsigned char g_7728d4;
extern int g_67fca0;
extern int g_67fca8;
extern int g_67fcac;
extern int g_67fcb4;
extern unsigned char g_1007ba0[16];
extern Group g_1007bc0[4];

unsigned int __cdecl fcn_00430910(void* p, int size, int n, void* file);

int __cdecl fcn_00521420(void* file)
{
	int v;
	int i;
	int k;

	if (fcn_00430910(&g_7728d4, 1, 1, file) <= 0)
		return 0;
	v = g_67fca8 - g_67fca0;
	if (fcn_00430910(&v, 4, 1, file) <= 0)
		return 0;
	v = g_67fcb4 - g_67fcac;
	if (fcn_00430910(&v, 4, 1, file) <= 0)
		return 0;
	for (i = 0; i < 16; i++) {
		if (fcn_00430910(&g_1007ba0[i], 1, 1, file) <= 0)
			return 0;
	}
	for (i = 0; i < 4; i++) {
		if (fcn_00430910(&g_1007bc0[i].count, 4, 1, file) <= 0)
			return 0;
		for (k = 0; k < 8; k++) {
			if (fcn_00430910(&g_1007bc0[i].pairs[k].a, 4, 1, file) <= 0)
				return 0;
			if (fcn_00430910(&g_1007bc0[i].pairs[k].b, 4, 1, file) <= 0)
				return 0;
		}
	}
	return 1;
}
