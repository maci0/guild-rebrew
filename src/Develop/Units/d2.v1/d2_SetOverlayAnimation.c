#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67d8cc;
extern short d2_CursorStateId;

void* __cdecl d2_GetResourceData(int resource_id);
void __cdecl d2_ClearAnimationSlot(int h);
int __cdecl d2_AllocAnimationSlot(short x, short y, void* img, int a4);

/* ADDRESS: GOLDTL 0x00473a90 */
void __cdecl d2_SetOverlayAnimation(int unused_arg, int resource_id)
{
	if (resource_id) {
		if (g_67d8cc != -1) {
			d2_ClearAnimationSlot(g_67d8cc);
			g_67d8cc = -1;
		}
		g_67d8cc = d2_AllocAnimationSlot((short) d2_MouseX, (short) d2_MouseY, d2_GetResourceData(resource_id), 0);
	} else {
		if (g_67d8cc != -1) {
			d2_ClearAnimationSlot(g_67d8cc);
			g_67d8cc = -1;
		}
		d2_CursorStateId = 0;
	}
}
