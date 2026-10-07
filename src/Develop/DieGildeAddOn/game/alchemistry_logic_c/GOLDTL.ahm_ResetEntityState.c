/* ahm_ResetEntityState + ahm_CheckFlag - proper C */

#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

/* Resets an alchemy entity's operational state when its type is 1 or 2:
 * clears the link list head, marks the terminal link as -1 and bumps the
 * link counter. */

/* The GOLDTL 0x4ec850 bytes are this CheckFlag body (NEAR 59/70: the
 * `pop esi` placement around the 0x1e branch is a layout decision — two
 * spellings emit identical bytes) (flag test at +0x1cc,
 * chain at +0x16c, type-table walk, +0x65 pointer test) — not the server
 * ResetEntityState shape. Shared file, per-build marker: only CheckFlag
 * carries GOLDTL here. */

// FUNCTION: GOLDTL 0x4ec850
int __cdecl ahm_CheckFlag(void* a)
{
	char* rec;
	unsigned char type;

	if (*(int*) ((char*) a + 0x1cc) & 4) {
		rec = *(char**) ((char*) a + 0x16c);
		if (rec != 0) {
			type = *(unsigned char*) (g_entity_type_table +
			    *(unsigned char*) rec + *(unsigned char*) rec * 0x24c);
			if (type == 0x1e) {
				return *(int*) (rec + 0x65) != 0;
			}
		}
	}
	return 0;
}
