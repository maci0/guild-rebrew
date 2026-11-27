#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl cm_ResolveSpecialEntityId(void*, int);

char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl gm_RemoveObjectByType(char*, int);


/* ADDRESS: GOLDTL 0x004c8920 */
int __cdecl cm_ExClearStorageSlot(char* request, char* result)
{
	char* f;
	char* e;

	*(int*) (request + 0x10) = cm_ResolveSpecialEntityId(request, *(int*) (request + 0x10));
	if (gm_ResolveEntityById(0, (void**) (&f), 0, *(int*) (request + 0x10)) == 0)
		return 1;
	if (*(short*) f != 0x2a && *(short*) f != 0x116)
		return 1;
	e = fcn_00502cd0(*(int*) (f + 0x14), 1, 0, *(unsigned short*) (request + 0x14));
	if (e == 0)
		return 1;
	if (*(int*) (e + 0xe) != 1)
		return 1;
	gm_RemoveObjectByType(f + 0x14, *(unsigned short*) (request + 0x14));
	if (result != 0)
		*result = 1;
	return 0;
}
