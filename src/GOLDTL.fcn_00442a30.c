#include <stdio.h>

// SIZE 0x40
typedef struct {
	char used;
	char p1[0x3f];
} Cell;

// SIZE 0x204
typedef struct {
	char p0[0x1e4];
	int count;
	int levels;
	char p1ec[0x14];
	Cell* cells;
} Mesh;

// SIZE 0x5c
typedef struct {
	char p0[0x58];
	int x58;
} Tex;

// SIZE 0x4a2
typedef struct {
	char p0[0x318];
	Mesh* mesh;
	Tex** tex;
	char p320[0x181];
	unsigned char lod;
} Obj;

// SIZE 0x215
typedef struct {
	char p0[0x1ec];
	int x1ec;
	char p1f0[0x24];
	unsigned char flags;
} Ent;

void __cdecl fcn_0045cab0(Tex*, int*, int*);
Tex* __cdecl fcn_0045c5b0(Cell*, int, int, int);
void __cdecl fcn_0045ce90(Tex*);
void __cdecl fcn_0045bfb0(Tex*);

/* ADDRESS: GOLDTL 0x00442a30 */

char __cdecl fcn_00442a30(Ent* e, Obj* o, unsigned char lod, char refresh)
{
	char ok;
	int v14;
	int v18;
	Tex* r;
	char buf[0x100];
	Mesh* m;
	Cell* d;
	Tex* t;
	int i;

	ok = 1;
	if (e == 0 || e->x1ec == 0 || o == 0) {
		return 0;
	}
	if (lod == o->lod) {
		return 1;
	}
	e->flags |= 4;
	m = o->mesh;
	if (lod < m->levels) {
		for (i = 0; i < m->count; i++) {
			o->lod = lod;
			d = &m->cells[m->count * lod + i];
			if (d->used != 0) {
				t = o->tex[i];
				if (t != 0) {
					fcn_0045cab0(t, &v18, &v14);
					r = fcn_0045c5b0(d, t->x58, v18, v14);
					if (r != 0) {
						if (refresh) {
							fcn_0045ce90(r);
						}
						o->tex[i] = r;
						o->tex[m->count + i] = r;
						fcn_0045bfb0(t);
					} else {
						sprintf(buf, "SelectTextureSet: cannot replace %s with %s (new not found) in %s", t, d, e);
						ok = 0;
					}
				}
			}
		}
	} else {
		ok = 0;
	}
	return ok;
}
