


#include "Develop/client_types.h"
extern Slot_779d00 g_779d00[];

char* __cdecl gm_FindBuildingPrimarySlot(char*);
char* __cdecl gm_SetupEntityQuery(char*);

void __cdecl d2_SetBookmarkSlotEntity(int idx, char* e)
{
	char* r;

	r = 0;
	if (*e != 0x1d) {
		r = gm_FindBuildingPrimarySlot(e);
		if (r == 0) {
			r = gm_SetupEntityQuery(e);
		}
	}
	*(int*) (((char*)g_779d00) + 4 + idx * 12) = *(int*) (e + 1);
	if (r != 0) {
		*(int*) (((char*)g_779d00) + 8 + idx * 12) = *(int*) (r + 2);
		return;
	}
	*(int*) (((char*)g_779d00) + 8 + idx * 12) = -1;
}
