/* spiel fragment D — object list helpers (gm_AddObjekt,
 * gm_SubObjekt, gm_SubObjectNoKill) and the filtered entity scanner. */


#include "../../Units/Error/error.h"

#include <stdio.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void* list, int obj_id);

extern unsigned char* g_query_filter_base; /* 0x10035464 */

// FUNCTION: GOLDTL 0x503e80
// SIZE: 352
// gm_FindNextFilteredEntity

void* __cdecl gm_FindNextFilteredEntity(void)
{
	unsigned char* list_head;
	unsigned char* end;
	unsigned char match;

	match = 0;
	if (g_entity_type_table == 0) {
		return 0;
	}
	end = (unsigned char*) g_entity_ptr + 0xa900;
	if (g_dynasty_field_4c > 0x100) {
		return 0;
	}
	if (g_dynasty_field_49 != 0) {
		list_head = g_query_filter_base;
		g_dynasty_field_49 = 0;
		if (list_head < end) {
			while (*list_head == 0) {
				list_head += 0xa9;
				g_query_filter_base = list_head;
				if (list_head >= end) {
					break;
				}
			}
		}
		goto candidate;
	} else {
		list_head = g_query_filter_base;
		do {
			list_head += 0xa9;
			g_query_filter_base = list_head;
			if (list_head < end) {
				goto a2;
			}
			return 0;
		a2:
			;
		} while (*list_head == 0);
	}
candidate:
	match = 0;
	if (list_head >= end) {
		return 0;
	}
	for (;;) {
		if (g_dynasty_field_48 != 0) {
			match = 1;
		}
		if (g_filter_extra5 != 0xff) {
			if (*list_head != g_filter_extra5) {
				goto no_match;
			}
			match = 1;
		}
		if (g_query_filter_extra1 != -1) {
			if (*(int*) (list_head + 1) != g_query_filter_extra1) {
				goto no_match;
			}
			match = 1;
		}
		if (g_query_filter_extra2 != 0x7fff) {
			if (*(short*) (list_head + 0x25) != g_query_filter_extra2) {
				goto no_match;
			}
			match = 1;
		}
		if (g_query_filter_extra3 != 0x7fff) {
			if (*(short*) (list_head + 0x27) != g_query_filter_extra3) {
				goto no_match;
			}
			match = 1;
		}
		if (g_query_filter_extra4 != 0xff) {
			match = (*(unsigned char*) ((char*) g_entity_type_table + *list_head + *list_head * 588) ==
			         g_query_filter_extra4);
		}
		goto counted;
	no_match:
		match = 0;
	counted:
		g_dynasty_field_4c++;
		if (match == 0) {
			while (*list_head == 0 || 1) {
				list_head += 0xa9;
				g_query_filter_base = list_head;
				if (list_head >= end) {
					break;
				}
				if (*list_head != 0) {
					break;
				}
			}
		}
		if (list_head >= end) {
			break;
		}
		if (match != 0) {
			break;
		}
	}
	if (match == 0) {
		g_query_filter_base = 0;
		list_head = 0;
	}
	return list_head;
}
