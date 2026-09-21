/* friedhof_logic - gv_CheckSlotActive.  Split out of friedhof_dump.c: the reference
 * places gv_GetSlotEntry..gv_AllocGraveyardField between this function and its former file-mates, so one
 * object cannot be position-aligned.  Body unchanged.
 */


#include "rebrew_types.h"
#include "rebrew_globals.h"
// FUNCTION: GOLDTL 0x4f15d0
// SIZE: 128


int __cdecl gv_CheckSlotActive(void* slot, int type)
{
	if (type == 0) {
		if (*(int*) ((char*) slot + 8) != 0 && *(unsigned char*) ((char*) slot + 0x18) != 0)
			return 1;
		return 0;
	}
	if (type == 1) {
		if (*(int*) ((char*) slot + 0xc) != 0 && *(unsigned char*) ((char*) slot + 0x19) != 0)
			return 1;
		return 0;
	}
	if (type == 2) {
		if (*(int*) ((char*) slot + 0x10) != 0 && *(unsigned char*) ((char*) slot + 0x1a) != 0)
			return 1;
		return 0;
	}
	if (type == 3) {
		if (*(int*) ((char*) slot + 0x14) != 0 && *(unsigned char*) ((char*) slot + 0x1b) != 0)
			return 1;
		return 0;
	}
	return 1;
}
