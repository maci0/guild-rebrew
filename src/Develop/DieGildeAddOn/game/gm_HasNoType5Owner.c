#include "Develop/DieGildeAddOn/game/g_7f4ca2.h"

extern Slot7f4ca2 g_7f4ca2[768];

char* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);


/* ADDRESS: GOLDTL 0x004b5020 */
int __cdecl gm_HasNoType5Owner(void)
{
	char* entity;
	unsigned short owner_slot;

	for (entity = gm_StartFilteredEntitySearch(1, 6); entity != 0; entity = gm_FindNextFilteredEntity()) {
		owner_slot = *(unsigned short*) (entity + 0x27);
		if (owner_slot != 0xffff && g_7f4ca2[owner_slot].kind == 5)
			return 0;
	}
	return 1;
}
