/* gv_SpawnEntities - proper C */

// FUNCTION: SERVER 0x10010850
// SIZE: 370

#include "rebrew_types.h"
#include "rebrew_globals.h"
extern int g_next_object_id;
int __cdecl gm_RandomMod(int range);
void* __cdecl FindSlotEntryFiltered(void* filter_arg, void* entity, void* cursor,
                                    void* filter, int type);

/* Spawns up to *count* graveyard workers for the entity.  Validates the
 * entity type (0x1d) and maturity level (1..3), then fills each spawned
 * slot's record with a fresh object id, random stats and random role
 * values.  Returns the number of slots spawned. */

/* Byte-match note: RELOC 370/370.  The spawn loop must be a bare
 * `while (spawned < count)`; wrapping it in a redundant `if (count > 0)`
 * left the stat loop's store as `mov [edi+ecx+0x23],al` against the
 * reference's `mov [ecx+edi+0x23],al` (369/370).  The extra guard raises
 * register pressure enough to swap the SIB base and index roles.  The
 * addressing expression itself is not the lever: twelve spellings of the
 * store address (subscript, pointer walk, split index, addend order,
 * hoisted base) all emit identical bytes. */

int __cdecl gv_SpawnEntities(void* entity, int count)
{
	unsigned char type;
	unsigned char* taddr;
	void* slot;
	int i;
	int r;
	int spawned;

	type = *(unsigned char*) entity;
	taddr = (unsigned char*) (g_entity_type_table + type + type * 0x24c);
	if ((*taddr == 0x1d) && (*(taddr + 0x247) >= 1) && (*(taddr + 0x247) <= 3)) {
		spawned = 0;
		while (spawned < count) {
			slot = FindSlotEntryFiltered(0, entity, 0, (void*) 0x10010700, 0);
			if (slot == 0)
				break;
			*(int*) *(int*) ((char*) slot + 0x10) = g_next_object_id;
			g_next_object_id++;
			*(int*) ((char*) slot + 4) = *(int*) *(int*) ((char*) slot + 0x10);
			*(unsigned short*) ((char*) slot + 8) = 0x7fff;
			*(unsigned short*) ((char*) slot + 0xa) =
			    (unsigned short) (g_current_year + 5);
			*(unsigned char*) ((char*) slot + 0xc) = 0xff;
			for (i = 0; i < 5; i++) {
				r = gm_RandomMod(8) & 0xffff;
				*(unsigned char*) (i + *(int*) ((char*) slot + 0x10) + 0x24) =
				    (unsigned char) ((float) r * g_const_21_0 + g_const_42_0);
			}
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x2c) =
			    (gm_RandomMod(9) & 0xffff) + 1;
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x30) =
			    (gm_RandomMod(2) & 0xffff) + 1;
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x34) =
			    (gm_RandomMod(0x5e) & 0xffff) + 1;
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x40) =
			    g_current_year - (gm_RandomMod(4) & 0xffff) - 1;
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x38) =
			    gm_RandomMod(2) & 0xffff;
			gm_RandomMod(0x10);
			gm_RandomMod(0x10);
			gm_RandomMod(0x10);
			spawned++;
		}
	} else {
		spawned = 0;
	}
	return spawned;
}
