#include "client_data.h"
#include "d2_gui.h"
#include "d2_win.h"
typedef struct { char pad00[0x5c]; int f5c; char pad60[0x1d0-0x60]; int f1d0; char pad1d4[0x2f4-0x1d4]; } GUI_ROW_5893D0;
int __cdecl fcn_00469c30(int x, int y, int a3);
int __cdecl fcn_00469c40(int x, int y, int win);
int __cdecl fcn_0046f740(int x, int y, int a3, int win);
int __cdecl fcn_00470820(int a0, int a1, char* text);
void __cdecl fcn_00471d80(int k, int flags);
void __cdecl fcn_00471af0(int k, int flag);
int __cdecl d2_SetForm(int k, int i);
void __cdecl fcn_00472380(int k, int a1, int a2, int a3, ...);
void __cdecl fcn_00468b80(int id, int value);
void __cdecl fcn_00468bb0(int slot, int n, ...);
int __cdecl fcn_004677e0(int x, int y, int a3, int a4, int a5, int a6, int a7, int win);
float __cdecl fcn_005e8860(int a0);
extern char * g_1015ea0; extern char g_10161bc[]; extern float g_662cf8; extern int g_6b7fac; extern char * g_772500; extern int g_772514;
/* ADDRESS: GOLDTL 0x005893d0 */
void __cdecl fcn_005893d0(int w, int a1)
{
	int width;
	int height;
	int half;
	int v;
	int id;
	int id2;

	width = g_1040494;
	height = g_1040490;
	half = (height - (width >> 4) * 9) >> 1;
	v = height - half;
	if (width == 0x320) {
		id = 0x7cb;
		id2 = 0x7ce;
	} else if (width == 0x400) {
		id = 0x7cc;
		id2 = 0x7cf;
	} else {
		id = 0x7cd;
		id2 = 0x7d0;
	}
	*(int*) (w + 0xd4) = fcn_00469c30(0, 0, id);
	*(int*) (w + 0xd8) = fcn_00469c30(0,
	    g_1040490
	    - (int) ((D2_BILD_GROESSE*)g_772500)[id2].hoehe, id2);
	*(int*) (w + 0xa4) = fcn_00470820(0, 0, (char*) 0x6a94e8);
	fcn_00471d80(*(int*) (w + 0xa4), 1);
	d2_SetForm(*(int*) (w + 0xa4), 0);
	fcn_00469c40(((D2_WIN*)g_1015f40)[g_772514].left, v - 0x19,
	    ((D2_WIN*)g_1015f40)[g_772514].slot);
	d2_SetForm(*(int*) (w + 0xa4), 2);
	*(int*) (w + 0xb8) = fcn_0046f740(0x59, 0xf, 0x7d5, *(int*) &g_772514);
	((GUI_ROW_5893D0*)g_1015ea0)[*(int*) (w + 0xb8)].f5c = 1;
	((GUI_ROW_5893D0*)g_1015ea0)[*(int*) (w + 0xb8)].f1d0 = 3;
	*(int*) (w + 0xbc) = fcn_0046f740(0x9b, 0xf, 0x7d4, *(int*) &g_772514);
	((GUI_ROW_5893D0*)g_1015ea0)[*(int*) (w + 0xbc)].f5c = 1;
	((GUI_ROW_5893D0*)g_1015ea0)[*(int*) (w + 0xbc)].f1d0 = 3;
	d2_SetForm(*(int*) (w + 0xa4), 1);
	*(int*) (w + 0xb0) = fcn_004677e0(0x140, 0x14, 100, 0, 100, 0x7b, 0x82,
	    *(int*) &g_772514);
	fcn_00472380(*(int*) (w + 0xb0), 0, 4, *(int*) 0x9a9214, 1);
	fcn_00468b80(*(int*) (w + 0xb0), *(int*) 0x14b54a4);
	fcn_00468bb0(*(int*) (w + 0xb0), 5, *(int*) 0x14b54ac,
	    *(int*) 0x14b54b0, *(int*) 0x14b54b4, *(int*) 0x14b54b8,
	    *(int*) 0x14b54bc);
	*(int*) (w + 0xb4) = fcn_004677e0(0x140, 0x32, 100, 0, 100, 0x7b, 0x82,
	    *(int*) &g_772514);
	fcn_00472380(*(int*) (w + 0xb4), 0, 100, *(int*) 0x9a9218, 1);
	fcn_00468b80(*(int*) (w + 0xb4), *(int*) 0x14b54a8);
	*(int*) (w + 0xc8) = fcn_0046f740(0x14, 0x17, 0x7d3, *(int*) &g_772514);
	((GUI_ROW_5893D0*)g_1015ea0)[*(int*) (w + 0xc8)].f5c = 1;
	((GUI_ROW_5893D0*)g_1015ea0)[*(int*) (w + 0xc8)].f1d0 = 3;
	*(int*) (w + 0xcc) = fcn_0046f740(0x56, 0x17, 0x7d1, *(int*) &g_772514);
	((GUI_ROW_5893D0*)g_1015ea0)[*(int*) (w + 0xcc)].f5c = 1;
	((GUI_ROW_5893D0*)g_1015ea0)[*(int*) (w + 0xcc)].f1d0 = 3;
	*(int*) (w + 0xd0) = fcn_0046f740(0x98, 0x17, 0x7d2, *(int*) &g_772514);
	((GUI_ROW_5893D0*)g_1015ea0)[*(int*) (w + 0xd0)].f5c = 1;
	((GUI_ROW_5893D0*)g_1015ea0)[*(int*) (w + 0xd0)].f1d0 = 3;
	*(int*) (w + 0xc0) = fcn_00470820(0, 0, (char*) 0x6a94c8);
	fcn_00471d80(*(int*) (w + 0xc0), 1);
	d2_SetForm(*(int*) (w + 0xc0), 0);
	fcn_00469c40(((D2_WIN*)g_1015f40)[g_772514].left, half - 0x4b,
	    ((D2_WIN*)g_1015f40)[g_772514].slot);
	d2_SetForm(*(int*) (w + 0xc0), 1);
	*(int*) (w + 0xa8) = fcn_004677e0(0x96, 0xb, 200, 0, 100, 0x75, 0x4c2,
	    *(int*) &g_772514);
	fcn_00472380(*(int*) (w + 0xa8), 0, 100,
	    (int) (fcn_005e8860(1) * 100.0f));
	fcn_00468b80(*(int*) (w + 0xa8), *(int*) 0x14b5498);
	*(int*) (w + 0xac) = fcn_004677e0(0x96, 0x1f, 200, 0, 100, 0x75, 0x4c2,
	    *(int*) &g_772514);
	fcn_00472380(*(int*) (w + 0xac), 0, 100,
	    (int) (fcn_005e8860(1) * 100.0f));
	fcn_00468b80(*(int*) (w + 0xac), *(int*) 0x14b549c);
	*(int*) (w + 0xc4) = fcn_004677e0(0x96, 0x33, 200, 0, 100, 0x75, 0x4c2,
	    *(int*) &g_772514);
	fcn_00472380(*(int*) (w + 0xc4), 0, 100,
	    (int) (*(float*) (a1 + *(int*) (w + 0xa0) * 4 + 8)
		* 100.0f));
	fcn_00468b80(*(int*) (w + 0xc4), *(int*) 0x14b54a0);
	*(int*) (w + 0x74) = fcn_00470820(0, 0, (char*) 0x6a94a8);
	fcn_00471d80(*(int*) (w + 0x74), 3);
	fcn_00471af0(*(int*) (w + 0x74), 0);
	*(int*) (w + 0x70) = *(int*) &g_6b7fac;
}
