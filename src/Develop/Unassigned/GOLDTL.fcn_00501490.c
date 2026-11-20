#include "Develop/DieGildeAddOn/game/object_prototype.h"


typedef struct
{
	char type;
	char name[0x40];
} Name41;
// SIZE 0x41

extern char* lpObjektePROT;

int __cdecl fcn_0065f220(char*, char*);

int __cdecl gm_FindObjektPrototypeByName(char* name)
{
	int i;

	for (i = 0; i < 0x2dc; i++) {
		if (fcn_0065f220(name, (char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[i] + 1) == 0) {
			return i;
		}
	}
	return 0;
}
