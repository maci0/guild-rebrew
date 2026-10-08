#include "../../Units/Error/error.h"
int __cdecl find_zone_record(char* base, int x, int y);

/* Plant records (TANNE, BUCHE, EICHE) and a zero-id terminator, walked by
 * lb_SearchRecordTable.  A struct object 8-aligns this TU's .data, which the
 * reference shows (four zero bytes at 0x1002d874). */
// SIZE 0x46
typedef struct {
	unsigned short id;   /* +0x00 */
	char name[0x40];     /* +0x02 */
	unsigned char f42;   /* +0x42 */
	unsigned char f43;   /* +0x43 */
	unsigned short f44;  /* +0x44 */
} PLANT_INFO;

PLANT_INFO g_plant_info_table[4] = {
	{ 0x1b7, "TANNE", 3, 1, 4 },
	{ 0x1b8, "BUCHE", 5, 1, 4 },
	{ 0x1b9, "EICHE", 5, 2, 8 },
	{ 0, "", 0, 1, 0 },
};


extern int g_dynamic_count;

/* Finds a record in a linked table by matching type fields.
 * Iterates from base pointer, comparing type1/type2 bytes.
 * Returns pointer to matching record or NULL. */

/* Checks if a zone is available for planting. Validates
 * the zone record, checks plant capacity, and verifies
 * the zone type matches the requested plant type. */


char* __cdecl lb_SearchRecordTable(int key)
{
	unsigned int idx;

	idx = 0;
	while (*(unsigned short*) ((char*) &g_plant_info_table + idx * 0x46) != 0) {
		if ((int) *(unsigned short*) ((char*) &g_plant_info_table + idx * 0x46) == key)
			return (char*) &g_plant_info_table + idx * 0x46;
		idx++;
	}
	return 0;
}

char* __cdecl plt_FindRecord(char* base, unsigned int type1, unsigned int type2)
{
	int i;
	char* record_cursor;
	unsigned char marker;

	i = 0;
	record_cursor = base + 9;
	marker = 0xff;
	while (i < 0x40) {
		if ((unsigned char) record_cursor[-1] == type1 && (unsigned char) record_cursor[0] == type2 && record_cursor[4] != (char) marker) {
			return base + i * 0x18;
		}
		i++;
		record_cursor += 0x18;
	}
	return (char*) 0;
}
/* Client-only plant-record lookups (the Gold T&L client's plant order).  No
 * server function calls them, so /OPT:REF discards them. */

char* __cdecl plt_FindRecordByOwner(char* base, int owner)
{
	char* p;
	int i;

	for (i = 0, p = base + 0x14; i < 0x40; i++, p += 0x18) {
		if (p[-7] != (char) 0xff && *(int*) p == owner) {
			return base + i * 0x18;
		}
	}
	return 0;
}

char* __cdecl plt_FindRecordById(char* base, int id)
{
	char* p;
	int i;

	for (i = 0, p = base; i < 0x40; i++, p += 0x18) {
		if (p[0xd] != (char) 0xff && *(int*) p == id) {
			return base + i * 0x18;
		}
	}
	return 0;
}

int __cdecl find_zone_record(char* base, int x, int y)
{
	int i;
	char* rec;
	int center;
	i = 0;
	rec = base + 8;
	while (i < 64) {
		if (*(rec + 5) == (char) 0xff) {
			goto next;
		}
		center = (signed char) *(rec + 4) / 2;
		if (x < (int) (unsigned char) *rec - center) {
			goto next;
		}
		if (x > (int) (unsigned char) *rec + center) {
			goto next;
		}
		if (y < (int) (unsigned char) *(rec + 1) - center) {
			goto next;
		}
		if (y <= (int) (unsigned char) *(rec + 1) + center) {
			return (int) (base + i * 24);
		}
	next:
		i++;
		rec += 24;
	}
	return 0;
}

/* Finds a zone record by x/y coordinates. Searches linked
 * records for a matching grid position. Returns record index
 * or -1 if not found. */

int __cdecl plt_CheckZoneAvailability(int zone_table, unsigned int x, unsigned int y, int zone_type)
{
	int i;
	int j;
	int found_free;
	char* zone_cursor;

	found_free = 0;
	i = 0;
	zone_cursor = (char*) (zone_table + 8);
	while (i < 0x40) {
		if (*(signed char*) (zone_cursor + 5) == (char) 0xff) {
			found_free = 1;
		} else if ((unsigned char) *zone_cursor == x && (unsigned char) *(zone_cursor + 1) == y) {
			return 0;
		}
		i++;
		zone_cursor += 0x18;
	}
	if (found_free == 0)
		return 0;
	for (j = 0; j < zone_type; j++) {
		for (i = 0; i < zone_type; i++) {
			if (find_zone_record(zone_table, x + i - zone_type / 2, y + j - zone_type / 2))
				return 0;
		}
	}
	return 1;
}

/* Sets/updates a plant map entry. Creates or modifies a
 * zone record with the specified plant type and coordinates.
 * Returns the record pointer on success. */

int __cdecl plt_SetPlantMap(int zone_table, unsigned int x, unsigned int y, int zone_type, int extra)
{
	char* map;
	char* rec;
	char* record_cursor;
	int i;
	unsigned char marker;

	map = (char*) lb_SearchRecordTable(zone_type);
	if (zone_table == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\auxillary\\plant.c", 0x83, "plt_SetPlantMap(): Map is not alloced or PlantInfo not found...", 1);
		return 0;
	}
	marker = 0xff;
	i = 0;
	record_cursor = (char*) zone_table + 9;
	while (i < 0x40) {
		if ((unsigned char) record_cursor[-1] == x && (unsigned char) record_cursor[0] == y && record_cursor[4] != (char) marker) {
			goto apply;
		}
		i++;
		record_cursor += 0x18;
	}
	i = 0;
	record_cursor = (char*) zone_table + 0xd;
	while (i < 0x40) {
		if (record_cursor[0] == (char) marker) {
			goto store_new;
		}
		i++;
		record_cursor += 0x18;
	}
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\auxillary\\plant.c", 0x9b, "plt_SetPlantMap(): Could not find map-entry!", 1);
	return 0;
store_new:
	*(int*) ((char*) zone_table + i * 24) = g_dynamic_count;
	g_dynamic_count++;
apply:
	rec = (char*) zone_table + i * 24;
	*(short*) (rec + 0xa) = (short) zone_type;
	if (extra != 0) {
		goto set_xy;
	}
	*(int*) (rec + 0x10) = -1;
	if (zone_type != 0) {
		*(char*) (rec + 0xd) = 1;
	} else {
		*(char*) (rec + 0xd) = 0xff;
	}
set_xy:
	*(char*) (rec + 8) = (char) x;
	*(char*) (rec + 9) = (char) y;
	if (map != 0) {
		*(char*) (rec + 0xc) = *(char*) (map + 0x42);
	} else {
		*(char*) (rec + 0xc) = 0;
	}
	return (int) rec;
}


/* Client-only building-site boxes (TL 0x4bd1e0, after plt_SetPlantMap; discarded). The
 * boxes are the 0x60-byte records ls_LoadBuildingEntityState reads into g_aux_entity_buffer, counted
 * by g_aux_entity_count: a site name and the bounding box of its 3D object. The client compares names
 * with _strnicmp and _strcmpi; strnicmp and strcmpi are their old names. */

/* SIZE 0x60 */
typedef struct BK_BOX {
	char name[0x40];
	float lo[4];
	float hi[4];
} BK_BOX;

/* SIZE 0x50 */
typedef struct BK_VERTEX {
	float p[3];
	char pad[0x44];
} BK_VERTEX;

typedef BK_VERTEX* (__cdecl* BK_GET_VERTICES)(char* name, char* obj, float* matrix);

/* Adds the box of a building-site object (name "bk_..." or "!bk_...") to the cache once. */
char __cdecl rd_AddBKBox(char* name)
{
	extern int __cdecl strnicmp(const char* a, const char* b, unsigned int n);
	extern int __cdecl strcmpi(const char* a, const char* b);
	extern void* __cdecl realloc(void* p, unsigned int size);
	extern int g_aux_entity_count;
	extern int g_aux_entity_buffer;
	float m[16];
	BK_VERTEX* v;
	char* d;
	char* obj;
	int i;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\auxillary\\plant.c", __LINE__, "rd_AddBKBox(): enter", 1);
	if (strnicmp(name, "bk_", 3) != 0 && strnicmp(name, "!bk_", 4) != 0) {
		return 1;
	}
	for (i = 0; i < g_aux_entity_count; i++) {
		if (strcmpi(name, ((BK_BOX*) g_aux_entity_buffer)[i].name) == 0) {
			return 1;
		}
	}
	obj = *(char**) (name + 0x1cc);
	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
	m[0] = m[5] = m[10] = m[15] = 1.0f;
	v = (*(BK_GET_VERTICES*) (*(char**) (obj + 0x318) + 0x1f0))(name, obj, m);
	g_aux_entity_buffer = (int) realloc((void*) g_aux_entity_buffer, (g_aux_entity_count + 1) * sizeof(BK_BOX));
	d = ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].name;
	while ((*d++ = *name++) != 0) {
	}
	((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].lo[0] = v->p[0];
	((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].lo[1] = v->p[1];
	((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].lo[2] = v->p[2];
	((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].hi[0] = v->p[0];
	((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].hi[1] = v->p[1];
	((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].hi[2] = v->p[2];
	for (i = 1; i < 8; i++) {
		((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].lo[0] =
		    v[i].p[0] < ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].lo[0]
		        ? v[i].p[0]
		        : ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].lo[0];
		((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].lo[1] =
		    v[i].p[1] < ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].lo[1]
		        ? v[i].p[1]
		        : ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].lo[1];
		((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].lo[2] =
		    v[i].p[2] < ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].lo[2]
		        ? v[i].p[2]
		        : ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].lo[2];
		((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].hi[0] =
		    v[i].p[0] > ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].hi[0]
		        ? v[i].p[0]
		        : ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].hi[0];
		((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].hi[1] =
		    v[i].p[1] > ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].hi[1]
		        ? v[i].p[1]
		        : ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].hi[1];
		((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].hi[2] =
		    v[i].p[2] > ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].hi[2]
		        ? v[i].p[2]
		        : ((BK_BOX*) g_aux_entity_buffer)[g_aux_entity_count].hi[2];
	}
	g_aux_entity_count++;
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\auxillary\\plant.c", __LINE__, "rd_AddBKBox(): exit", 1);
	return 1;
}

/* Returns the cached box of a building site, or 0 (TL 0x4bdf40). */
BK_BOX* __cdecl rd_GetBKSize(char* name)
{
	extern int __cdecl strcmpi(const char* a, const char* b);
	extern int __cdecl sprintf(char* buf, const char* fmt, ...);
	extern int g_aux_entity_count;
	extern int g_aux_entity_buffer;
	char buf[0x40];
	int i;

	for (i = 0; i < g_aux_entity_count; i++) {
		if (strcmpi(name, ((BK_BOX*) g_aux_entity_buffer)[i].name) == 0) {
			return &((BK_BOX*) g_aux_entity_buffer)[i];
		}
	}
	sprintf(buf, "rd_GetBKSize(): Unbekannter Bauplatz '%s'", name);
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\auxillary\\plant.c", __LINE__, buf, 1);
	return 0;
}

