


#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/client_straftat.h"
#pragma pack(push, 1)

// SIZE 0x2d
#pragma pack(pop)


int __cdecl cm_FindFreeCrimeSlot(void)
{
	int slot;
	int i;

	slot = -1;
	for (i = 0; i < 512; i++) {
		if (cm_CrimeRecords[i].state == 0) {
			slot = i;
			i = 512;
		}
	}
	return slot;
}
