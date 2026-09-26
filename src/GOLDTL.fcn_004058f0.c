// FUNCTION: GOLDTL 0x004058f0
// SIZE: 102
// FUNCTION: GOLD 0x00404e60
// SIZE: 102

// SIZE 0x1c
typedef struct {
	int v;
	int pad[6];
} Cell;

typedef struct {
	char pad0[0x20];
	int n;
	Cell* cells;
} Grid;

extern char g_1043370[];
extern int g_67a370;
extern int g_14d1f40[];
extern int g_1511f40[];

void __cdecl fcn_004058f0(Grid* m)
{
	int* dst;
	int i;
	int j;

	if ((*(Grid**)g_1043370) == m) {
		dst = g_14d1f40;
	} else if (*(Grid**) (((char*)g_67a370) + 0xb0) == m) {
		dst = g_1511f40;
	} else {
		return;
	}
	for (i = 0; i < m->n; i++) {
		for (j = 0; j < m->n; j++) {
			dst[m->n * j + i] = m->cells[m->n * j + i].v;
		}
	}
}
