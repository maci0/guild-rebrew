#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl cm_ResolveSpecialEntityId(char*, int);



/* ADDRESS: GOLDTL 0x004c87d0 */
/* ADDRESS: GOLDDE 0x004b5fb0 */
int __cdecl fcn_004c87d0(char* command, char* result)
{
	char* dyn;
	char* stat;
	char* exist;
	char** src;
	char** dst;
	char* prev;
	int key;

	*(int*) (command + 0x14) = cm_ResolveSpecialEntityId(command, *(int*) (command + 0x14));
	if (gm_ResolveEntityById((void**) (&dyn), (void**) (&exist), (void**) (&stat), *(int*) (command + 0x14)) == 0)
		return 1;
	if (dyn != 0)
		src = (char**) (dyn + 0x5d);
	else if (exist != 0)
		src = (char**) (exist + 0x14);
	else
		src = (char**) (stat + 0x178);
	*(int*) (command + 0x10) = cm_ResolveSpecialEntityId(command, *(int*) (command + 0x10));
	if (gm_ResolveEntityById((void**) (&dyn), (void**) (&exist), (void**) (&stat), *(int*) (command + 0x10)) == 0)
		return 1;
	if (dyn != 0)
		dst = (char**) (dyn + 0x5d);
	else if (exist != 0)
		dst = (char**) (exist + 0x14);
	else
		dst = (char**) (stat + 0x178);
	key = cm_ResolveSpecialEntityId(command, *(int*) (command + 0x18));
	*(int*) (command + 0x18) = key;
	prev = 0;
	for (exist = *src; exist != 0; exist = *(char**) (exist + 0x3f)) {
		if (*(int*) (exist + 2) == key) {
			if (prev == 0)
				*src = *(char**) (exist + 0x3f);
			else
				*(char**) (prev + 0x3f) = *(char**) (exist + 0x3f);
			break;
		}
		prev = exist;
	}
	if (exist == 0)
		return 1;
	*(int*) (exist + 6) = *(int*) (command + 0x10);
	*(char**) (exist + 0x3f) = *dst;
	*dst = exist;
	if (result != 0)
		result[0] = 1;
	return 0;
}
