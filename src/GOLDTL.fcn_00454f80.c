// FUNCTION: GOLD 0x458640
// FUNCTION: GOLDTL 0x454f80

// SIZE 0x1
typedef struct Res {
	unsigned char lo : 6;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} Res;

// SIZE 0x8
typedef struct Link {
	char* e;
	struct Link* next;
} Link;

// SIZE 0x44
typedef struct Cell {
	struct Cell* child[4];
	int pad[11];
	Link* head;
	Link* tail;
} Cell;

int __cdecl fcn_00454c90(Cell*, char*, char*);
Res __cdecl fcn_00437ee0(int, char*, char*);

void __cdecl fcn_00454f80(Cell* c, char* e, int v)
{
	Res r;
	Link* l;
	unsigned int i;
	int t;

	if (c == 0) {
		return;
	}
	t = fcn_00454c90(c, e + 0x4c, e + 0x18c);
	r = fcn_00437ee0(t, 0, 0);
	if (r.b6) {
		for (l = c->head; l != 0; l = l->next) {
			if (*(char**) (l->e + 0x1ec) != 0) {
				*(int*) (*(char**) (l->e + 0x1ec) + 0xb0) = v;
			}
		}
	} else if (r.lo) {
		for (i = 0; i < 4; i++) {
			if (c->child[i] != 0) {
				fcn_00454f80(c->child[i], e, v);
			}
		}
	}
}
