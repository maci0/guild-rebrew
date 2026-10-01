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

// GLOBAL: SERVER 0x1002d878
PLANT_INFO g_plant_info_table[4] = {
	{ 0x1b7, "TANNE", 3, 1, 4 },
	{ 0x1b8, "BUCHE", 5, 1, 4 },
	{ 0x1b9, "EICHE", 5, 2, 8 },
	{ 0, "", 0, 1, 0 },
};

// DATA: SERVER 0x1002d990
char s_plt_SetPlantMap____Could_not_fin[] = "plt_SetPlantMap(): Could not find map-entry!";

// DATA: SERVER 0x1002d9c0
char s_D__Develop_DieGildeAddOn_auxilla[] = "D:\\Develop\\DieGildeAddOn\\auxillary\\plant.c";

// DATA: SERVER 0x1002d9ec
char s_plt_SetPlantMap____Map_is_not_al[] = "plt_SetPlantMap(): Map is not alloced or PlantInfo not found...";

/* 0x58 pairs read by plt_TableLookup; a struct
 * array, 8-aligned like the reference (four zero bytes at 0x1002da2c). */
// SIZE 0x8
typedef struct {
	int first;
	int second;
} PLANT_PAIR;

// DATA: SERVER 0x1002da30
PLANT_PAIR g_plant_pair_table[0x58] = {
	{ 0, 0 },
	{ 0x320008, 0 },
	{ 0x4b000c, 0 },
	{ 0x7d0014, 0 },
	{ 0x80000, 0 },
	{ 0xc0000, 0 },
	{ 0xf0000, 0 },
	{ 0x140000, 0 },
	{ 0xa0000, 0x30000 },
	{ 0xf0000, 0x90000 },
	{ 0x190000, 0x100000 },
	{ 0x140000, 0x140006 },
	{ 0x1e0000, 0x3c0009 },
	{ 0x2d0000, 0x6e000c },
	{ 0x1e0000, 0xa0000 },
	{ 0x2d0000, 0x1e0000 },
	{ 0x460000, 0x3c0000 },
	{ 0xa0000, 0xa0000 },
	{ 0x140000, 0x1e0000 },
	{ 0x190000, 0x3c0000 },
	{ 0x1e0000, 0xf0003 },
	{ 0x2d0000, 0x320006 },
	{ 0x500000, 0x780009 },
	{ 0x1e0000, 0x140003 },
	{ 0x320000, 0x320005 },
	{ 0x4b0000, 0x640006 },
	{ 0x1e0000, 0xf0000 },
	{ 0x320000, 0x230000 },
	{ 0x4b0000, 0x460000 },
	{ 0, 0 },
	{ 0x1e0000, 0x1e000a },
	{ 0x1e0000, 0x1e000a },
	{ 0x1e0000, 0x1e000a },
	{ 0x1e0000, 0x140003 },
	{ 0x320000, 0x320005 },
	{ 0x4b0000, 0x640006 },
	{ 0x140000, 0x50000 },
	{ 0x280000, 0xa0000 },
	{ 0x640000, 0x140000 },
	{ 0x1e0000, 0x1e000c },
	{ 0xa0000, 0 },
	{ 0x1e0000, 0x140003 },
	{ 0x320000, 0x320005 },
	{ 0x4b0000, 0x640006 },
	{ 0x1e0000, 0x140008 },
	{ 0x320000, 0x28000a },
	{ 0x4b0000, 0x50000c },
	{ 0x1e0000, 0x140003 },
	{ 0x320000, 0x320005 },
	{ 0x4b0000, 0x640006 },
	{ 0x1e0000, 0x140003 },
	{ 0x320000, 0x320005 },
	{ 0x4b0000, 0x640006 },
	{ 0x1e0000, 0x190004 },
	{ 0x320000, 0x280005 },
	{ 0x500000, 0x460006 },
	{ 0x140000, 0x50000 },
	{ 0x280000, 0xa0000 },
	{ 0x500000, 0x140000 },
	{ 0x140000, 0x50000 },
	{ 0x280000, 0xa0000 },
	{ 0x500000, 0x140000 },
	{ 0x140000, 0x50000 },
	{ 0x280000, 0xa0000 },
	{ 0x500000, 0x140000 },
	{ 0x140000, 0x50000 },
	{ 0x280000, 0xa0000 },
	{ 0x500000, 0x140000 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
};
// GLOBAL: SERVER 0x1002dcf0
int g_plant_flag = 1;

// GLOBAL: SERVER 0x1003540c
int g_dynamic_count;

/* Finds a record in a linked table by matching type fields.
 * Iterates from base pointer, comparing type1/type2 bytes.
 * Returns pointer to matching record or NULL. */
// FUNCTION: GOLD 0x004bc5a0
// SIZE: 80
// FUNCTION: GOLDTL 0x4bcb80
// SIZE: 80

/* Checks if a zone is available for planting. Validates
 * the zone record, checks plant capacity, and verifies
 * the zone type matches the requested plant type. */

// FUNCTION: SERVER 0x10014ee0
// SIZE: 69

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

// FUNCTION: GOLD 0x4bc5f0
// SIZE: 80
// FUNCTION: GOLDTL 0x4bcbd0
// SIZE: 80
// FUNCTION: SERVER 0x10014f30
// plt_FindRecord
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
// FUNCTION: GOLD 0x4bc6a0
// SIZE: 112
// FUNCTION: GOLDTL 0x4bcc80
// SIZE: 103
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

/* Finds a zone record by x/y coordinates. Searches linked
 * records for a matching grid position. Returns record index
 * or -1 if not found. */

// FUNCTION: GOLD 0x4bc710
// SIZE: 176
// FUNCTION: GOLDTL 0x4bccf0
// SIZE: 163
// FUNCTION: SERVER 0x10014ff0
// plt_CheckZoneAvailability
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

// FUNCTION: SERVER 0x100150a0
// plt_SetPlantMap
int __cdecl plt_SetPlantMap(int zone_table, unsigned int x, unsigned int y, int zone_type, int extra)
{
	char* map;
	char* rec;
	char* record_cursor;
	int i;
	unsigned char marker;

	map = (char*) lb_SearchRecordTable(zone_type);
	if (zone_table == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_auxilla, 0x83, s_plt_SetPlantMap____Map_is_not_al, 1);
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
	LogMessageInternal(s_D__Develop_DieGildeAddOn_auxilla, 0x9b, s_plt_SetPlantMap____Could_not_fin, 1);
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
	*out = g_plant_pair_table[index].first;
	*(int*) ((char*) out + 4) = g_plant_pair_table[index].second;
	return 1;
}
