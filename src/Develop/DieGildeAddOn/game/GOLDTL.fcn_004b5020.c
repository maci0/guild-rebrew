#include "g_7f4ca2.h"

extern Slot7f4ca2 g_7f4ca2[768];

char* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);


/* ADDRESS: GOLDTL 0x004b5020 */
int __cdecl fcn_004b5020(void)
{
	char* p;
	unsigned short h;

	for (p = gm_StartFilteredEntitySearch(1, 6); p != 0; p = gm_FindNextFilteredEntity()) {
		h = *(unsigned short*) (p + 0x27);
		if (h != 0xffff && g_7f4ca2[h].kind == 5)
			return 0;
	}
	return 1;
}
