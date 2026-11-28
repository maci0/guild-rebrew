

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
extern float d3_ViewportZFar;
extern float d3_ProjectionDist;
extern float d3_ViewportZNear;
extern unsigned char gm_ClientModeFlags;
extern char g_6a41d4[];
extern char g_6a41c0[];
extern int g_7e1d40;
#include "Develop/client_types.h"
extern Page_1038144 d2_FormPageWindows[];
extern struct ctlinfo g_1015f50[];

void __cdecl d2_ClearScreen(void);
void __cdecl d2_UpdateViewportCenter(int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl d2_SetBackdropResource(int);
void __cdecl d3_SetViewport(float, float, float, float, int, int, int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_PositionControl(int, int, int);
void __cdecl d2_PositionWindow(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
void __cdecl d2_RenderAndPresentFrame(void);
#include "Develop/DieGildeAddOn/game/client_timer.h"
void __cdecl d2_LoadingScreenTimerCallback(void);

void __cdecl d2_ShowLoadingScreen(void)
{
	d2_SuppressOverlay = 1;
	d2_ClearScreen();
	d2_UpdateViewportCenter(0x24087);
	d2_SetBackdropResource(gm_RandomMod(2) == 1 ? 0x78e : 0x791);
	g_1040480 = -1;
	g_1040488 = -1;
	g_1040484 = -1;
	g_104048c = -1;
	d3_SetViewport((float) g_1040494, (float) d2_ScreenHeight, 0.0f, 0.0f, (*(int*)&d3_ViewportZNear), (*(int*)&d3_ViewportZFar), (*(int*)&d3_ProjectionDist), g_1040494, d2_ScreenHeight);
	if (gm_ClientModeFlags & 4) {
		g_7e1d40 = d2_LoadForm(0, 0, g_6a41d4);
	} else {
		g_7e1d40 = d2_LoadForm(0, 0, g_6a41c0);
	}
	d2_PositionControl(0, d2_ScreenHeight - g_1015f50[((struct dlgslot*)d2_FormPageWindows)[g_7e1d40].ctl].y - 0x30, g_1015f50[((struct dlgslot*)d2_FormPageWindows)[g_7e1d40].ctl].h);
	d2_PositionWindow(((struct dlgslot*)d2_FormPageWindows)[g_7e1d40].ctl, 1);
	d2_SetForm(g_7e1d40, 1);
	d2_AddWindowValueGauge(0, 0, 0x246, 0, 0x246, 0x83, 0x42, d2_CurrentWindowId);
	d2_RenderAndPresentFrame();
	tb_OpenFunction(d2_LoadingScreenTimerCallback, 7);
}
