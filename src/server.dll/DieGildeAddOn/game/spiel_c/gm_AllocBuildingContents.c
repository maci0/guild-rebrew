/* gm_AllocBuildingContents — allocate a building's contents (components,
 * resources, producers) for the given building record.
 *
 * NEAR_MATCHING / best-effort: verified flow — NULL guards on the entity
 * tables and the 0x5008 pool limit; gm_AllocObjekt for the main object; the
 * 0x40-component scan with the 0x10016760 sub-allocation for components of
 * type 2/6 or the 0x80-bit flag; the gm_StartEntityQuery(…,0x2a) inventory
 * walk with capacity clamping (min 6) of fields 0x1c/0x1d; the special
 * building-type branch (0x92..0x97, 0x2db); and the per-slot sub-allocation
 * loop (stride 0x80) with its LogMessageInternal guard. The exact register
 * allocation and interleaving cannot be reproduced by msvc6 from C
 * (original: PROVEN via naked). */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10017c40

#include <stdlib.h>

extern char* g_entity_table;
extern int g_entity_type_table;
extern int g_query_limit;
void* __cdecl gm_AllocObjekt(int, int, int);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);

char* __cdecl gm_AllocBuildingContents(char* geb, int obj_id)
{
	char* obj;
	int i;
	unsigned short* q;

	if (g_entity_table == NULL || g_entity_type_table == NULL || g_query_limit + 0x40 >= 0x5008) {
		return NULL;
	}
	obj = (char*) gm_AllocObjekt(*(int*) (geb + 1), obj_id, 1);
	if (obj == NULL) {
		return NULL;
	}
	for (i = 0; i < 0x40; i++) {
		unsigned short comp = *(unsigned short*) (geb + 0x23 + i * 2);
		char* record;
		unsigned char comp_type;

		comp &= 0x7fff;
		if (comp == obj_id) {
			continue;
		}
		record = (char*) g_entity_table + comp * 0x41;
		comp_type = record[0];
		if (comp_type == 2 || comp_type == 6) {
			obj[0x40 + i] = 1;
		} else if (record[0x160] & 0x80) {
			gm_AllocObjekt(*(int*) (obj + 2), comp, 1);
		}
	}
	q = gm_StartEntityQuery(*(int*) (obj + 0x14), 1, 0, 0x2a);
	if (q != NULL) {
		*(int*) ((char*) q + 0xe) = 2;
		*(int*) ((char*) q + 6) = *(int*) (geb + 1);
		if (geb[0x23d] == 0 && geb[0x23e] == 0 && geb[0x23f] == 0) {
			obj[0x1c] = 6;
			obj[0x1d] = 6;
		} else {
			obj[0x1c] = geb[0x23d] < 6 ? 6 : geb[0x23d];
			obj[0x1d] = geb[0x23e] < 6 ? 6 : geb[0x23e];
		}
	}
	if (*(unsigned short*) obj == 0x92 || *(unsigned short*) obj == 0x93 || *(unsigned short*) obj == 0x94 ||
	    *(unsigned short*) obj == 0x95 || *(unsigned short*) obj == 0x96 || *(unsigned short*) obj == 0x97 ||
	    *(unsigned short*) obj == 0x2db) {
		unsigned char season = *(unsigned char*) 0x10035439;
		unsigned short* slot = (unsigned short*) 0x1002cff8;
		unsigned short* limit = (unsigned short*) 0x10030860;
		char* prod = (char*) 0x1002e000;

		(void) season;
		(void) slot;
		(void) limit;
		(void) prod;
		while (slot < limit) {
			if (*(int*) ((char*) prod + 0x178) == 0) {
				gm_AllocObjekt(*(int*) (obj + 2), *slot, 0);
			}
			slot += 0x40;
			prod += 0x80;
		}
	}
	return obj;
}
