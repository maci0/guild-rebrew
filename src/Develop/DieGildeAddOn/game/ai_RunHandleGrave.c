#include "Develop/DieGildeAddOn/game/spiel.h"

void __cdecl gv_RequestRentGrave(int a1, int x, int a3, int a4, int a5);
void __cdecl gv_SendMoveSlotEntry(int a1, int a2, int x, int a4, int a5, int a6);

/* ADDRESS: GOLDTL 0x00490130 */
int __cdecl ai_RunHandleGrave(int a1, char* p, char* q)
{
	int targetEntity;

	gm_ResolveEntityById((void**) (&targetEntity), 0, 0, *(int*) (p + 0xc));
	if (!targetEntity) {
		return 0;
	}
	if (*(int*) (p + 0x10) == 4) {
		gv_RequestRentGrave(a1, targetEntity, *(int*) (p + 4), 10, *(int*) (p + 8));
		return 0x3e;
	}
	if (*(int*) (p + 0x10) == 5) {
		gv_SendMoveSlotEntry(a1, *(int*) (p + 4), targetEntity, *(int*) (q + 4), *(int*) (q + 0x10), *(int*) (p + 8));
		return 0x3e;
	}
	return 0;
}
