typedef struct IDev IDev;
// SIZE 0xcc
typedef struct IDevVtbl {
	void* slots[37];
	long (__stdcall* SetTransform)(IDev*, int, float*);
	void* slots2[12];
	long (__stdcall* SetRenderState)(IDev*, int, int);
	void* slots3[10];
	long (__stdcall* SetTexture)(IDev*, int, int);
} IDevVtbl;
// SIZE 0x4
struct IDev {
	IDevVtbl* v;
};

typedef struct MObj MObj;
// SIZE 0x20
typedef struct MObjVtbl {
	void (__stdcall* slots[8])(MObj*, int);
} MObjVtbl;
// SIZE 0x4
struct MObj {
	MObjVtbl* v;
};

// SIZE 0x34
typedef struct Occ {
	MObj* a;
	MObj* b;
	int state;
	char padc[8];
	unsigned int flag;
	char pad18[0x1c];
} Occ;

// SIZE 0x1f4
typedef struct Cell {
	char pad[0x14];
	Occ occ[8];
	char pad2[0x3a];
	unsigned char on;
	char pad3[5];
} Cell;

#include "Develop/Units/d3/d3_camera.h"
extern void* g_6b5de0;

float* __stdcall fcn_005ec410(float*, float, float, float);
float* __stdcall fcn_005eb970(float*, float*, float*);
void __cdecl fcn_004372d0(unsigned char, unsigned char, int, unsigned char, unsigned char);

/* ADDRESS: GOLDTL 0x00441400 */
void __cdecl fcn_00441400(char* o)
{
	float m[16];
	MObj** pp;
	Cell* c;
	MObj* p;
	unsigned k;
	int a;
	int b;

	if (g_6b8014 == 0) {
		return;
	}
	fcn_005ec410(m, *(float*) (o + 0x50) - *(float*) (((char*) g_6b8014) + 0x4c),
	             *(float*) (o + 0x54) - *(float*) (((char*) g_6b8014) + 0x50),
	             *(float*) (o + 0x58) - *(float*) (((char*) g_6b8014) + 0x54));
	fcn_005eb970(m, m, (float*) (((char*) g_6b8014) + 0x18c));
	((IDev*) g_6b5de0)->v->SetTransform(((IDev*) g_6b5de0), 0x100, m);
	fcn_004372d0(0xff, 0, 0, 0, 0);
	for (pp = (MObj**) (o + 0x30), k = 0; k < 8; k++) {
		if (*pp != 0) {
			((IDev*) g_6b5de0)->v->SetTexture(((IDev*) g_6b5de0), 0, *(int*) ((char*) *pp + 0x50));
			for (a = 0; a < 8; a++) {
				for (b = 0; b < 8; b++) {
					c = (Cell*) (o + 0xa0) + a * 8 + b;
					if (c->on > 0 && c->occ[k].a != 0) {
						p = c->occ[k].a;
						p->v->slots[3](p, 0);
					}
				}
			}
		}
		pp++;
	}
	((IDev*) g_6b5de0)->v->SetRenderState(((IDev*) g_6b5de0), 0x1b, 1);
	((IDev*) g_6b5de0)->v->SetRenderState(((IDev*) g_6b5de0), 0x8d, 1);
	((IDev*) g_6b5de0)->v->SetRenderState(((IDev*) g_6b5de0), 0x13, 5);
	for (pp = (MObj**) (o + 0x30), k = 0; k < 8; k++) {
		if (*pp != 0) {
			((IDev*) g_6b5de0)->v->SetTexture(((IDev*) g_6b5de0), 0, *(int*) ((char*) *pp + 0x50));
			for (a = 0; a < 8; a++) {
				for (b = 0; b < 8; b++) {
					c = (Cell*) (o + 0xa0) + a * 8 + b;
					if (c->on > 0 && c->occ[k].b != 0 && c->occ[k].state == 1) {
						p = c->occ[k].b;
						p->v->slots[3](p, 0);
					}
				}
			}
		}
		pp++;
	}
	((IDev*) g_6b5de0)->v->SetRenderState(((IDev*) g_6b5de0), 0xe, 0);
	((IDev*) g_6b5de0)->v->SetRenderState(((IDev*) g_6b5de0), 0x14, 2);
	for (pp = (MObj**) (o + 0x30), k = 0; k < 8; k++) {
		if (*pp != 0) {
			((IDev*) g_6b5de0)->v->SetTexture(((IDev*) g_6b5de0), 0, *(int*) ((char*) *pp + 0x50));
			for (a = 0; a < 8; a++) {
				for (b = 0; b < 8; b++) {
					c = (Cell*) (o + 0xa0) + a * 8 + b;
					if (c->on > 0 && c->occ[k].b != 0) {
						if (c->occ[k].state != 1) {
							p = c->occ[k].b;
							p->v->slots[3](p, 0);
						}
						if (c->occ[k].flag > 0) {
							p = c->occ[k].b;
							p->v->slots[3](p, 1);
						}
					}
				}
			}
		}
		pp++;
	}
	((IDev*) g_6b5de0)->v->SetRenderState(((IDev*) g_6b5de0), 0x1b, 0);
	((IDev*) g_6b5de0)->v->SetRenderState(((IDev*) g_6b5de0), 0x13, 2);
	((IDev*) g_6b5de0)->v->SetRenderState(((IDev*) g_6b5de0), 0x14, 1);
	((IDev*) g_6b5de0)->v->SetRenderState(((IDev*) g_6b5de0), 0x8d, 0);
	((IDev*) g_6b5de0)->v->SetRenderState(((IDev*) g_6b5de0), 0xe, 1);
}
