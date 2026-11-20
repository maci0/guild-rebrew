#include "Develop/DieGildeAddOn/game/object_prototype.h"


typedef struct
{
	char type;
	char name[0x40];
} Name41;
// SIZE 0x41

extern char* lpObjektePROT;

int __cdecl fcn_005014d0(int i)
{
	OBJECT_PROTOTYPE* e;

	e = &((OBJECT_PROTOTYPE*)lpObjektePROT)[i];
	if ((*(char *)&e->kind) == 1 || (*(char *)&e->kind) == 0x1a || (*(char *)&e->kind) == 0xb || (*(char *)&e->kind) == 0x1c || (*(char *)&e->kind) == 0x1b ||
	    (*(char *)&e->kind) == 3 || (*(char *)&e->kind) == 4) {
		return 1;
	}
	return 0;
}
