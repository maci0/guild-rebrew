

// SIZE 0x3cc
typedef struct {
	char pad0[0x27c];
	int panel;
	char pad280[0x3cc - 0x280];
} Slot;

extern int g_6a25b8;
extern int g_6a2be0;
extern int g_6a25fc;
extern int d2_HudTopBarWindowId;
#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];
extern int g_7ea380[15];
extern int g_6a2578;
extern int g_6a257c;
extern int g_6a2580;
extern int g_6a2584;
extern int g_6a2588;
extern int g_6a258c;
extern int g_6a259c;
extern int g_6a2590;
extern int g_6a2594;
extern int g_6a25a0;
extern int g_6a25a4;

void __cdecl d2_SetFormVisibility(int h, int v);
void __cdecl d2_SetEventLeisteVisibility(int v);
void __cdecl d2_SetSlotVisibility(int h, int v);

/* ADDRESS: GOLDDE 0x00510370 */
void __cdecl d2_UpdateHudVisibility(int show)
{
	int i;

	g_6a2be0 = show;
	if (g_6a25b8 != -1) {
		d2_SetFormVisibility(g_6a25b8, show);
	}
	d2_SetEventLeisteVisibility(show);
	if (g_6a25b8 != -1) {
		d2_SetFormVisibility(g_6a25b8, show);
	}
	if (g_6a2578 != -1) {
		d2_SetSlotVisibility(g_6a2578, show);
	}
	if (g_6a257c != -1) {
		d2_SetSlotVisibility(g_6a257c, show);
	}
	if (g_6a2580 != -1) {
		d2_SetSlotVisibility(g_6a2580, show);
	}
	if (g_6a2584 != -1) {
		d2_SetSlotVisibility(g_6a2584, show);
	}
	if (g_6a2588 != -1) {
		d2_SetSlotVisibility(g_6a2588, show);
	}
	if (g_6a258c != -1) {
		d2_SetSlotVisibility(g_6a258c, show);
	}
	if (g_6a259c != -1) {
		d2_SetSlotVisibility(g_6a259c, show);
	}
	if (g_6a2590 != -1) {
		d2_SetSlotVisibility(g_6a2590, show);
	}
	if (g_6a2594 != -1) {
		d2_SetSlotVisibility(g_6a2594, show);
	}
	if (g_6a25fc != -1 && show == 0) {
		d2_SetSlotVisibility(g_6a25fc, show);
	}
	if (g_6a25a0 != -1) {
		d2_SetSlotVisibility(g_6a25a0, show);
	}
	if (g_6a25a4 != -1) {
		d2_SetSlotVisibility(g_6a25a4, show);
	}
	if (d2_HudTopBarWindowId != -1) {
		d2_SetSlotVisibility(((Slot*)d2_Windows)[d2_HudTopBarWindowId].panel, show);
	}
	for (i = 0; i < 15; i++) {
		if (g_7ea380[i] != -1) {
			d2_SetSlotVisibility(g_7ea380[i], show);
		}
	}
}
