void __cdecl he_FreeAction(char*);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;




char* __cdecl gm_LookupSpecialObject(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl he_AllocUnkendunk(char* o)
{
	char* t;

	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	t = gm_LookupSpecialObject(0x178);
	if (t != 0 && *(int*) (t + 4) != 0) {
		*(pos14_7f4c00*) (o + 0xb0) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (o + 0xb0), 0, *(int*) (t + 4), 0);
		return;
	}
	he_FreeAction(o);
}
