


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

void __cdecl ch_BackupGrid(Grid* grid)
{
	int* dst;
	int i;
	int j;

	if ((*(Grid**)g_1043370) == grid) {
		dst = g_14d1f40;
	} else if (*(Grid**) (((char*)g_67a370) + 0xb0) == grid) {
		dst = g_1511f40;
	} else {
		return;
	}
	for (i = 0; i < grid->n; i++) {
		for (j = 0; j < grid->n; j++) {
			dst[grid->n * j + i] = grid->cells[grid->n * j + i].v;
		}
	}
}
