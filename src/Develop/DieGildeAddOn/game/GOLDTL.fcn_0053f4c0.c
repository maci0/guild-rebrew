

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

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ScreenHeight;
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

void __cdecl d2_ClearScreen(void);
void __cdecl fcn_00537320(int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl d2_SetBackdropResource(int);
void __cdecl fcn_00438da0(float, float, float, float, int, int, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl d2_PositionWindow(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
void __cdecl d2_RenderAndPresentFrame(void);
#include "client_timer.h"
void __cdecl fcn_0053f4b0(void);

void __cdecl d2_ShowLoadingScreen(void)
{
	d2_SuppressOverlay = 1;
	d2_ClearScreen();
	fcn_00537320(0x24087);
	d2_SetBackdropResource(gm_RandomMod(2) == 1 ? 0x78e : 0x791);
	g_1040480 = -1;
	g_1040488 = -1;
	g_1040484 = -1;
	g_104048c = -1;
	fcn_00438da0((float) g_1040494, (float) d2_ScreenHeight, 0.0f, 0.0f, (*(int*)&g_10529c8), (*(int*)&g_10421a0), (*(int*)&g_10432a4), g_1040494, d2_ScreenHeight);
	if (g_7747b0 & 4) {
		g_7e1d40 = fcn_00470820(0, 0, g_6a41d4);
	} else {
		g_7e1d40 = fcn_00470820(0, 0, g_6a41c0);
	}
	fcn_00469c40(0, d2_ScreenHeight - g_1015f50[((struct dlgslot*)g_1038144)[g_7e1d40].ctl].y - 0x30, g_1015f50[((struct dlgslot*)g_1038144)[g_7e1d40].ctl].h);
	d2_PositionWindow(((struct dlgslot*)g_1038144)[g_7e1d40].ctl, 1);
	d2_SetForm(g_7e1d40, 1);
	d2_AddWindowValueGauge(0, 0, 0x246, 0, 0x246, 0x83, 0x42, d2_CurrentWindowId);
	d2_RenderAndPresentFrame();
	tb_OpenFunction(fcn_0053f4b0, 7);
}
