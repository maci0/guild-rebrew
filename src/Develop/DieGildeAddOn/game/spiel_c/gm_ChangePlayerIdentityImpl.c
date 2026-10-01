// FUNCTION: GOLDTL 0x422150
// SIZE: 784
// FUNCTION: SERVER 0x10018530

#include <stdlib.h>
#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern unsigned char g_slot_table[0x300 * 0x21c];
extern unsigned short* g_entity_table_end; /* 0x1003546c */

int __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_WalkEntityChain(unsigned short);
void __cdecl gm_AssignBuildingOwner(char*, int, int);
int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_GetOppositeStatIndex(int);
int __cdecl gm_MapEntityStatRange(int);
char* __cdecl gm_GetEntityTableEntry(char*);
void __cdecl gm_AddObjekt(int, int, int);
void __cdecl gm_KillSpieler(int, int);
void __cdecl amt_ClearEntityLinks(char*);

int __cdecl gm_ChangePlayerIdentityImpl(int from_id, int to_id, int unused)
{
	int counter;
	int owner;
	unsigned short to_slot;
	unsigned short chain;
	int link;
	char rec_a[0x21c];
	char rec_b[0x21c];
	char* from_ent;
	char* to_ent;
	char* ent;
	char* stat_ent;
	char* obj;
	char* dst;
	int i;
	int level;
	int range;
	unsigned short obj_type;

	(void) unused;

	from_ent = (char*) gm_LookupEntityRecordById(from_id);
	if (from_ent == NULL) {
		return -1;
	}

	i = 0;
	counter = 0x100;
	do {
		ent = (char*) g_entity_ptr + i * 0xa9;
		if (*ent != 0) {
			if (gm_GetBuildingTypeCategory(*ent & 0xff) == 2) {
				if (*(unsigned short*) (ent + 0x27) == *(unsigned short*) from_ent) {
					owner = *g_entity_table_end;
					gm_AssignBuildingOwner(ent, owner, owner);
				}
			}
		}
		i++;
		counter--;
	} while (counter != 0);

	chain = *(unsigned short*) from_ent;
	link = gm_WalkEntityChain(chain);
	to_ent = (char*) gm_LookupEntityRecordById(to_id);
	if (to_ent == NULL) {
		return -2;
	}
	to_slot = *(unsigned short*) to_ent;
	if (*(unsigned short*) (from_ent + 0x50) != *(unsigned short*) (to_ent + 0x50)) {
		*(unsigned short*) (to_ent + 0x50) = *(unsigned short*) (from_ent + 0x50);
	}
	amt_ClearEntityLinks(from_ent);

	memcpy(rec_a, to_ent, 0x21c);
	*(int*) (rec_a + 4) = *(int*) (from_ent + 4);
	*(unsigned short*) rec_a = *(unsigned short*) from_ent;
	rec_a[2] = from_ent[2];
	rec_a[0xd] = from_ent[0xd];
	*(int*) (rec_a + 0x170) = *(int*) (from_ent + 0x170);

	range = gm_MapEntityStatRange(to_ent[0x164] & 0xff);
	if (range != 0) {
		stat_ent = gm_GetEntityTableEntry(from_ent);
		if (stat_ent != NULL) {
			level = gm_CheckStatLevel(*(unsigned short*) from_ent, range);
			if (level != 0) {
				if (gm_GetOppositeStatIndex(level) <
					gm_GetOppositeStatIndex(to_ent[0x164] & 0xff)) {
					stat_ent[range + 0x74] = to_ent[0x164];
				} else {
					rec_a[0x164] = from_ent[0x164];
				}
			}
		}
	} else {
		rec_a[0x164] = from_ent[0x164];
	}

	memcpy(rec_b, from_ent, 0x21c);
	*(int*) (rec_b + 4) = *(int*) (to_ent + 4);
	*(unsigned short*) rec_b = *(unsigned short*) to_ent;
	rec_b[2] = 9;

	memcpy((char*) ((int) g_slot_table + 0x0) + chain * 0x21c, rec_a, 0x21c);
	memcpy((char*) ((int) g_slot_table + 0x0) + to_slot * 0x21c, rec_b, 0x21c);

	obj = *(char**) ((char*) ((int) g_slot_table + 0x178) + chain * 0x21c);
	while (obj != NULL) {
		*(int*) (obj + 6) = *(int*) ((char*) (g_slot_table + 4) + chain * 0x21c);
		obj = *(char**) (obj + 0x3f);
	}
	obj = *(char**) ((char*) ((int) g_slot_table + 0x178) + to_slot * 0x21c);
	while (obj != NULL) {
		*(int*) (obj + 6) = *(int*) ((char*) (g_slot_table + 4) + to_slot * 0x21c);
		obj = *(char**) (obj + 0x3f);
	}

	dst = (char*) ((int) g_slot_table + 0x5c);
	counter = 0x300;
	do {
		ent = dst;
		level = 8;
		do {
			if (*(int*) ent == from_id) {
				*(int*) ent = to_id;
			} else if (*(int*) ent == to_id) {
				*(int*) ent = from_id;
			}
			ent += 4;
			level--;
		} while (level != 0);
		dst += 0x21c;
		counter--;
	} while (counter != 0);

	obj = *(char**) (rec_b + 0x178);
	while (obj != NULL) {
		obj_type = *(unsigned short*) obj;
		if (obj_type != 0) {
			if (g_item_def_table[(obj_type << 6) + obj_type] == 9) {
				gm_AddObjekt(*(int*) (rec_a + 4), obj_type,
					*(int*) (obj + 0xe));
			}
		}
		obj = *(char**) (obj + 0x3f);
	}

	*(int*) ((char*) (g_slot_table + 0x1a8) + chain * 0x21c) = link;
	*(int*) ((char*) (g_slot_table + 0x194) + chain * 0x21c) = 4;
	*(int*) ((char*) (g_slot_table + 0x1c8) + chain * 0x21c) = 0;
	gm_KillSpieler(*(unsigned short*) rec_b, 0);

	return chain;
}

