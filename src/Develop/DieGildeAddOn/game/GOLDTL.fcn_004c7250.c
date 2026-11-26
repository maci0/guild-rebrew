#include "Develop/DieGildeAddOn/game/spiel.h"



int __cdecl cm_ResolveSpecialEntityId(char*, int);


int __cdecl cm_ChkChangeBits(char* cmd)
{
	char* e1;
	char* e2;
	char* e3;
	char* target;

	*(int*) (cmd + 0x10) = cm_ResolveSpecialEntityId(cmd, *(int*) (cmd + 0x10));
	if (gm_ResolveEntityById((void**) (&e1), (void**) (&e2), (void**) (&e3), *(int*) (cmd + 0x10)) == 0)
		return 1;
	target = e1 != 0 ? e1 : (e2 != 0 ? e2 : e3);
	if (e3 != 0 && target + *(int*) (cmd + 0x14) == e3 + 0x1c8 && (*(int*) (cmd + 0x1c) & 0x800000) != 0 &&
	    (*(int*) (e3 + 0x1c8) & 0x800000) != 0)
		return 1;
	return 0;
}
