#include "Develop/DieGildeAddOn/game/spiel.h"



int __cdecl fcn_004c4dc0(char*, int);


int __cdecl fcn_004c8cb0(char* x, char* out)
{
	char* e1;
	char* e2;
	char* e3;
	char* p;

	*(int*) (x + 0x10) = fcn_004c4dc0(x, *(int*) (x + 0x10));
	if (gm_ResolveEntityById((void**) (&e1), (void**) (&e2), (void**) (&e3), *(int*) (x + 0x10)) == 0)
		return 1;
	p = e1 != 0 ? e1 : (e2 != 0 ? e2 : e3);
	p += *(int*) (x + 0x14);
	switch (*(int*) (x + 0x18)) {
	case 1:
		*p &= ~*(char*) (x + 0x20);
		*p |= *(char*) (x + 0x1c);
		break;
	case 2:
		*(short*) p &= ~*(short*) (x + 0x20);
		*(short*) p |= *(short*) (x + 0x1c);
		break;
	case 4:
		*(int*) p &= ~*(int*) (x + 0x20);
		*(int*) p |= *(int*) (x + 0x1c);
		break;
	}
	if (out != 0)
		*out = 1;
	return 0;
}
