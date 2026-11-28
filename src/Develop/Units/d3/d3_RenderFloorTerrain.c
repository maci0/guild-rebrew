#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef long (__stdcall* D3_TERRAIN_SET_TRANSFORM_FN)(D3D_DEVICE_VIEW*, int, float*);
typedef long (__stdcall* D3_TERRAIN_SET_TEXTURE_FN)(D3D_DEVICE_VIEW*, int, int);













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

typedef struct D3_FLOOR_TERRAIN {
	char pad0[0x30];
	MObj* tex[8];
	float pos[3];
	char pad5c[0x44];
	Cell cells[8][8];
} D3_FLOOR_TERRAIN;

#include "Develop/Units/d3/d3_camera.h"


float* __stdcall fcn_005ec410(float*, float, float, float);
float* __stdcall fcn_005eb970(float*, float*, float*);
void __cdecl d3_SetRenderMaterialState(unsigned char, unsigned char, int, unsigned char, unsigned char);

/* ADDRESS: GOLDTL 0x00441400 */
/* ADDRESS: GOLDDE 0x00439dc0 */
void __cdecl d3_RenderFloorTerrain(char* o)
{
	D3_FLOOR_TERRAIN* t;
	float m[16];
	Cell* c;
	MObj* p;
	unsigned k;
	int a;
	int b;

	t = (D3_FLOOR_TERRAIN*) o;
	if (d3_ActiveCamera == 0) {
		return;
	}
	fcn_005ec410(m, t->pos[0] - *(float*) (((char*) d3_ActiveCamera) + 0x4c),
	             t->pos[1] - *(float*) (((char*) d3_ActiveCamera) + 0x50),
	             t->pos[2] - *(float*) (((char*) d3_ActiveCamera) + 0x54));
	fcn_005eb970(m, m, (float*) (((char*) d3_ActiveCamera) + 0x18c));
	((D3_TERRAIN_SET_TRANSFORM_FN) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetTransform)(((D3D_DEVICE_VIEW*)g_6b5de0), 0x100, m);
	d3_SetRenderMaterialState(0xff, 0, 0, 0, 0);
	for (k = 0; k < 8; k++) {
		if (t->tex[k] != 0) {
			((D3_TERRAIN_SET_TEXTURE_FN) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_cc[10])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, *(int*) ((char*) t->tex[k] + 0x50));
			for (a = 0; a < 8; a++) {
				for (b = 0; b < 8; b++) {
					c = &t->cells[a][b];
					if (c->on > 0 && c->occ[k].a != 0) {
						p = c->occ[k].a;
						p->v->slots[3](p, 0);
					}
				}
			}
		}
	}
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x1b, 1);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x8d, 1);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x13, 5);
	for (k = 0; k < 8; k++) {
		if (t->tex[k] != 0) {
			((D3_TERRAIN_SET_TEXTURE_FN) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_cc[10])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, *(int*) ((char*) t->tex[k] + 0x50));
			for (a = 0; a < 8; a++) {
				for (b = 0; b < 8; b++) {
					c = &t->cells[a][b];
					if (c->on > 0 && c->occ[k].b != 0 && c->occ[k].state == 1) {
						p = c->occ[k].b;
						p->v->slots[3](p, 0);
					}
				}
			}
		}
	}
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0xe, 0);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x14, 2);
	for (k = 0; k < 8; k++) {
		if (t->tex[k] != 0) {
			((D3_TERRAIN_SET_TEXTURE_FN) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_cc[10])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, *(int*) ((char*) t->tex[k] + 0x50));
			for (a = 0; a < 8; a++) {
				for (b = 0; b < 8; b++) {
					c = &t->cells[a][b];
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
	}
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x1b, 0);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x13, 2);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x14, 1);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0x8d, 0);
	((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->SetRenderState(((D3D_DEVICE_VIEW*)g_6b5de0), 0xe, 1);
}
