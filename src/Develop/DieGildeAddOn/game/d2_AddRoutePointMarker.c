extern char g_86834c[];
#include "Develop/Units/d2.v1/d2_radio_slot.h"
extern unsigned char gm_ActiveTownIndex;
extern char* tp_ch_PathGrid;
extern int g_772900;
extern int d2_RouteRadioGroupId;
#include "Develop/Units/d2.v1/d2_gui.h"
extern D2_RADIO_SLOT d2_RadioSlots[8];

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
char __cdecl d3sm_3D2SuperMap(char*, float*, int*, int*, float*);
void __cdecl d2_ProjectMapCoordToScreen(char*, int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl d2_AddToRadioGroup(int, int);

/* ADDRESS: GOLDTL 0x004be3d0 */
/* ADDRESS: GOLDDE 0x004abf50 */
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

	idx = gm_ActiveTownIndex;
	idx = (idx << 6) - idx;
	map = tp_ch_PathGrid;
	rec = point;
	idx = idx * 12;
	a = *(int*) ((int) &g_86834c + idx);
	b = *(int*) (((int) &g_86834c + 0x4) + idx);
	obj = gm_SearchTable67(*(unsigned int*) (rec + 4));
	if (obj == 0) {
		return -1;
	}
	obj = *(char**) (obj + 0x61);
	d3_TransformPoint(obj, (float*) (obj + 0x4c), out);
	/* The native fourth argument slot also holds the height output. */
	if (!d3sm_3D2SuperMap(map, out, &p.col, &p.row, (float*) &point)) {
		return -1;
	}
	d2_ProjectMapCoordToScreen((char*) &p, a, b);
	v = d2_FindLinkedRecordIndex(routeHead, rec) + 0x7bb;
	v = d2_AddElementToWindow((int) p.x - 0x20, (int) p.y - 0x20, v, town[2]);
	n = g_772900;
	d2_RadioSlots[n].id = v;
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[v].value_058)) = 1;
	if (d2_RouteRadioGroupId == -1) {
		d2_RouteRadioGroupId = d2_CreateRadioGroup(1, d2_RadioSlots[g_772900].id);
	} else {
		d2_AddToRadioGroup(d2_RouteRadioGroupId, d2_RadioSlots[g_772900].id);
	}
	n = g_772900;
	d2_RadioSlots[n].b = (int) rec;
	v = d2_RadioSlots[n].id;
	g_772900++;
	return v;
}
