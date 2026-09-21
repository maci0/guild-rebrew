#include <stdio.h>
#include "../../Units/Error/error.h"
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "office_slot.h"

void* __cdecl gm_LookupEntityRecordById(int);

extern char g_office_slots[]; /* 0x101de5a0 */

/* Validates if an entity is eligible for an office position.
 * Checks entity type, existing office holdings, and eligibility
 * requirements. Returns 0 on success, non-zero on failure. */

// FUNCTION: GOLDTL 0x4e8940
// SIZE: 151
// amt_ClearEntityLinks

int __cdecl amt_ClearEntityLinks(char* entity)
{
	OfficeSlot* slot;
	unsigned short default_val;
	int i;
	int result;
	int state_tmp;

	default_val = (unsigned short) g_current_hour;
	result = 0;
	slot = (OfficeSlot*) 0x101de5a0;
	for (i = 0; i < 0x2a; i++) {
		if (slot[i].entityId == *(int*) (entity + 4)) {
			slot[i].entityId = -1;
			slot[i].assignmentId = -1;
			state_tmp = (default_val > 0xb) ? 4 : 3;
			slot[i].state = (char) state_tmp;
			slot[i].count = 0;
			result |= 1;
		}
		else if (slot[i].assignmentId == *(int*) (entity + 4)) {
			slot[i].assignmentId = -1;
			slot[i].state = 1;
		}
	}
	if (*(char*) (entity + 0x168) != 0) {
		for (i = 0; i < 0x2a; i++) {
			if (slot[i].role == *(char*) (entity + 0x168)) {
				if (slot[i].count > 0) {
					slot[i].count--;
					result |= 1;
				}
			}
		}
	}
	*(char*) (entity + 0x166) = 0;
	*(char*) (entity + 0x169) = 0;
	*(char*) (entity + 0x168) = 0;
	return result;
}

/* Updates entity links for an office assignment. Sets up
 * the bidirectional references between the office slot and
 * the entity holding it. */
