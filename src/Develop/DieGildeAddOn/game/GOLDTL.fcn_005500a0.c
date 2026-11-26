#include "Develop/DieGildeAddOn/game/spiel.h"
extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;





void __cdecl he_FreeAction(char*);
int __cdecl fcn_004c6090(unsigned char*, int, int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl fcn_005500a0(char* o)
{
	unsigned char* e;
	BUILDING_PROTOTYPE* t;

	e = 0;
	gm_ResolveEntityById((void**) (&e), 0, 0, *(int*) (o + 0xb0));
	if (e == 0) {
		he_FreeAction(o);
	}
	t = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e];
	*(int*) (o + 0xbc) = fcn_004c6090(e, 0, t->role_22f, 0);
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, 6, 0);
}
