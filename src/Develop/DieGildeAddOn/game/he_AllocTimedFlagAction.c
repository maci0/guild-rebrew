#include "Develop/DieGildeAddOn/game/spiel.h"



#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl he_FreeAction(char*);

void __cdecl he_AllocTimedFlagAction(char* action)
{
	unsigned char* subentity;

	subentity = 0;
	*(pos14_7f4c00*) (action + 0xc0) = *(pos14_7f4c00*) (action + 0x44);
	gm_AddTime((pos14_7f4c00*) (action + 0xc0), 0, *(int*) (action + 0xb8) * *(int*) (action + 0xb0), 0);
	*(pos14_7f4c00*) (action + 0x52) = *(pos14_7f4c00*) (action + 0x44);
	gm_AddTime((pos14_7f4c00*) (action + 0x52), 0, 0, 1);
	gm_ResolveEntityById(0, (void**) (&subentity), 0, *(int*) (action + 0xac));
	if (subentity != 0) {
		if ((subentity[0x13] & 0x20) != 0) {
			he_FreeAction(action);
			return;
		}
		cm_RequestChangeBits(*(int*) (subentity + 2), 0x13, 1, 0x20, 0);
	}
	*(pos14_7f4c00*) (action + 0x60) = gm_GameTime;
	*(int*) (action + 0xb4) = subentity[0x12] + *(int*) (action + 0xb0) < 100 ? subentity[0x12] + *(int*) (action + 0xb0) : 100;
}
