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

extern int g_query_limit;
extern unsigned char g_slot_table[2];
extern int g_next_object_id; /* defined in spiel.c */
int g_current_year;

extern int g_citizen_count;
extern float g_const_1_5; /* 0x10025fb4 */
extern float g_const_2_2; /* 0x10025fb0 */
extern float g_const_0_06875; /* 0x10025fac */
extern float g_const_896_0; /* 0x10025fa8 */
extern double g_const_1_over_720; /* 0x10025fa0 */
extern float g_const_0_0; /* 0x100256cc */
extern float g_gv_const_57c8; /* 0x100257c8 */
extern double g_const_half; /* 0x100257d0 */
extern unsigned char g_current_season;

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









