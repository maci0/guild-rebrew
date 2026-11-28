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

void __cdecl d3_PackTextureFlags(Tex*, int*, int*);
Tex* __cdecl d3_LoadOrReuseTexture(Cell*, int, int, int);
void __cdecl d3_LoadTextureSurfaceTl(Tex*);
void __cdecl d3_ReleaseTexture(Tex*);


/* ADDRESS: GOLDTL 0x00442a30 */
/* ADDRESS: GOLDDE 0x0043ae80 */
char __cdecl SelectTextureSet(Ent* e, Obj* o, unsigned char lod, char refresh)
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
					d3_PackTextureFlags(t, &v18, &v14);
					r = d3_LoadOrReuseTexture(d, t->x58, v18, v14);
					if (r != 0) {
						if (refresh) {
							d3_LoadTextureSurfaceTl(r);
						}
						o->tex[i] = r;
						o->tex[m->count + i] = r;
						d3_ReleaseTexture(t);
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
