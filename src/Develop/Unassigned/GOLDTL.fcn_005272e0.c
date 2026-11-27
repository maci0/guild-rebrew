


#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6a259c;
extern int g_6a258c;
extern int g_6a25a4;

void __cdecl d2_SetFormVisibility(int h, int v);
#ifdef REBREW_GOLD
#define d2_DestroyElement fcn_0046e700
#endif
void __cdecl d2_DestroyElement(int h);
void __cdecl d2_SetSlotVisibility(int h, int v);

void __cdecl d2_DestroyHudOverlay(void)
{
	if (g_6a25b8 != -1) {
		d2_SetFormVisibility(g_6a25b8, 0);
	}
	if (g_6a2578 != -1) {
		d2_DestroyElement(g_6a2578);
		g_6a2578 = -1;
	}
	if (g_6a257c != -1) {
		d2_DestroyElement(g_6a257c);
		g_6a257c = -1;
	}
	if (g_6a2580 != -1) {
		d2_DestroyElement(g_6a2580);
		g_6a2580 = -1;
	}
	if (g_6a259c != -1) {
		d2_DestroyElement(g_6a259c);
		g_6a259c = -1;
	}
	if (g_6a2584 != -1) {
		d2_DestroyElement(g_6a2584);
		g_6a2584 = -1;
	}
	if (g_6a2588 != -1) {
		d2_DestroyElement(g_6a2588);
		g_6a2588 = -1;
	}
	if (g_6a258c != -1) {
		d2_DestroyElement(g_6a258c);
		g_6a258c = -1;
	}
	if (g_6a2590 != -1) {
		d2_DestroyElement(g_6a2590);
		g_6a2590 = -1;
	}
	if (g_6a2594 != -1) {
		d2_DestroyElement(g_6a2594);
		g_6a2594 = -1;
	}
	if (g_6a25a0 != -1) {
		d2_DestroyElement(g_6a25a0);
		g_6a25a0 = -1;
	}
	if (g_6a25a4 != -1) {
		d2_DestroyElement(g_6a25a4);
		g_6a25a4 = -1;
	}
	if (g_6a25fc != -1) {
		d2_SetSlotVisibility(g_6a25fc, 0);
	}
}
