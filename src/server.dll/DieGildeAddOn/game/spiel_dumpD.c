/* spiel fragment D — object list helpers (gm_AddOrAccumulateObject,
 * gm_SubObjekt, gm_SubObjektNoKill) and the filtered entity scanner. */

// CFLAGS: /O2 /Gd

#include "../../Units/Error/error.h"

#include <stdio.h>

int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void* list, int obj_id);

extern int g_entity_type_table; /* 0x100a8c30 */
extern unsigned char* g_entity_ptr; /* 0x1014d8c0 */
extern unsigned char* g_query_filter_base; /* 0x10035464 */
extern short g_query_filter_extra2; /* 0x10030b8c */
extern short g_query_filter_extra3; /* 0x10030b8e */
extern unsigned char g_filter_extra5; /* 0x10030b84 */
extern int g_query_filter_extra1; /* 0x10030b88 */
extern unsigned char g_query_filter_extra4; /* 0x10030b90 */
extern unsigned char g_dynasty_field_48; /* 0x10035448 */
extern unsigned char g_dynasty_field_49; /* 0x10035449 */
extern int g_dynasty_field_4c; /* 0x1003544c */

/* Adds b units of object a to the list reachable from the resolved parent
 * entity, or accumulates the amount into an existing entry.  Returns the
 * entry pointer (or the result of gm_AllocObjekt when a new entry was
 * created). */

// FUNCTION: SERVER 0x10016cd0
// gm_AddOrAccumulateObject

int __cdecl gm_AddOrAccumulateObject(int a, int b, int c)
{
	char* p;
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
	if (dyn != 0) p = (char*) dyn + 0x5d;
	else if (exi != 0) p = (char*) exi + 0x14;
	else if (sta != 0) p = (char*) sta + 0x178;
	else return 0;
	exi = (void*) gm_StartEntityQuery(*(int*) p, 1, 0, b);
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
	char* p;
	void* dyn;
	void* sta;

	if (!gm_ResolveEntityById(&dyn, (void**) &a, &sta, a)) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xe2d,
		                   "gm_SubObjekt(): Parent not found", 1);
		return 0;
	}
	if (dyn != 0) p = (char*) dyn + 0x5d;
	else if (a != 0) p = (char*) a + 0x14;
	else if (sta != 0) p = (char*) sta + 0x178;
	else return 0;
	a = (int) gm_StartEntityQuery(*(int*) p, 1, 0, b);
	if (a == 0) {
		return 0;
	}
	if (*(int*) (a + 0xe) < c) {
		return 0;
	}
	*(int*) (a + 0xe) -= c;
	if (*(int*) (a + 0xe) <= 0) {
		gm_RemoveObjectByType(p, b);
	}
	return 1;
}

/* Like gm_SubObjekt but keeps the list entry alive: a missing entry is
 * allocated with a negative count instead of failing.  Returns 1. */

// FUNCTION: SERVER 0x10016ea0
// gm_SubObjektNoKill

int __cdecl gm_SubObjektNoKill(int a, int b, int c)
{
	char* p;
	void* dyn;
	void* sta;
	int orig_a;

	orig_a = a;
	if (!gm_ResolveEntityById(&dyn, (void**) &a, &sta, a)) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xe5c,
		                   "gm_SubObjectNoKill(): Parent not found", 1);
		return 0;
	}
	if (dyn != 0) p = (char*) dyn + 0x5d;
	else if (a != 0) p = (char*) a + 0x14;
	else if (sta != 0) p = (char*) sta + 0x178;
	else return 0;
	a = (int) gm_StartEntityQuery(*(int*) p, 1, 0, b);
	if (a == 0) {
		a = (int) gm_AllocObjekt(orig_a, b, 1);
		*(int*) (a + 0xe) = 0;
	}
	*(int*) (a + 0xe) -= c;
	if (*(int*) (a + 0xe) != 0) {
		return 1;
	}
	gm_RemoveObjectByType(p, b);
	return 1;
}

/* Scans the entity array for the next entity matching the active filter
 * state (set up by gm_StartFilteredEntitySearch).  Advances the search
 * cursor, counts inspected candidates, and returns the first match or
 * NULL once the array is exhausted. */

// FUNCTION: SERVER 0x10016f80
// FindNextFilteredEntity

void* __cdecl FindNextFilteredEntity(void)
{
	unsigned char* p;
	unsigned char* end;
	unsigned char match;

	match = 0;
	end = (unsigned char*) g_entity_ptr + 0xa900;
	if (g_entity_type_table == 0) {
		return 0;
	}
	if (g_dynasty_field_4c > 0x100) {
		return 0;
	}
	if (g_dynasty_field_49 != 0) {
		g_dynasty_field_49 = 0;
		p = g_query_filter_base;
		if (p >= end) {
			return 0;
		}
		do {
			if (*p != 0) {
				goto candidate;
			}
			p += 0xa9;
			g_query_filter_base = p;
		} while (p < end);
		goto candidate;
	} else {
		p = g_query_filter_base;
		do {
			p += 0xa9;
			g_query_filter_base = p;
			if (p >= end) {
				return 0;
			}
		} while (*p == 0);
	}
candidate:
	if (p >= end) {
		return 0;
	}
	for (;;) {
		if (g_dynasty_field_48 != 0) {
			match = 1;
		}
		if (g_filter_extra5 != 0xff) {
			if (*p != g_filter_extra5) {
				goto no_match;
			}
			match = 1;
		}
		if (g_query_filter_extra1 != -1) {
			if (*(int*) (p + 1) != g_query_filter_extra1) {
				goto no_match;
			}
			match = 1;
		}
		if (g_query_filter_extra2 != 0x7fff) {
			if (*(short*) (p + 0x25) != g_query_filter_extra2) {
				goto no_match;
			}
			match = 1;
		}
		if (g_query_filter_extra3 != 0x7fff) {
			if (*(short*) (p + 0x27) != g_query_filter_extra3) {
				goto no_match;
			}
			match = 1;
		}
		if (g_query_filter_extra4 != 0xff) {
			match = (*(unsigned char*) ((char*) g_entity_type_table + *p + *p * 588) ==
			         g_query_filter_extra4);
		}
		goto counted;
	no_match:
		match = 0;
	counted:
		g_dynasty_field_4c++;
		if (match != 0) {
			return p;
		}
		for (;;) {
			p += 0xa9;
			g_query_filter_base = p;
			if (p >= end) {
				break;
			}
			if (*p != 0) {
				break;
			}
		}
		if (p >= end) {
			if (match != 0) {
				return p;
			}
			g_query_filter_base = 0;
			return 0;
		}
		if (match != 0) {
			return p;
		}
	}
}
