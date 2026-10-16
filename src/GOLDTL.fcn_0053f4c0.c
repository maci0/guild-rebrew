

// SIZE 0x2bc
struct dlgslot {
	int ctl;
	char pad[0x2b8];
};

// SIZE 0x3cc
struct ctlinfo {
	int y;
	char pad4[0x268];
	int h;
	char pad270[0x15c];
};

extern int g_7725c8;
extern int g_1040480;
extern int g_1040484;
extern int g_1040488;
extern int g_104048c;
extern int g_1040490;
extern int g_1040494;
extern float g_10421a0;
extern float g_10432a4;
extern float g_10529c8;
extern unsigned char g_7747b0;
extern char g_6a41d4[];
extern char g_6a41c0[];
extern int g_7e1d40;
#include "client_types.h"
extern Page_1038144 g_1038144[];
extern struct ctlinfo g_1015f50[];
extern int g_772514;

void __cdecl fcn_0046b4f0(void);
void __cdecl fcn_00537320(int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_00469e30(int);
void __cdecl fcn_00438da0(float, float, float, float, int, int, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl fcn_00471c00(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_0046ac30(void);
#include "client_timer.h"
void __cdecl fcn_0053f4b0(void);

void __cdecl fcn_0053f4c0(void)
{
	g_7725c8 = 1;
	fcn_0046b4f0();
	fcn_00537320(0x24087);
	fcn_00469e30(gm_RandomMod(2) == 1 ? 0x78e : 0x791);
	g_1040480 = -1;
	g_1040488 = -1;
	g_1040484 = -1;
	g_104048c = -1;
	fcn_00438da0((float) g_1040494, (float) g_1040490, 0.0f, 0.0f, (*(int*)&g_10529c8), (*(int*)&g_10421a0), (*(int*)&g_10432a4), g_1040494, g_1040490);
	if (g_7747b0 & 4) {
		g_7e1d40 = fcn_00470820(0, 0, g_6a41d4);
	} else {
		g_7e1d40 = fcn_00470820(0, 0, g_6a41c0);
	}
	fcn_00469c40(0, g_1040490 - g_1015f50[((struct dlgslot*)g_1038144)[g_7e1d40].ctl].y - 0x30, g_1015f50[((struct dlgslot*)g_1038144)[g_7e1d40].ctl].h);
	fcn_00471c00(((struct dlgslot*)g_1038144)[g_7e1d40].ctl, 1);
	fcn_004727a0(g_7e1d40, 1);
	fcn_004677e0(0, 0, 0x246, 0, 0x246, 0x83, 0x42, g_772514);
	fcn_0046ac30();
	fcn_0042de90(fcn_0053f4b0, 7);
}
