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

// FUNCTION: GOLD 0x0042aef0
// FUNCTION: GOLDTL 0x4297c0
// gm_ResetAllEntities
extern char* g_6b7e94;
extern char* g_6b7e98;
extern void __cdecl fcn_00429670(unsigned char*);
void __cdecl gm_ResetAllEntities(void)
{
	int i;
	unsigned char* e;
	for (i = 0; i < 0x64c00; i += 0xc98) {
		e = ((unsigned char*)g_6b7e94) + i;
		if (e[0x124] & 1) {
			(*(unsigned char**)&g_6b7e98) = e;
			fcn_00429670(e);
		}
	}
	(*(unsigned char**)&g_6b7e98) = 0;
}

