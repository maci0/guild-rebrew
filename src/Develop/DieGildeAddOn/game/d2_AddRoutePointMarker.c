#include "Develop/Units/d2.v1/d2_radio_slot.h"
extern unsigned char g_773d75;
extern char* g_1043370;
extern int g_772900;
extern int g_6816d8;
#include "Develop/Units/d2.v1/d2_gui.h"
extern D2_RADIO_SLOT g_10058a0[8];

typedef struct MapPos {
	int f0;
	int f4;
	int col;
	int row;
	float x;
	float y;
} MapPos;

char* __cdecl gm_SearchTable67(unsigned int);
int __cdecl d2_FindLinkedRecordIndex(char*, char*);
void __cdecl d3_TransformPoint(char*, float*, float*);
char __cdecl d3sm_SampleHeight(char*, float*, int*, int*, float*);
void __cdecl d2_ProjectMapCoordToScreen(char*, int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl d2_AddToRadioGroup(int, int);

/* ADDRESS: GOLDTL 0x004be3d0 */
int __cdecl d2_AddRoutePointMarker(int* town, char* building, char* routeHead, char* point)
{
	float out[4];
	MapPos p;
	char* rec;
	char* obj;
	int idx;
	int a;
	int b;
	int v;
	int n;
	char* map;

	idx = g_773d75;
	idx = (idx << 6) - idx;
	map = g_1043370;
	rec = point;
	idx = idx * 12;
	a = *(int*) (0x86834c + idx);
	b = *(int*) (0x868350 + idx);
	obj = gm_SearchTable67(*(unsigned int*) (rec + 4));
	if (obj == 0) {
		return -1;
	}
	obj = *(char**) (obj + 0x61);
	d3_TransformPoint(obj, (float*) (obj + 0x4c), out);
	/* The native fourth argument slot also holds the height output. */
	if (!d3sm_SampleHeight(map, out, &p.col, &p.row, (float*) &point)) {
		return -1;
	}
	d2_ProjectMapCoordToScreen((char*) &p, a, b);
	v = d2_FindLinkedRecordIndex(routeHead, rec) + 0x7bb;
	v = d2_AddElementToWindow((int) p.x - 0x20, (int) p.y - 0x20, v, town[2]);
	n = g_772900;
	g_10058a0[n].id = v;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[v].value_058)) = 1;
	if (g_6816d8 == -1) {
		g_6816d8 = d2_CreateRadioGroup(1, g_10058a0[g_772900].id);
	} else {
		d2_AddToRadioGroup(g_6816d8, g_10058a0[g_772900].id);
	}
	n = g_772900;
	g_10058a0[n].b = (int) rec;
	v = g_10058a0[n].id;
	g_772900++;
	return v;
}
