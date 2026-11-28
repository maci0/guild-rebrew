typedef struct Slot {
	char pad0[0x20];
	int type;
	char pad24[0x88 - 0x24];
	int result;
	char pad8c[0x2f4 - 0x8c];
} Slot;
// SIZE 0x2f4

#include "Develop/client_types.h"
typedef Anim_100e7a0 Anim;
// SIZE 0x14

extern char* d2_Controls;
extern Anim_100e7a0 g_100e7a0[0x30];
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00473030 */
void __cdecl d2_SetControlAnimationState(int slot, char mode)
{
	Slot* s;

	if (slot > 0x400) {
		return;
	}
	s = (Slot*) &((D2_CONTROL_TL*) d2_Controls)[slot];
	if (((D2_CONTROL_TL*) s)->kind != 4) {
		return;
	}
	if (mode == 0) {
		g_100e7a0[((D2_CONTROL_TL*) s)->value_088].frame = 0;
		g_100e7a0[((D2_CONTROL_TL*) s)->value_088].running = 0;
	} else if (mode == 1) {
		g_100e7a0[((D2_CONTROL_TL*) s)->value_088].frame = g_100e7a0[((D2_CONTROL_TL*) s)->value_088].seq[0x16] - 1;
		g_100e7a0[((D2_CONTROL_TL*) s)->value_088].running = 1;
	}
}
