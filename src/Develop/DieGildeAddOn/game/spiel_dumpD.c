#include "../../Units/Error/error.h"

#include <stdio.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void* list, int obj_id);

extern unsigned char* g_query_filter_base; 

extern unsigned char g_filter_extra5; /* 0x10030b84 */

extern int g_query_filter_extra1; /* 0x10030b88 */

extern short g_query_filter_extra2; /* 0x10030b8c */

extern short g_query_filter_extra3; /* 0x10030b8e */

extern unsigned char g_query_filter_extra4; /* 0x10030b90 */
extern char g_dynasty_name_ready; /* 0x10035448 */
extern char g_dynasty_scan_flag; /* 0x10035449 */
extern int g_dynasty_scan_count; /* 0x1003544c */

/* Adds b units of object a to the list reachable from the resolved parent
 * entity, or accumulates the amount into an existing entry.  Returns the
 * entry pointer (or the result of gm_AllocObjekt when a new entry was
 * created). */
// FUNCTION: GOLDTL 0x503e80
// SIZE: 352
// FUNCTION: SERVER 0x10016cd0
// gm_AddObjekt

int __cdecl gm_AddObjekt(int a, int b, int c)
{
	char* list_head;
	void* dyn;
	void* exi;
	void* sta;

	if (b == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xdf4,
		                   "gm_AddObjekt(): obj == ob_NULL", 1);
		return 0;
	}
	if (!gm_ResolveEntityById(&dyn, &exi, &sta, a)) {
		char buf[0x200];
		sprintf(buf, "gm_AddObjekt(): Parent not found. ObjProt:%i Menge:%i", b, c);
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xdfd, buf, 8);
		return 0;
	}
	if (dyn != 0) list_head = (char*) dyn + 0x5d;
	else if (exi != 0) list_head = (char*) exi + 0x14;
	else if (sta != 0) list_head = (char*) sta + 0x178;
	else return 0;
	exi = (void*) gm_ff_Objekt(*(int*) list_head, 1, 0, b);
	if (exi == 0) {
		return (int) gm_AllocObjekt(a, b, c);
	}
	*(int*) ((char*) exi + 0xe) += c;
	return (int) exi;
}

/* Removes c units of object b from the list reachable from the resolved
 * parent entity.  When the entry's count drops to zero the entry is
 * removed from the list.  Returns 1 on success, 0 on failure. */

// FUNCTION: SERVER 0x10016de0
// gm_SubObjekt

int __cdecl gm_SubObjekt(int a, int b, int c)
{
	char* list_head;
	void* dyn;
	void* sta;

	if (!gm_ResolveEntityById(&dyn, (void**) &a, &sta, a)) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xe2d,
		                   "gm_SubObjekt(): Parent not found", 1);
		return 0;
	}
	if (dyn != 0) list_head = (char*) dyn + 0x5d;
	else if (a != 0) list_head = (char*) a + 0x14;
	else if (sta != 0) list_head = (char*) sta + 0x178;
	else return 0;
	a = (int) gm_ff_Objekt(*(int*) list_head, 1, 0, b);
	if (a == 0) {
		return 0;
	}
	if (*(int*) (a + 0xe) < c) {
		return 0;
	}
	*(int*) (a + 0xe) -= c;
	if (*(int*) (a + 0xe) <= 0) {
		gm_RemoveObjectByType(list_head, b);
	}
	return 1;
}

/* Like gm_SubObjekt but keeps the list entry alive: a missing entry is
 * allocated with a negative count instead of failing.  Returns 1.
 *
 * The query result reuses `exi` (the resolve out-param) rather than a
 * separate `int r`: the extra local claimed its own frame slot and shifted
 * the whole stack layout.  Reusing `exi` gives the target's slot
 * assignment (exi = [esp+0x18]) and its lazy `push esi` before the query
 * call.  The tail is one merged `if (count == 0) remove;` + `return 1`,
 * not an early `return 1` on the non-zero path. */

// FUNCTION: SERVER 0x10016ea0
// gm_SubObjectNoKill

int __cdecl gm_SubObjectNoKill(int a, int b, int c)
{
	char* list_head;
	void* exi;
	void* dyn;
	void* sta;

	if (!gm_ResolveEntityById(&dyn, &exi, &sta, a)) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xe5c,
		                   "gm_SubObjectNoKill(): Parent not found", 1);
		return 0;
	}
	if (dyn != 0) list_head = (char*) dyn + 0x5d;
	else if (exi != 0) list_head = (char*) exi + 0x14;
	else if (sta != 0) list_head = (char*) sta + 0x178;
	else return 0;
	exi = (void*) gm_ff_Objekt(*(int*) list_head, 1, 0, b);
	if (exi == 0) {
		exi = (void*) gm_AllocObjekt(a, b, 1);
		*(int*) ((char*) exi + 0xe) = 0;
	}
	*(int*) ((char*) exi + 0xe) -= c;
	if (*(int*) ((char*) exi + 0xe) == 0) {
		gm_RemoveObjectByType(list_head, b);
	}
	return 1;
}


/* Scans the entity array for the next entity matching the active filter
 * state (set up by gm_StartFilteredEntitySearch).  Advances the search
 * cursor, counts inspected candidates, and returns the first match or
 * NULL once the array is exhausted.
 *
 * Byte-identical to the reference apart from relocations.  What the match
 * depends on:
 *   - `match` and `end` are set before the two entry guards, which gives the
 *     reference's prologue (`push esi; xor cl,cl; lea esi,[eax+0xa900]`).
 *   - No `return` inside the pre-scan cursor loops.  A return in the
 *     no-flag advance loop made msvc6 merge every `return 0` into one far
 *     block; without it each entry guard keeps its own inline
 *     `xor eax,eax; pop esi; ret`, as in the reference.
 *   - Both pre-scan loops walk g_query_filter_base itself, and the local is
 *     read from it afterwards.  With a local cursor msvc6 hoisted the global
 *     load above the flag test and threaded the flag-49 loop's exit.
 *   - The scan loop is `while (match == 0)`, so its back edge is the
 *     reference's `test cl,cl; je top` with the epilogue duplicated after it.
 *   - Each filter mismatch is its own `else { match = 0; goto counted; }`.
 *     msvc6 cross-jumps the four copies into one out-of-line block, which is
 *     where the reference has it; a shared `no_match:` label kept the block
 *     inline after the last filter.
 *   - The advance loop's odd `while (*list_head == 0 || 1)` head is
 *     load-bearing: `for (;;)` and a do/while both change the object. */

// FUNCTION: SERVER 0x10016f80

// gm_FindNextFilteredEntity

void* __cdecl gm_FindNextFilteredEntity(void)
{
	unsigned char* list_head;
	unsigned char* end;
	unsigned char match;

	match = 0;
	end = (unsigned char*) g_entity_ptr + 0xa900;
	if (g_entity_type_table == 0) {
		return 0;
	}
	if (g_dynasty_scan_count > 0x100) {
		return 0;
	}
	if (g_dynasty_scan_flag != 0) {
		g_dynasty_scan_flag = 0;
		while (g_query_filter_base < end) {
			if (*g_query_filter_base != 0) {
				break;
			}
			g_query_filter_base += 0xa9;
		}
	} else {
		do {
			g_query_filter_base += 0xa9;
		} while (g_query_filter_base < end && *g_query_filter_base == 0);
	}
	list_head = g_query_filter_base;
	if (list_head >= end) {
		return 0;
	}
	while (match == 0) {
		if (g_dynasty_name_ready != 0) {
			match = 1;
		}
		if (g_filter_extra5 != 0xff) {
			if (*list_head == g_filter_extra5) {
				match = 1;
			} else {
				match = 0;
				goto counted;
			}
		}
		if (g_query_filter_extra1 != -1) {
			if (*(int*) (list_head + 1) == g_query_filter_extra1) {
				match = 1;
			} else {
				match = 0;
				goto counted;
			}
		}
		if (g_query_filter_extra2 != 0x7fff) {
			if (*(short*) (list_head + 0x25) == g_query_filter_extra2) {
				match = 1;
			} else {
				match = 0;
				goto counted;
			}
		}
		if (g_query_filter_extra3 != 0x7fff) {
			if (*(short*) (list_head + 0x27) == g_query_filter_extra3) {
				match = 1;
			} else {
				match = 0;
				goto counted;
			}
		}
		if (g_query_filter_extra4 != 0xff) {
			match = (*(unsigned char*) ((char*) g_entity_type_table + *list_head + *list_head * 588) ==
			         g_query_filter_extra4);
		}
	counted:
		g_dynasty_scan_count++;
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
	}
	if (match == 0) {
		g_query_filter_base = 0;
		list_head = 0;
	}
	return list_head;
}
