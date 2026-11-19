


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
void __cdecl fcn_00535560(Panel*);
void __cdecl fcn_00535550(Panel*);
void __cdecl fcn_00471490(int);

void __cdecl fcn_005350d0(Panel* p)
{
	int i;

	if (p == 0) {
		return;
	}
	for (i = 0; i < p->count; i++) {
		if (i < p->first || i > p->first + 1) {
			d2_SetGroupVisibility(p->items[i], 0);
		}
	}
	if (p->owner1 != -1 && d2_CurrentElementId == p->owner1 && g_14ce8cc != 0) {
		fcn_00535560(p);
	}
	if (p->owner2 != -1 && d2_CurrentElementId == p->owner2 && g_14ce8cc != 0) {
		fcn_00535550(p);
	}
	for (i = p->first + (unsigned char) g_7747ac; i < p->count; i++) {
		if (i > p->first + (unsigned char) g_7747ac) {
			break;
		}
		fcn_00471490(p->items[i]);
	}
	*(unsigned char*) &g_7747ac ^= 1;
}
