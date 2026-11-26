


// SIZE 0x274
typedef struct {
	char pad0[0x228];
	int items[16];
	int owner2;
	int owner1;
	signed char first;
	signed char count;
} Panel;

extern int g_7747ac;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_SetGroupVisibility(int, int);
void __cdecl d2_TurnBookPagesBack(Panel*);
void __cdecl fcn_00535550(Panel*);
void __cdecl fcn_00471490(int);

void __cdecl d2_UpdatePagedPanel(Panel* panel)
{
	int i;

	if (panel == 0) {
		return;
	}
	for (i = 0; i < panel->count; i++) {
		if (i < panel->first || i > panel->first + 1) {
			d2_SetGroupVisibility(panel->items[i], 0);
		}
	}
	if (panel->owner1 != -1 && d2_CurrentElementId == panel->owner1 && g_14ce8cc != 0) {
		d2_TurnBookPagesBack(panel);
	}
	if (panel->owner2 != -1 && d2_CurrentElementId == panel->owner2 && g_14ce8cc != 0) {
		fcn_00535550(panel);
	}
	for (i = panel->first + (unsigned char) g_7747ac; i < panel->count; i++) {
		if (i > panel->first + (unsigned char) g_7747ac) {
			break;
		}
		fcn_00471490(panel->items[i]);
	}
	*(unsigned char*) &g_7747ac ^= 1;
}
