

typedef struct IUnk IUnk;
// SIZE 0xc
typedef struct IUnkVtbl {
	long (__stdcall* QueryInterface)(IUnk*, void*, void**);
	unsigned long (__stdcall* AddRef)(IUnk*);
	unsigned long (__stdcall* Release)(IUnk*);
} IUnkVtbl;
// SIZE 0x4
struct IUnk {
	IUnkVtbl* v;
};

// SIZE 0x34
typedef struct Sub {
	int head[4];
	IUnk* a;
	IUnk* b;
	int rest[7];
} Sub;

// SIZE 0x1f4
typedef struct Cell {
	Sub sub[8];
	IUnk* main;
	char pad[0x14];
	char on;
	char pad2[0x3b];
} Cell;

extern unsigned long g_14ce728;

void __cdecl fcn_0043b8f0(char* o)
{
	Cell (*cells)[8];
	int a;
	int b;
	int c;

	cells = (Cell (*)[8]) (o + 0xa4);
	for (a = 0; a < 8; a++) {
		for (b = 0; b < 8; b++) {
			if (cells[a][b].on != 0 && cells[a][b].main != 0) {
				g_14ce728 = cells[a][b].main->v->Release(cells[a][b].main);
				cells[a][b].main = 0;
			}
			for (c = 0; c < 8; c++) {
				if (cells[a][b].sub[c].a != 0) {
					g_14ce728 = cells[a][b].sub[c].a->v->Release(cells[a][b].sub[c].a);
					cells[a][b].sub[c].a = 0;
				}
				if (cells[a][b].sub[c].b != 0) {
					g_14ce728 = cells[a][b].sub[c].b->v->Release(cells[a][b].sub[c].b);
					cells[a][b].sub[c].b = 0;
				}
			}
		}
	}
}
