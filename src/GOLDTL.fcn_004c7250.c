#include "Develop/DieGildeAddOn/game/spiel.h"



int __cdecl fcn_004c4dc0(char*, int);


int __cdecl fcn_004c7250(char* x)
{
	char* e1;
	char* e2;
	char* e3;
	char* p;

	*(int*) (x + 0x10) = fcn_004c4dc0(x, *(int*) (x + 0x10));
	if (gm_ResolveEntityById((void**) (&e1), (void**) (&e2), (void**) (&e3), *(int*) (x + 0x10)) == 0)
		return 1;
	p = e1 != 0 ? e1 : (e2 != 0 ? e2 : e3);
	if (e3 != 0 && p + *(int*) (x + 0x14) == e3 + 0x1c8 && (*(int*) (x + 0x1c) & 0x800000) != 0 &&
	    (*(int*) (e3 + 0x1c8) & 0x800000) != 0)
		return 1;
	return 0;
}
