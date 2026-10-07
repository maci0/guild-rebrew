// FUNCTION: GOLD 0x404ed0
// FUNCTION: GOLDTL 0x00405960

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
extern int g_675320;
extern int g_675324;
extern int g_6b5c4c;
extern int g_6b5c50;

void __cdecl fcn_00405960(Grid* m)
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
	g_675320 = g_675320 < 0 ? 0 : g_675320;
	if (m->n < g_6b5c4c) {
		g_6b5c4c = m->n;
	}
	g_675324 = g_675324 < 0 ? 0 : g_675324;
	if (m->n < g_6b5c50) {
		g_6b5c50 = m->n;
	}
	for (i = g_675320; i < g_6b5c4c; i++) {
		for (j = g_675324; j < g_6b5c50; j++) {
			m->cells[m->n * j + i].v = dst[m->n * j + i];
		}
	}
	g_675320 = m->n;
	g_6b5c4c = 0;
	g_675324 = m->n;
	g_6b5c50 = 0;
}
