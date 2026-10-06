typedef struct IDev IDev;
// SIZE 0xf8
typedef struct IDevVtbl {
	void* slots0[34];
	long (__stdcall* m88)(IDev*);
	void* slots8c[15];
	long (__stdcall* SetRenderState)(IDev*, int, int);
	void* slotscc[10];
	long (__stdcall* mf4)(IDev*, int, int);
} IDevVtbl;
// SIZE 0x4
struct IDev {
	IDevVtbl* v;
};

extern void* g_6b5de0;
#include "client_types.h"
extern Vec3_67bbdc g_67bbdc;
extern float g_1052bd8;
extern int g_1052bdc;
extern char g_1052c40;
extern char g_6b7ff9;
extern char g_6b7ffa;
extern unsigned char g_6b7ffd;
extern char g_67a2ac;

void __cdecl fcn_00450b20(float a, char* b, int c, int d);

// FUNCTION: GOLDTL 0x437160
void __cdecl fcn_00437160(unsigned char fog, int color, char light)
{
	((IDev*)g_6b5de0)->v->m88(((IDev*)g_6b5de0));
	((IDev*)g_6b5de0)->v->mf4(((IDev*)g_6b5de0), 0, 0);
	fcn_00450b20(1.0f, &(*(char*)&g_67bbdc), 0, 0);
	g_1052bd8 = 1.0f;
	g_1052bdc = 0;
	g_1052c40 = 0;
	((IDev*)g_6b5de0)->v->SetRenderState(((IDev*)g_6b5de0), 0x1c, fog);
	if (fog) {
		((IDev*)g_6b5de0)->v->SetRenderState(((IDev*)g_6b5de0), 0x22, color);
	}
	((IDev*)g_6b5de0)->v->SetRenderState(((IDev*)g_6b5de0), 7, light ? (g_6b7ff9 != 0) + 1 : 0);
	if (light) {
		((IDev*)g_6b5de0)->v->SetRenderState(((IDev*)g_6b5de0), 0xe, light && g_6b7ffa == 0);
		((IDev*)g_6b5de0)->v->SetRenderState(((IDev*)g_6b5de0), 0x2f, g_6b7ffa ? 0x10 : 0);
	}
	g_6b7ffd = fog;
	g_67a2ac = light;
}
