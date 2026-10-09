#include "../command_internal.h"

/* TL Ex-table handler, dispatch index 70 (the server's entry there is a no-op).
 * Looks up the entity whose id is at cmd+0x10; with a result buffer it writes
 * result[0] = found ? 1 : 2 and clears result[1] and result[6..9]. Always
 * returns 0. No string names it; the name is inferred. */

int __cdecl fcn_004f48e0(char* idPtr);

int __cdecl cm_ExFindEntity(int cmd, char* result)
{
	int found;

	found = fcn_004f48e0((char*) cmd + 0x10);
	if (result != (char*) 0x0) {
		result[1] = '\0';
		*result = (char) ((found == 0) + 1);
		*(int*) (result + 6) = 0;
	}
	return 0;
}
