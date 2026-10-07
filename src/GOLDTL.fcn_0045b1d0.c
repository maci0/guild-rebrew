// FUNCTION: GOLD 0x0045e550
// FUNCTION: GOLDTL 0x45b1d0

// SIZE 0x1c
typedef struct Cell {
	int v;
	int pad[6];
} Cell;

void __cdecl fcn_0045b1d0(char* g, int from, int to)
{
	int j;
	int i;
	Cell* c;

	for (j = 1; j < *(int*) (g + 0x20) - 1; j++) {
		c = &(*(Cell**) (g + 0x24))[*(int*) (g + 0x20) * j + 1];
		for (i = 1; i < *(int*) (g + 0x20) - 1; i++, c++) {
			if (c->v == from && (c[-*(int*) (g + 0x20)].v == from || c[-*(int*) (g + 0x20)].v == to) &&
			    (c[*(int*) (g + 0x20)].v == from || c[*(int*) (g + 0x20)].v == to) && (c[-1].v == from || c[-1].v == to) &&
			    (c[1].v == from || c[1].v == to)) {
				c->v = to;
			}
		}
	}
}
