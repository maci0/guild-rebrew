extern unsigned char g_773d75;
extern int g_100f1dc;
extern char* g_77255c;
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_AccumulateTyped2(char*);
void __cdecl d2_ClampAmountToRange(int, int, int, int*);
int __cdecl gm_AmountToUnits(int, unsigned char);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterForm(int, int);
void __cdecl d2_SetForm(int, int);
char* __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, char*);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
int __cdecl d2_UpdateProgressBar(int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
char* __cdecl d2_GetControlValue(int);
int __cdecl gm_ConvertUnitsToAmount(char*, unsigned char);
void __cdecl d2_DestroyForm(int);


/* ADDRESS: GOLDTL 0x004e3de0 */
void __cdecl cut_RunAuctionBidDialog(char* a, int* b)
{
	int i;
	int val;
	int cap;
	int max;
	int lo;
	int hi;
	int dlg;
	int w;
	int bar;
	int x;
	char* o;
	char* t;

	*(int*) (a + 0x98) = 0;
	for (i = 0; i < b[0x12]; i++) {
		if (b[9 + i] == *(int*) (a + 0x10))
			break;
	}
	if (i >= b[0x12])
		return;
	if (b[i] == -1)
		return;
	*(int*) (a + 0x94) = b[8];
	gm_StartFilteredEntitySearch(1, 1, b[0x11]);
	val = b[8];
	o = gm_LookupEntityRecordById(*(int*) (a + 0x10));
	if (o == 0)
		return;
	cap = gm_AccumulateTyped2(o);
	d2_ClampAmountToRange(val, cap, 0x20, &max);
	lo = gm_AmountToUnits(val, g_773d75);
	hi = gm_AmountToUnits(max, g_773d75);
	if (cap < val)
		return;
	dlg = d2_LoadForm(0, 0, "cutscenes\\pacht");
	d2_CenterForm(dlg, 3);
	g_100f1dc = -1;
	d2_SetForm(dlg, 0);
	t = io_AppendText(0x1aa6, g_773d75);
	io_AppendText(0x1aa7);
	w = d2_GetWindowListItem(dlg, 0, t);
	d2_SetElementValue(w, lo, hi, lo);
	bar = d2_AddWindowValueGauge((*(int*) (g_77255c + 0xc) - 0x12c) / 2 - 8, 8, 0x12c, 0, 100, 0x75, 0x42, d2_CurrentWindowId);
	d2_UpdateProgressBar(bar, 0x5dc, 1);
	g_100f1dc = -1;
	while (main_RunFrameLoop(cut_RunAuctionBidDialog, cut_EventLoopFlags) != 0) {
		if (d2_UpdateProgressBar(bar, 0, 0) == 0) {
			g_774654 = 1;
		} else {
			x = g_100f1dc;
			if (x != -1) {
				g_774654 = 1;
				if (x != 1 && x == 2) {
					*(int*) (a + 0x98) = 1;
					*(int*) (a + 0x94) = gm_ConvertUnitsToAmount(d2_GetControlValue(w), g_773d75);
				}
			}
		}
	}
	d2_DestroyForm(dlg);
}
