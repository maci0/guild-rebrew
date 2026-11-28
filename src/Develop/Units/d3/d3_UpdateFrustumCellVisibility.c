


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

int __cdecl d3_TransformBoundsCorners(Cell*, char*, char*);
Res __cdecl d3_TestBoxAgainstFrustum(int, char*, char*);

/* ADDRESS: GOLDDE 0x0044a830 */
void __cdecl d3_UpdateFrustumCellVisibility(Cell* c, char* e, int v)
{
	Res r;
	Link* l;
	unsigned int i;
	int t;

	if (c == 0) {
		return;
	}
	t = d3_TransformBoundsCorners(c, e + 0x4c, e + 0x18c);
	r = d3_TestBoxAgainstFrustum(t, 0, 0);
	if (r.b6) {
		for (l = c->head; l != 0; l = l->next) {
			if (*(char**) (l->e + 0x1ec) != 0) {
				*(int*) (*(char**) (l->e + 0x1ec) + 0xb0) = v;
			}
		}
	} else if (r.lo) {
		for (i = 0; i < 4; i++) {
			if (c->child[i] != 0) {
				d3_UpdateFrustumCellVisibility(c->child[i], e, v);
			}
		}
	}
}
