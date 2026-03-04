extern int __cdecl find_zone_record(int param_1, unsigned int x, unsigned int y);
extern int __cdecl SearchRecordTable(int);
extern void __cdecl LogMessageInternal(char*, unsigned int, char*, int);
extern int DAT_1003540c;

// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 74
// SYMBOL: _FindRecord
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
// SYMBOL: _find_zone_record
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
// SYMBOL: _CheckZoneAvailability
// BLOCKER_DELTA: 170
// FUNCTION: SERVER 0x10014ff0
// CheckZoneAvailability

int __cdecl CheckZoneAvailability(int param_1, unsigned int param_2, unsigned int param_3, int param_4)
{
	int bVar1;
	unsigned char* pbVar2;
	int iVar3;
	int iVar4;
	int local_4;

	bVar1 = 0;
	iVar4 = 0;
	pbVar2 = (unsigned char*) (param_1 + 8);
	do {
		if (pbVar2[5] == 0xff) {
			bVar1 = 1;
		}
		else if (*pbVar2 == param_2 && pbVar2[1] == param_3) {
			return 0;
		}
		iVar4 = iVar4 + 1;
		pbVar2 = pbVar2 + 0x18;
		if (0x3f < iVar4) {
			if (!bVar1) {
				return 0;
			}
			local_4 = 0;
			if (param_4 > 0) {
				do {
					iVar4 = 0;
					do {
						iVar3 = find_zone_record(
							param_1,
							(iVar4 - param_4 / 2) + param_2,
							(local_4 - param_4 / 2) + param_3
						);
						if (iVar3 != 0) {
							return 0;
						}
						iVar4 = iVar4 + 1;
					} while (iVar4 < param_4);
					local_4 = local_4 + 1;
				} while (local_4 < param_4);
			}
			return 1;
		}
	} while (1);
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov)
// SIZE: 257
// SYMBOL: _plt_SetPlantMap
// BLOCKER_DELTA: 160
// FUNCTION: SERVER 0x100150a0
// plt_SetPlantMap

int __cdecl plt_SetPlantMap(int param_1, unsigned int param_2, unsigned int param_3, int param_4, int param_5)
{
	int iVar1;
	int iVar3;
	unsigned char* pbVar4;
	char* pcVar2;

	iVar1 = SearchRecordTable(param_4);
	if (param_1 == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\auxillary\\plant.c",
			0x83,
			"plt_SetPlantMap(): Map is not alloced or PlantInfo not found...",
			1
		);
		return 0;
	}
	iVar3 = 0;
	pbVar4 = (unsigned char*) (param_1 + 9);
	do {
		if (((pbVar4[-1] == param_2) && (*pbVar4 == param_3)) && (pbVar4[4] != 0xff)) {
			goto found;
		}
		iVar3 = iVar3 + 1;
		pbVar4 = pbVar4 + 0x18;
	} while (iVar3 < 0x40);
	iVar3 = 0;
	pcVar2 = (char*) (param_1 + 0xd);
	while (1) {
		if (*pcVar2 == (char) -1) {
			goto store_entry;
		}
		iVar3 = iVar3 + 1;
		pcVar2 = pcVar2 + 0x18;
		if (iVar3 >= 0x40) {
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
	*(int*) (param_1 + iVar3 * 0x18) = DAT_1003540c;
	DAT_1003540c = DAT_1003540c + 1;
found:
	param_1 = param_1 + iVar3 * 0x18;
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
	if (iVar1 != 0) {
		*(char*) (param_1 + 0xc) = *(char*) (iVar1 + 0x42);
		return param_1;
	}
	*(char*) (param_1 + 0xc) = 0;
	return param_1;
}

// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 41
// SYMBOL: _table_lookup
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
