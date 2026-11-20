

#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef void (__stdcall* ClearFn)(D3D_DEVICE_VIEW*, int, int, int, int, float, int);












extern int g_6a2bdc;
extern int d2_SuppressOverlay;

extern int g_774710;
extern int d2_ScreenHeight;
extern int g_1040494;
extern char g_67d67c[];
extern int g_6a25ac;
extern int g_774670;

void __cdecl fcn_005270c0(int show);
void __cdecl fcn_00533cf0(int v);
int __cdecl fcn_004675f0(int x, int y, int w, int a, int b, int c, int d);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_DestroyElement(int h);
void __cdecl fcn_004730c0(int a, int b, int w, int h, char* s, int c, int d);
void __cdecl fcn_00527f60(int a, int b);
void __cdecl fcn_0046a110(int v);
void __cdecl fcn_0041bcb0(void);

void __cdecl d2_UpdateProgressOverlay(int phase, int cur, int max)
{
	if (g_6a2bdc == -1) {
		d2_SuppressOverlay = 1;
		fcn_005270c0(0);
		fcn_00533cf0(1);
		((ClearFn) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_00[36])(((D3D_DEVICE_VIEW*)g_6b5de0), 0, 0, 1, 0, 1.0f, 0);
		g_774710 = 0;
		g_6a2bdc = fcn_004675f0(g_1040494 / 2 - 0xcd, d2_ScreenHeight - 0x40, 0x190, 0, 0x190, 0x83, 0x42);
		d2_SetElementValue(g_6a2bdc, 0, 0x190, 0);
		if (g_6a2bdc == -1) {
			g_774710++;
			return;
		}
	}
	if (phase == 0) {
		d2_SetElementValue(g_6a2bdc, 0, 0x190, cur * 200 / max);
	} else if (phase == 1) {
		d2_SetElementValue(g_6a2bdc, 0, 0x190, cur * 200 / max + 200);
		if (cur >= max - 1) {
			d2_DestroyElement(g_6a2bdc);
			g_6a2bdc = -1;
			d2_SuppressOverlay = 0;
			fcn_004730c0(0, 0, g_1040494, d2_ScreenHeight, g_67d67c, 0x5a, 2);
			fcn_005270c0(1);
			fcn_00533cf0(0);
			if (g_6a25ac != -1) {
				fcn_00527f60(1, 0);
			}
			g_774670 = 1;
		}
	}
	if (g_774710 % 10 == 0 && g_6a2bdc != -1) {
		fcn_0046a110(1);
		fcn_0041bcb0();
	}
	g_774710++;
}
