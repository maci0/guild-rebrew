

typedef struct IDev IDev;
// SIZE 0x100
typedef struct IDevVtbl {
	void* slots0[50];
	long (__stdcall* SetRenderState)(IDev*, int, int);
	void* slotscc[12];
	long (__stdcall* SetTextureStageState)(IDev*, int, int, int);
} IDevVtbl;
// SIZE 0x4
struct IDev {
	IDevVtbl* v;
};

#include "client_types.h"
extern void* g_6b5de0;
extern VECTOR3 g_67bbdc;
extern float g_1052bd8;
extern int g_1052bdc;
extern char g_1052c40;
extern char g_6b7ffa;
extern unsigned char g_6b7ffb;
extern unsigned char g_6b7ffc;
extern unsigned char g_6b7ffd;
extern unsigned char g_6b7ffe;
extern unsigned char g_6b7fff;
extern char g_6b8000;
char g_67a2ac = 1;

void __cdecl fcn_00450b20(float a, char* b, int c, char d);

void __cdecl fcn_004372d0(unsigned char alpha, unsigned char flags, int color, unsigned char test, unsigned char cull)
{
	float f;
	unsigned char b;

	f = (float) alpha * (1.0f / 255.0f);
	if (alpha < 0xff || (flags & 1) != 0) {
		if (g_6b7ffa == 0) {
			if (g_67a2ac) {
				((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x2f, 0x10);
				((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0xe, 0);
			}
			((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x1b, 1);
			g_6b7ffa = 1;
		}
		if ((flags & 1) != 0 && g_6b7ffb == 0) {
			((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x14, 2);
			((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x13, 2);
			if (g_6b7ffd) {
				((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x1c, 0);
			}
			g_6b7ffb = 1;
		} else if ((flags & 1) == 0) {
			((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x14, 6);
			((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x13, 5);
			if (g_6b7ffd) {
				((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x1c, 1);
			}
			g_6b7ffb = 0;
		}
	} else if (g_6b7ffa != 0) {
		if (g_67a2ac) {
			((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x2f, 0);
			((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0xe, 1);
		}
		((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x1b, 0);
		((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x14, 1);
		((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x13, 2);
		g_6b7ffa = 0;
		g_6b7ffb = 0;
	}
	if (f != g_1052bd8 || color != g_1052bdc) {
		fcn_00450b20((float) alpha * (1.0f / 255.0f), (char*)&g_67bbdc, color, flags & 1);
		g_1052bd8 = f;
		g_1052c40 = flags;
		g_1052bdc = color;
	}
	if (test != g_6b7ffc) {
		((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0xf, test);
		((IDev*)g_6b5de0)->v->SetTextureStageState(g_6b5de0, 0, 4, test ? 4 : 3);
		g_6b7ffc = test;
	}
	if (test) {
		((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x18, g_6b7ffa ? 0 : 0xbf);
	}
	if (cull != g_6b7ffe) {
		((IDev*)g_6b5de0)->v->SetRenderState(g_6b5de0, 0x16, cull ? 1 : (g_6b8000 ? 2 : 3));
		g_6b7ffe = cull;
	}
	b = (flags >> 1) & 1;
	if (b != g_6b7fff) {
		g_6b7fff = b;
		((IDev*)g_6b5de0)->v->SetTextureStageState(g_6b5de0, 0, 0xb, b ? 0x30000 : 0);
		((IDev*)g_6b5de0)->v->SetTextureStageState(g_6b5de0, 0, 0x18, g_6b7fff ? 2 : 0);
	}
}
