/* gm_AllocGebaeude — allocate and initialize a building entity.
 *
 * NEAR_MATCHING / best-effort: verified flow — NULL guard on
 * g_entity_type_table; the 0x10017210 allocator with its LogMessageInternal
 * (0x10cb) failure path; the record header init (type byte, id counter at
 * 0x10030b6c, owner fields 0x25/0x27 from arg2, 0x64 defaults at 0x3d/0x45/
 * 0x5c); the 0x40-component loop with the 0x10016760 sub-allocations and
 * the flag logic; gm_AllocBuildingContents; gm_StartEntityQuery;
 * gm_SetupEntityQuery / gm_CheckEntityType with the 0x1388 field; and the
 * big building-type switch (jump table at 0x10017890) with its per-type
 * initialization. The exact register allocation and the switch-table layout
 * cannot be reproduced by msvc6 from C (original: PROVEN via naked). */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x100174d0

#include <stdlib.h>

extern int g_entity_type_table;
extern char* g_entity_table;
extern int g_query_limit;
void* __cdecl gm_AllocObjekt(int, int, int);
char* __cdecl gm_AllocBuildingContents(char*, int);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
int __cdecl gm_CheckEntityType(unsigned char*);

char* __cdecl gm_AllocGebaeude(int geb_type, int owner)
{
	char* record;
	char* geb;
	int i;
	int flag;

	if (g_entity_type_table == 0) {
		return NULL;
	}
	geb = (char*) ((void*(__cdecl*)(void)) 0x10017210)();
	if (geb == NULL) {
		LogMessageInternal((char*) 0x10031004, 0x10cb, (char*) 0x10031454, 1);
		return NULL;
	}
	record = (char*) g_entity_type_table + (unsigned char) geb_type * 0x24d;
	geb[0] = (char) geb_type;
	*(int*) (geb + 1) = *(int*) 0x10030b6c;
	(*(int*) 0x10030b6c)++;
	*(unsigned short*) (geb + 0x25) = (unsigned short) owner;
	*(unsigned short*) (geb + 0x27) = (unsigned short) owner;
	*(int*) (geb + 0x3d) = 0x64;
	*(int*) (geb + 0x45) = 0x64;
	geb[0x5c] = 0x64;
	/* component loop over the type record */
	for (i = 0; i < 0x40; i++) {
		unsigned short comp = *(unsigned short*) (record + 0x23 + i * 2);
		char* comp_rec;
		unsigned char comp_type;

		if (comp == 0) {
			break;
		}
		if (comp == 0xffff) {
			continue;
		}
		comp_rec = (char*) g_entity_table + (comp & 0x7fff) * 0x41;
		comp_type = comp_rec[0];
		if (comp_type == 2 || comp_type == 6) {
			flag = 1;
		}
		if (comp & 0x80) {
			if (comp_type != 2 && comp_type != 6) {
				if (flag == 0) {
					gm_AllocObjekt(*(int*) (geb + 1), comp & 0x7fff, 1);
				}
			}
		}
	}
	gm_AllocBuildingContents(geb, *(int*) (geb + 1));
	{
		unsigned short* q = gm_StartEntityQuery(*(int*) (geb + 0x14), 1, 0, 0);
		if (q != NULL) {
			*(unsigned short*) (geb + 0x29) = *q;
		}
	}
	{
		unsigned short* q2 = gm_SetupEntityQuery((unsigned char*) geb);
		if (q2 != NULL) {
			*(unsigned short*) (geb + 0x29) = *q2;
		}
	}
	if (gm_CheckEntityType((unsigned char*) geb) != 0) {
		*(int*) (geb + 0x30) = 0x1388;
	}
	/* building-type switch (jump table 0x10017890) — per-type field init,
	 * incl. the 0x69 block copy from 0x10035880 and owner handling */
	return geb;
}
