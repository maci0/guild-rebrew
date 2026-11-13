#include "g_10058a0.h"
extern unsigned char g_773d75;
extern char* g_1043370;
extern int g_772900;
extern int g_6816d8;
extern char* g_1015ea0;
extern IdSlot10058a0 g_10058a0[8];

typedef struct MapPos {
	int f0;
	int f4;
	int col;
	int row;
	float x;
	float y;
} MapPos;

char* __cdecl gm_SearchTable67(unsigned int);
int __cdecl fcn_004be300(char*, char*);
void __cdecl fcn_00455350(char*, float*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
void __cdecl fcn_005b00f0(char*, int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl fcn_00469470(int, int);

/* ADDRESS: GOLDTL 0x004be3d0 */
int __cdecl fcn_004be3d0(int* a0, char* a1, char* a2, char* a3)
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
	rec = a3;
	idx = idx * 12;
	a = *(int*) (0x86834c + idx);
	b = *(int*) (0x868350 + idx);
	obj = gm_SearchTable67(*(unsigned int*) (rec + 4));
	if (obj == 0) {
		return -1;
	}
	obj = *(char**) (obj + 0x61);
	fcn_00455350(obj, (float*) (obj + 0x4c), out);
	/* The native fourth argument slot also holds the height output. */
	if (!fcn_0045b990(map, out, &p.col, &p.row, (float*) &a3)) {
		return -1;
	}
	fcn_005b00f0((char*) &p, a, b);
	v = fcn_004be300(a2, rec) + 0x7bb;
	v = fcn_0046f740((int) p.x - 0x20, (int) p.y - 0x20, v, a0[2]);
	n = g_772900;
	g_10058a0[n].id = v;
	*(int*) (g_1015ea0 + v * 0x2f4 + 0x58) = 1;
	v = g_10058a0[g_772900].id;
	if (g_6816d8 == -1) {
		g_6816d8 = d2_CreateRadioGroup(1, v);
	} else {
		fcn_00469470(g_6816d8, v);
	}
	n = g_772900;
	g_10058a0[n].b = (int) rec;
	v = g_10058a0[n].id;
	g_772900 = n + 1;
	return v;
}
