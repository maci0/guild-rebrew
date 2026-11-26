void __cdecl he_FreeAction(char*);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;




char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl gm_GetBuildingTechEffect(char*, int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00565800(char* o)
{
	char* e;

	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0xac));
	if (e != 0) {
		gm_GetBuildingTechEffect(e, 0x10, 1);
		*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (o + 0x52), 0x18, 0, 0);
		*(int*) (o + 0x58) = 0;
		return;
	}
	he_FreeAction(o);
}
