#include "Develop/DieGildeAddOn/game/client_data.h"
#include "d2_gui.h"
#include "d2_win.h"
typedef struct { char pad00[0x5c]; int f5c; char pad60[0x1d0-0x60]; int f1d0; char pad1d4[0x2f4-0x1d4]; } GUI_ROW_5893D0;
int __cdecl d2_CreateElement(int x, int y, int a3);
int __cdecl d2_PositionControl(int x, int y, int win);
int __cdecl d2_AddElementToWindow(int x, int y, int a3, int win);
int __cdecl d2_LoadForm(int a0, int a1, char* text);
void __cdecl d2_CenterForm(int k, int flags);
void __cdecl d2_SetFormVisibility(int k, int flag);
int __cdecl d2_SetForm(int k, int i);
void __cdecl d2_CreateGuiWindow(int k, int a1, int a2, int a3, ...);
void __cdecl d2_SetValueGaugeLabel(int id, int value);
void __cdecl d2_SetValueGaugeStepLabels(int slot, int n, ...);
int __cdecl d2_AddWindowValueGauge(int x, int y, int a3, int a4, int a5, int a6, int a7, int win);
float __cdecl gm_GetNormalizedWeatherStrength(int a0);
extern char * d2_Controls; extern char d2_WindowElementIdView[]; extern float flt_100_0; extern int gm_GameTicks; extern char * d2_FileObjTable; extern int d2_CurrentWindowId;
/* ADDRESS: GOLDTL 0x005893d0 */
/* ADDRESS: GOLDDE 0x0056f090 */
void __cdecl d2_CreateCannonControls(int w, int a1)
{
	int width;
	int height;
	int half;
	int v;
	int id;
	int id2;

	width = g_1040494;
	height = d2_ScreenHeight;
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
	*(int*) (w + 0xd4) = d2_CreateElement(0, 0, id);
	*(int*) (w + 0xd8) = d2_CreateElement(0,
	    d2_ScreenHeight
	    - (int) ((D2_BILD_GROESSE*)d2_FileObjTable)[id2].hoehe, id2);
	*(int*) (w + 0xa4) = d2_LoadForm(0, 0, (char*) 0x6a94e8);
	d2_CenterForm(*(int*) (w + 0xa4), 1);
	d2_SetForm(*(int*) (w + 0xa4), 0);
	d2_PositionControl(((D2_WIN*)d2_Windows)[d2_CurrentWindowId].left, v - 0x19,
	    ((D2_WIN*)d2_Windows)[d2_CurrentWindowId].slot);
	d2_SetForm(*(int*) (w + 0xa4), 2);
	*(int*) (w + 0xb8) = d2_AddElementToWindow(0x59, 0xf, 0x7d5, *(int*) &d2_CurrentWindowId);
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[*(int*) (w + 0xb8)].value_05c) = 1;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[*(int*) (w + 0xb8)].flags_1d0) = 3;
	*(int*) (w + 0xbc) = d2_AddElementToWindow(0x9b, 0xf, 0x7d4, *(int*) &d2_CurrentWindowId);
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[*(int*) (w + 0xbc)].value_05c) = 1;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[*(int*) (w + 0xbc)].flags_1d0) = 3;
	d2_SetForm(*(int*) (w + 0xa4), 1);
	*(int*) (w + 0xb0) = d2_AddWindowValueGauge(0x140, 0x14, 100, 0, 100, 0x7b, 0x82,
	    *(int*) &d2_CurrentWindowId);
	d2_CreateGuiWindow(*(int*) (w + 0xb0), 0, 4, *(int*) 0x9a9214, 1);
	d2_SetValueGaugeLabel(*(int*) (w + 0xb0), *(int*) 0x14b54a4);
	d2_SetValueGaugeStepLabels(*(int*) (w + 0xb0), 5, *(int*) 0x14b54ac,
	    *(int*) 0x14b54b0, *(int*) 0x14b54b4, *(int*) 0x14b54b8,
	    *(int*) 0x14b54bc);
	*(int*) (w + 0xb4) = d2_AddWindowValueGauge(0x140, 0x32, 100, 0, 100, 0x7b, 0x82,
	    *(int*) &d2_CurrentWindowId);
	d2_CreateGuiWindow(*(int*) (w + 0xb4), 0, 100, *(int*) 0x9a9218, 1);
	d2_SetValueGaugeLabel(*(int*) (w + 0xb4), *(int*) 0x14b54a8);
	*(int*) (w + 0xc8) = d2_AddElementToWindow(0x14, 0x17, 0x7d3, *(int*) &d2_CurrentWindowId);
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[*(int*) (w + 0xc8)].value_05c) = 1;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[*(int*) (w + 0xc8)].flags_1d0) = 3;
	*(int*) (w + 0xcc) = d2_AddElementToWindow(0x56, 0x17, 0x7d1, *(int*) &d2_CurrentWindowId);
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[*(int*) (w + 0xcc)].value_05c) = 1;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[*(int*) (w + 0xcc)].flags_1d0) = 3;
	*(int*) (w + 0xd0) = d2_AddElementToWindow(0x98, 0x17, 0x7d2, *(int*) &d2_CurrentWindowId);
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[*(int*) (w + 0xd0)].value_05c) = 1;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[*(int*) (w + 0xd0)].flags_1d0) = 3;
	*(int*) (w + 0xc0) = d2_LoadForm(0, 0, (char*) 0x6a94c8);
	d2_CenterForm(*(int*) (w + 0xc0), 1);
	d2_SetForm(*(int*) (w + 0xc0), 0);
	d2_PositionControl(((D2_WIN*)d2_Windows)[d2_CurrentWindowId].left, half - 0x4b,
	    ((D2_WIN*)d2_Windows)[d2_CurrentWindowId].slot);
	d2_SetForm(*(int*) (w + 0xc0), 1);
	*(int*) (w + 0xa8) = d2_AddWindowValueGauge(0x96, 0xb, 200, 0, 100, 0x75, 0x4c2,
	    *(int*) &d2_CurrentWindowId);
	d2_CreateGuiWindow(*(int*) (w + 0xa8), 0, 100,
	    (int) (gm_GetNormalizedWeatherStrength(1) * 100.0f));
	d2_SetValueGaugeLabel(*(int*) (w + 0xa8), *(int*) 0x14b5498);
	*(int*) (w + 0xac) = d2_AddWindowValueGauge(0x96, 0x1f, 200, 0, 100, 0x75, 0x4c2,
	    *(int*) &d2_CurrentWindowId);
	d2_CreateGuiWindow(*(int*) (w + 0xac), 0, 100,
	    (int) (gm_GetNormalizedWeatherStrength(1) * 100.0f));
	d2_SetValueGaugeLabel(*(int*) (w + 0xac), *(int*) 0x14b549c);
	*(int*) (w + 0xc4) = d2_AddWindowValueGauge(0x96, 0x33, 200, 0, 100, 0x75, 0x4c2,
	    *(int*) &d2_CurrentWindowId);
	d2_CreateGuiWindow(*(int*) (w + 0xc4), 0, 100,
	    (int) (*(float*) (a1 + *(int*) (w + 0xa0) * 4 + 8)
		* 100.0f));
	d2_SetValueGaugeLabel(*(int*) (w + 0xc4), *(int*) 0x14b54a0);
	*(int*) (w + 0x74) = d2_LoadForm(0, 0, (char*) 0x6a94a8);
	d2_CenterForm(*(int*) (w + 0x74), 3);
	d2_SetFormVisibility(*(int*) (w + 0x74), 0);
	*(int*) (w + 0x70) = *(int*) &gm_GameTicks;
}
