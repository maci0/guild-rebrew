#include "../../game_structs.h"
#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"

#pragma intrinsic(memcpy, memset)

/* 0x43-byte node; same layout as LinkedNode in game_structs.h (the remove
 * helpers and gm_FreeObjectListRecursive spell it). This TU only reads the
 * two head fields, so it uses LinkedNode directly. */
#include "game_structs.h"
#define Record LinkedNode

extern int g_query_limit;
void __cdecl m_FreeTracked(void*);
void* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

// FUNCTION: GOLDTL 0x4297c0
// SIZE: 59
// gm_ResetAllEntities

void __cdecl gm_ResetAllEntities(void)
{
	int i;
	EntityQueryRecord* entity_cursor;
	for (i = 0; i < 0x100; i++) {
		entity_cursor = (EntityQueryRecord*) g_entity_ptr + i;
		if (entity_cursor->type != 0) {
			gm_CleanupBuildingEntity((unsigned char*) entity_cursor);
		}
	}
	{
		int* dst;
		int n;
		dst = (int*) g_entity_ptr;
		for (n = 0; n < 0x2a40; n++) {
			*dst++ = 0;
		}
	}
}

/* Cleans up object entities. Frees inventory objects and
 * linked item chains from all active entities. */
