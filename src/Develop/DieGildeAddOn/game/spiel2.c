#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"
#include "game_data.h"

#pragma intrinsic(memcpy, memset)

extern unsigned char g_slot_table[2];

/* Scans the per-entity slot table for an entry whose 16-bit id
 * matches arg2. Each entity owns 0x2a90 bytes at 0x1009b770,
 * holding 0x55 slots of 0x80 bytes; returns the matching slot
 * pointer or NULL. */

// DATA: SERVER 0x1009b770
// FUNCTION: SERVER 0x10016240
// gm_FindSlotById


char* __cdecl gm_FindSlotById(int arg1, int arg2)
{
	int i;

	for (i = 0; i < 0x55; i++) {
		if (*(unsigned short*) (0x1009b770 + arg1 * 0x2a90 + i * 0x80) == arg2) {
			return (char*) (0x1009b770 + arg1 * 0x2a90 + i * 0x80);
		}
	}
	return 0;
}

/* Returns the next matching entity from an active query.
 * Advances the query iterator and returns the next entity
 * that matches the query criteria. */









