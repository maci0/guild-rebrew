


#include "Develop/client_types.h"
extern Slot_779d00 main_CameraBookmarks[];

char* __cdecl gm_FindBuildingPrimarySlot(char*);
char* __cdecl gm_SetupEntityQuery(char*);

/* ADDRESS: GOLDDE 0x00578290 */
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
	*(int*) (((char*)main_CameraBookmarks) + 4 + idx * 12) = *(int*) (e + 1);
	if (r != 0) {
		*(int*) (((char*)main_CameraBookmarks) + 8 + idx * 12) = *(int*) (r + 2);
		return;
	}
	*(int*) (((char*)main_CameraBookmarks) + 8 + idx * 12) = -1;
}
