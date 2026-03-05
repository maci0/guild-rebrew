extern int __cdecl find_zone_record(char* base, int x, int y);
extern int __cdecl SearchRecordTable(int);
extern void __cdecl LogMessageInternal(char*, unsigned int, char*, int);
extern int DAT_1003540c;

// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 74
// FUNCTION: SERVER 0x10014f30
// FindRecord
char* __cdecl FindRecord(char* base, unsigned int type1, unsigned int type2)
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

// STATUS: EXACT
// ORIGIN: GAME
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

// ORIGIN: GAME
// STATUS: MATCHING
// BLOCKER: instruction folding (lea vs mov), zero-extend pattern (xor vs mov)
// SIZE: 175
// BLOCKER_DELTA: 170
// FUNCTION: SERVER 0x10014ff0
// CheckZoneAvailability

int __cdecl CheckZoneAvailability(int param_1, unsigned int param_2, unsigned int param_3, int param_4)
{
	int has_free_slot;
	unsigned char* entry_ptr;
	int zone_result;
	int index;
	int row;

	has_free_slot = 0;
	index = 0;
	entry_ptr = (unsigned char*) (param_1 + 8);
	do {
		if (entry_ptr[5] == 0xff) {
			has_free_slot = 1;
		}
		else if (*entry_ptr == param_2 && entry_ptr[1] == param_3) {
			return 0;
		}
		index = index + 1;
		entry_ptr = entry_ptr + 0x18;
		if (0x3f < index) {
			if (!has_free_slot) {
				return 0;
			}
			row = 0;
			if (param_4 > 0) {
				do {
					index = 0;
					do {
						zone_result = find_zone_record(
							(char*) param_1,
							(index - param_4 / 2) + param_2,
							(row - param_4 / 2) + param_3
						);
						if (zone_result != 0) {
							return 0;
						}
						index = index + 1;
					} while (index < param_4);
					row = row + 1;
				} while (row < param_4);
			}
			return 1;
		}
	} while (1);
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov)
// SIZE: 257
// BLOCKER_DELTA: 160
// FUNCTION: SERVER 0x100150a0
// plt_SetPlantMap

int __cdecl plt_SetPlantMap(int param_1, unsigned int param_2, unsigned int param_3, int param_4, int param_5)
{
	int record_ptr;
	int slot_index;
	unsigned char* scan_ptr;
	char* marker_ptr;

	record_ptr = SearchRecordTable(param_4);
	if (param_1 == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\auxillary\\plant.c",
			0x83,
			"plt_SetPlantMap(): Map is not alloced or PlantInfo not found...",
			1
		);
		return 0;
	}
	slot_index = 0;
	scan_ptr = (unsigned char*) (param_1 + 9);
	do {
		if (((scan_ptr[-1] == param_2) && (*scan_ptr == param_3)) && (scan_ptr[4] != 0xff)) {
			goto found;
		}
		slot_index = slot_index + 1;
		scan_ptr = scan_ptr + 0x18;
	} while (slot_index < 0x40);
	slot_index = 0;
	marker_ptr = (char*) (param_1 + 0xd);
	while (1) {
		if (*marker_ptr == (char) -1) {
			goto store_entry;
		}
		slot_index = slot_index + 1;
		marker_ptr = marker_ptr + 0x18;
		if (slot_index >= 0x40) {
			LogMessageInternal(
				"D:\\Develop\\DieGildeAddOn\\auxillary\\plant.c",
				0x9b,
				"plt_SetPlantMap(): Could not find map-entry!",
				1
			);
			return 0;
		}
	}
store_entry:
	*(int*) (param_1 + slot_index * 0x18) = DAT_1003540c;
	DAT_1003540c = DAT_1003540c + 1;
found:
	param_1 = param_1 + slot_index * 0x18;
	*(short*) (param_1 + 10) = (short) param_4;
	if (param_5 == 0) {
		*(int*) (param_1 + 0x10) = 0xffffffff;
		if (param_4 == 0) {
			*(char*) (param_1 + 0xd) = (char) 0xff;
		}
		else {
			*(char*) (param_1 + 0xd) = 1;
		}
	}
	*(char*) (param_1 + 9) = (char) param_3;
	*(char*) (param_1 + 8) = (char) param_2;
	if (record_ptr != 0) {
		*(char*) (param_1 + 0xc) = *(char*) (record_ptr + 0x42);
		return param_1;
	}
	*(char*) (param_1 + 0xc) = 0;
	return param_1;
}

// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 41
// GHIDRA: GetStatPair
// FUNCTION: SERVER 0x100151B0
// table_lookup
int __cdecl table_lookup(int index, int* out)
{
	if (index >= 0x58) {
		return 0;
	}
	*out = *(int*) (0x1002DA30 + index * 8);
	*(int*) ((char*) out + 4) = *(int*) (0x1002DA34 + index * 8);
	return 1;
}
