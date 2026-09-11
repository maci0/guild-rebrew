#include "../../Units/Error/error.h"
int __cdecl find_zone_record(char* base, int x, int y);
/* Looks up a plant-info table entry by key. Table at 0x1002d878,
 * stride 0x46; terminated by a zero key word. */

// FUNCTION: SERVER 0x10014ee0
// SIZE: 69

extern int g_plant_info_table; /* 0x1002d878 */

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

extern int g_dynamic_count;

/* Finds a record in a linked table by matching type fields.
 * Iterates from base pointer, comparing type1/type2 bytes.
 * Returns pointer to matching record or NULL. */

// FUNCTION: SERVER 0x10014f30
// plt_FindRecord
char* __cdecl plt_FindRecord(char* base, unsigned int type1, unsigned int type2)
{
	int i;
	char* p;
	unsigned char marker;

	i = 0;
	p = base + 9;
	marker = 0xff;
	while (i < 0x40) {
		if ((unsigned char) p[-1] == type1 && (unsigned char) p[0] == type2 && p[4] != (char) marker) {
			return base + i * 0x18;
		}
		i++;
		p += 0x18;
	}
	return (char*) 0;
}

/* Finds a zone record by x/y coordinates. Searches linked
 * records for a matching grid position. Returns record index
 * or -1 if not found. */

// FUNCTION: SERVER 0x10014F80
// find_zone_record
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

/* Checks if a zone is available for planting. Validates
 * the zone record, checks plant capacity, and verifies
 * the zone type matches the requested plant type. */

// FUNCTION: SERVER 0x10014ff0
// plt_CheckZoneAvailability
int __cdecl plt_CheckZoneAvailability(int zone_table, unsigned int x, unsigned int y, int zone_type)
{
	int i;
	int j;
	int found_free;
	char* e;

	found_free = 0;
	i = 0;
	e = (char*) (zone_table + 8);
	while (i < 0x40) {
		if (*(signed char*) (e + 5) == (char) 0xff) {
			found_free = 1;
		} else if ((unsigned char) *e == x && (unsigned char) *(e + 1) == y) {
			return 0;
		}
		i++;
		e += 0x18;
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

char s_plt_SetPlantMap____Could_not_fin_1002d990[] = "plt_SetPlantMap(): Could not find map-entry!";
char s_D__Develop_DieGildeAddOn_auxilla_1002d9c0[] = "D:\\Develop\\DieGildeAddOn\\auxillary\\plant.c";
char s_plt_SetPlantMap____Map_is_not_al_1002d9ec[] = "plt_SetPlantMap(): Map is not alloced or PlantInfo not found...";

// FUNCTION: SERVER 0x100150a0
// plt_SetPlantMap
int __cdecl plt_SetPlantMap(int zone_table, unsigned int x, unsigned int y, int zone_type, int extra)
{
	char* map;
	char* rec;
	char* p;
	int i;
	unsigned char marker;

	map = (char*) lb_SearchRecordTable(zone_type);
	if (zone_table == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_auxilla_1002d9c0, 0x83, s_plt_SetPlantMap____Map_is_not_al_1002d9ec, 1);
		return 0;
	}
	marker = 0xff;
	i = 0;
	p = (char*) zone_table + 9;
	while (i < 0x40) {
		if ((unsigned char) p[-1] == x && (unsigned char) p[0] == y && p[4] != (char) marker) {
			goto apply;
		}
		i++;
		p += 0x18;
	}
	i = 0;
	p = (char*) zone_table + 0xd;
	while (i < 0x40) {
		if (p[0] == (char) marker) {
			goto store_new;
		}
		i++;
		p += 0x18;
	}
	LogMessageInternal(s_D__Develop_DieGildeAddOn_auxilla_1002d9c0, 0x9b, s_plt_SetPlantMap____Could_not_fin_1002d990, 1);
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

/* Simple lookup into a global table by index. Returns value
 * through out-pointer. Returns 0 if index out of range. */

// FUNCTION: SERVER 0x100151B0
// plt_TableLookup
int __cdecl plt_TableLookup(int index, int* out)
{
	if (index >= 0x58) {
		return 0;
	}
	*out = *(int*) (0x1002DA30 + index * 8);
	*(int*) ((char*) out + 4) = *(int*) (0x1002DA34 + index * 8);
	return 1;
}
