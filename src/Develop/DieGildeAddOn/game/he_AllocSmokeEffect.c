#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl he_FreeAction(char*);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;





char* __cdecl gm_LookupSpecialObject(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl he_AllocSmokeEffect(char* o)
{
	char* e;
	char* t;

	gm_ResolveEntityById((void**) (&e), 0, 0, *(int*) (o + 0xac));
	if (e != 0 && *(int*) (e + 0x61) != 0) {
		t = gm_LookupSpecialObject(*(unsigned short*) (o + 0xc2));
		if (t != 0 && *(int*) (t + 4) != 0) {
			*(pos14_7f4c00*) (o + 0xb4) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (o + 0xb4), 0, *(int*) (t + 4), 0);
			*(int*) (o + 0xb0) = 0;
			*(int*) (o + 0x70) = 0;
			return;
		}
	}
	he_FreeAction(o);
}
