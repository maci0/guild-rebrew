/* Refreshes the portrait graphics of one animation object: three slot frames,
   bars, the two counter labels and the position/displacement fields. */
#include "client_data.h"
int __cdecl d2_GetControlValue(int);
float __cdecl gm_CalcArtilleryVolleyCost(int, int, int);
void __cdecl gm_GetArtilleryLimits(char*, int*, int*);
void __cdecl d2_CreateGuiWindow(int, ...);
void __cdecl d2_SetElementEnabled(int, int);
int __cdecl gm_CanFireCannonShot(char*, int, int, int, int*, int*);
float __cdecl gm_GetNormalizedWeatherStrength(void);
#include "Develop/Units/d2.v1/d2_gui.h"
float __cdecl d2_CalcKanoneProgress(float*);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_EqualizeWindowButtonWidths(int, int, char*, int);
void __cdecl d2_SetElementFont(int, int);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
int __cdecl gm_GetSeasonTreasury(char*, unsigned char);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x00588200 */
void __cdecl d2_UpdateKanoneDialog(char* obj, char* panel, char* a2)
{
	int level;
	int percent;
	int max;
	int rec;
	int show;
	unsigned int v1;
	unsigned int v2;
	float f;
	char text[64];

	level = d2_GetControlValue(*(int*) (panel + 0xb0));
	percent = d2_GetControlValue(*(int*) (panel + 0xb4));
	f = gm_CalcArtilleryVolleyCost(level, percent, 1);
	gm_GetArtilleryLimits(obj, (int*) (panel + 0xdc), (int*) (panel + 0xe0));
	max = *(int*) (panel + 0xe0);
	if (max < level) {
		level = max;
	}
	d2_CreateGuiWindow(*(int*) (panel + 0xb0), 0, max, level);
	d2_SetElementEnabled(*(int*) (panel + 0xcc), 1 <= *(int*) (panel + 0xdc));
	d2_SetElementEnabled(*(int*) (panel + 0xd0), 2 <= *(int*) (panel + 0xdc));
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[*(int*) (panel + 0xc8)].value_03c =
	    *(int*) (panel + 0xa0) == 0;
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[*(int*) (panel + 0xcc)].value_03c =
	    *(int*) (panel + 0xa0) == 1;
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[*(int*) (panel + 0xd0)].value_03c =
	    *(int*) (panel + 0xa0) == 2;
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[*(int*) (panel + 0xc8)].value_038 =
	    *(int*) (panel + 0xa0) == 0;
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[*(int*) (panel + 0xcc)].value_038 =
	    *(int*) (panel + 0xa0) == 1;
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[*(int*) (panel + 0xd0)].value_038 =
	    *(int*) (panel + 0xa0) == 2;
	rec = gm_CanFireCannonShot((char*) (*(unsigned short*) &g_774970 * 0x21c + (unsigned long)&g_7f4ca0), level,
	                   percent, *(int*) (panel + 0xa0) + 1, (int*) &v1, (int*) &v2);
	show = *(float*) (panel + 0x20) <= 0.01f && rec != 0 &&
	       *(float*) (a2 + 8 + *(int*) (panel + 0xa0) * 4) >= f &&
	       (*(unsigned char*) (a2 + 4) & 2) == 0;
	d2_SetElementEnabled(*(int*) (panel + 0xb8), show);
	d2_SetElementEnabled(*(int*) (panel + 0xbc),
	             (~*(unsigned int*) (a2 + 4) >> 1) & 1);
	d2_CreateGuiWindow(*(int*) (panel + 0xa8), 0, 100, (int) (gm_GetNormalizedWeatherStrength() * 100.0f), 1);
	d2_CreateGuiWindow(*(int*) (panel + 0xac), 0, 100, (int) (d2_CalcKanoneProgress((float*) panel) * 100.0f), 1);
	d2_CreateGuiWindow(*(int*) (panel + 0xc4), 0, 100,
	             (int) (*(float*) (a2 + 8 + *(int*) (panel + 0xa0) * 4) * 100.0f), 1);
	d2_SetForm(*(int*) (panel + 0xc0), 2);
	io_AppendText(0x6811b0);
	rec = d2_EqualizeWindowButtonWidths(0, 0xf, *(char**) 0x14b54c0, *(int*) &d2_CurrentWindowId);
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[rec].value_06c = 1;
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[rec].width =
	    *(int*) (*(int*) &d2_CurrentWindowId * 0x3cc + (unsigned long)&g_1015f4c) / 2;
	d2_SetElementFont(rec, 0x54);
	io_FormatTextBuffer(text, (char*) 0x6a9480, v2, v1);
	rec = d2_EqualizeWindowButtonWidths(0, 0x23, text, *(int*) &d2_CurrentWindowId);
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[rec].value_06c = 1;
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[rec].width =
	    *(int*) (*(int*) &d2_CurrentWindowId * 0x3cc + (unsigned long)&g_1015f4c) / 2;
	d2_SetElementFont(rec, 0x54);
	rec = d2_EqualizeWindowButtonWidths(*(int*) (*(int*) &d2_CurrentWindowId * 0x3cc + (unsigned long)&g_1015f4c) / 2,
	                   0xf, *(char**) 0x14b54c4, *(int*) &d2_CurrentWindowId);
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[rec].value_06c = 1;
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[rec].width =
	    *(int*) (*(int*) &d2_CurrentWindowId * 0x3cc + (unsigned long)&g_1015f4c) / 2;
	d2_SetElementFont(rec, 0x54);
	io_FormatTextBuffer(text, (char*) 0x6a9480,
	             gm_GetSeasonTreasury((char*) (*(unsigned short*) &g_774970 * 0x21c + (unsigned long)&g_7f4ca0),
	                          *(unsigned char*) &g_773d75),
	             *(int*) (*(unsigned short*) &g_774970 * 0x21c + (unsigned long)&g_7f4ca0 + 0x194));
	rec = d2_EqualizeWindowButtonWidths(*(int*) (*(int*) &d2_CurrentWindowId * 0x3cc + (unsigned long)&g_1015f4c) / 2,
	                   0x23, text, *(int*) &d2_CurrentWindowId);
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[rec].value_06c = 1;
	((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[rec].width =
	    *(int*) (*(int*) &d2_CurrentWindowId * 0x3cc + (unsigned long)&g_1015f4c) / 2;
	d2_SetElementFont(rec, 0x54);
	*(int*) 0x9a9214 = level;
	*(int*) 0x9a9218 = percent;
	*(int*) 0x9a921c = *(int*) (panel + 0xa0);
	*(int*) 0x9a9208 = *(int*) (panel + 0x10);
	*(int*) 0x9a920c = *(int*) (panel + 0x14);
	*(int*) 0x9a9210 = *(int*) (panel + 0x18);
}
