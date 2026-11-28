#include <string.h>
#include "Develop/DieGildeAddOn/game/client_data.h"

extern int __cdecl d2_CloseWindow(int a1);
extern int __cdecl d2_ReleaseSurface(void* o);

/* ADDRESS: GOLDTL 0x00471e30 */
void __cdecl d2_DestroyForm(int dialogIndex)
{
	D2_FORM_RECORD* base;
	int i;
	int* slot;
	int* items;

	if (dialogIndex > 0x30) {
		if (dialogIndex < 1) {
			return;
		}
	}
	base = &d2_Forms[dialogIndex];
	if (d2_Forms[dialogIndex].used == 0) {
		return;
	}
	items = (int*) d2_FormPageWindows;
	for (i = base->count - 1; i >= 0; i--) {
		d2_CloseWindow(items[dialogIndex * 175 + i]);
	}
	slot = (int*) base->h;
	for (i = 0; i < 2; i++) {
		if (slot[-2] != 0) {
			d2_ReleaseSurface((void*) slot[-2]);
		}
		if (slot[0] != 0) {
			d2_ReleaseSurface((void*) slot[0]);
		}
		slot++;
	}
	memset(base, 0, 700);
}
