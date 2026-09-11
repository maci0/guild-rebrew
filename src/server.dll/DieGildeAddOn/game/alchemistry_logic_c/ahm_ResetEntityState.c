/* ahm_ResetEntityState + ahm_CheckFlag - proper C */

#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

/* Resets an alchemy entity's operational state when its type is 1 or 2:
 * clears the link list head, marks the terminal link as -1 and bumps the
 * link counter. */

// FUNCTION: SERVER 0x1000BD50
// SIZE: 78

void __cdecl ahm_ResetEntityState(void* a)
{
	if (*(unsigned char*) ((char*) a + 2) == 1 ||
	    *(unsigned char*) ((char*) a + 2) == 2) {
		if (*(unsigned char*) ((char*) a + 0x164) != 0) {
			memset((char*) a + 0x1b4, 0, 0x10);
			*(int*) ((char*) a + 0x1c0) = -1;
			*(int*) ((char*) a + 0x1b4) |= 1;
		}
	}
}

/* Checks the flag state of an alchemy entity's linked record.  Returns
 * non-zero when the entity type table marks it as an alchemy building
 * (0x1e) and the record carries an allocated data pointer. */

// FUNCTION: SERVER 0x1000BDA0
// SIZE: 70


int __cdecl ahm_CheckFlag(void* a)
{
	char* rec;

	if (*(int*) ((char*) a + 0x1cc) & 4) {
		rec = *(char**) ((char*) a + 0x16c);
		if (rec != 0) {
			if (*(unsigned char*) (g_entity_type_table +
			    *(unsigned char*) rec + *(unsigned char*) rec * 0x24c) == 0x1e)
				return *(int*) (rec + 0x65) != 0;
		}
	}
	return 0;
}
