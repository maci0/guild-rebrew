#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/entity.h"

extern char* gm_CityEntity;
extern char* lpObjektePROT;
extern unsigned char* g_entity_ptr;

extern void* __cdecl gm_LookupEntityRecordById(int id);
extern void* __cdecl gm_ResetMissionEntry(void* entity);
extern int __cdecl gm_GetBuildingTypeCategory(int type);
extern int __cdecl gm_AssignBuildingOwner(void* record, int a, int b);
extern int __cdecl gm_CalcPersonWealth(unsigned short raw_idx);
extern void __cdecl he_FreeActionsByKind(void* entity);
extern void __cdecl he_ClearEntityActions(void* entity);
extern void __cdecl amt_ClearEntityOffices(void* entity);
extern int __cdecl gm_MapEntityStatRange(int age);
extern void* __cdecl gm_GetEntityTableEntry(void* entity);
extern int __cdecl gm_CheckStatLevel(int slot, int kind);
extern int __cdecl gm_GetOppositeStatIndex(int value);
extern char* __cdecl gm_FindOrAllocHeadSet(int a, int b);
extern void __cdecl gm_AddObjekt(int record, int item, int value);
extern void __cdecl gm_KillSpieler(int slot, int value);

/* ADDRESS: GOLDTL 0x00509620 */
/* ADDRESS: GOLDDE 0x004f46a0 */
int __cdecl gm_TransferDynastyEstate(int sourceId, int targetId)
{
	int counter;
	int owner;
	unsigned short q_slot;
	unsigned short p_slot;
	int value;
	EntityStruct rec_a;
	EntityStruct rec_b;
	EntityStruct* p;
	EntityStruct* q;
	unsigned char* ep;
	char* found;
	char* node;
	char* dst;
	int i;
	int level;
	int rank;
	char* item;
	unsigned short obj_type;

	p = (EntityStruct*) gm_LookupEntityRecordById(sourceId);
	if (p == 0)
		return -1;
	gm_ResetMissionEntry(p);

	i = 0;
	counter = 0x100;
	do {
		ep = g_entity_ptr + i * 0xa9;
		if (*ep != 0) {
			if (gm_GetBuildingTypeCategory(*ep & 0xff) == 2) {
				if (*(unsigned short*) (ep + 0x27) == p->entity_index) {
					owner = *(unsigned short*) gm_CityEntity;
					gm_AssignBuildingOwner(ep, owner, owner);
				}
			}
		}
		i++;
		counter--;
	} while (counter != 0);

	p_slot = p->entity_index;
	value = gm_CalcPersonWealth(p_slot);
	q = (EntityStruct*) gm_LookupEntityRecordById(targetId);
	if (q == 0)
		return -2;
	he_FreeActionsByKind(p);
	he_ClearEntityActions(p);
	he_ClearEntityActions(q);
	q_slot = q->entity_index;
	if (p->max_hp != q->max_hp)
		q->max_hp = p->max_hp;
	amt_ClearEntityOffices(p);

	memcpy(&rec_a, q, 0x21c);
	rec_a.entity_id = p->entity_id;
	rec_a.entity_index = p->entity_index;
	rec_a.entity_state = p->entity_state;
	rec_a.is_active = p->is_active;
	rec_a.current_building = p->current_building;

	rank = gm_MapEntityStatRange(((char*) q)[0x164] & 0xff);
	if (rank != 0) {
		found = (char*) gm_GetEntityTableEntry(p);
		if (found != 0) {
			level = gm_CheckStatLevel(p->entity_index, rank);
			if (level != 0) {
				if (gm_GetOppositeStatIndex(level) <
					gm_GetOppositeStatIndex(((char*) q)[0x164] & 0xff)) {
					found[rank + 0x74] = ((char*) q)[0x164];
				} else {
					rec_a.age = p->age;
				}
			}
		}
	} else {
		rec_a.age = p->age;
	}

	if (p->gender == rec_a.gender) {
		strcpy((char*) &rec_a + 0x1f4, (char*) p + 0x1f4);
		rec_a.target_id = p->target_id;
	} else {
		*((char*) &rec_a + 0x1f4) = 0;
		item = gm_FindOrAllocHeadSet(rec_a.gender & 0xff, rec_a.age & 0xff);
		if (item != 0) {
			strcpy((char*) &rec_a + 0x1f4, item + 4);
			rec_a.target_id = *(int*) (item + 0x34) + 0x639;
		}
	}

	rec_b = *p;
	rec_b.entity_id = q->entity_id;
	rec_b.entity_index = q->entity_index;
	rec_b.entity_state = 9;

	memcpy((char*) g_slot_table + p_slot * 0x21c, &rec_a, 0x21c);
	memcpy((char*) g_slot_table + q_slot * 0x21c, &rec_b, 0x21c);

	node = *(char**) ((char*) g_slot_table + 0x178 + p_slot * 0x21c);
	while (node != 0) {
		*(int*) (node + 6) = *(int*) ((char*) g_slot_table + 4 + p_slot * 0x21c);
		node = *(char**) (node + 0x3f);
	}
	node = *(char**) ((char*) g_slot_table + 0x178 + q_slot * 0x21c);
	while (node != 0) {
		*(int*) (node + 6) = *(int*) ((char*) g_slot_table + 4 + q_slot * 0x21c);
		node = *(char**) (node + 0x3f);
	}

	dst = (char*) g_slot_table + 0x5c;
	counter = 0x300;
	do {
		char* ent = dst;
		level = 8;
		do {
			if (*(int*) ent == sourceId) {
				*(int*) ent = targetId;
			} else if (*(int*) ent == targetId) {
				*(int*) ent = sourceId;
			}
			ent += 4;
			level--;
		} while (level != 0);
		dst += 0x21c;
		counter--;
	} while (counter != 0);

	node = *(char**) ((char*) &rec_b + 0x178);
	while (node != 0) {
		obj_type = *(unsigned short*) node;
		if (obj_type != 0) {
			if ((*(char*) &((OBJECT_PROTOTYPE*) lpObjektePROT)[obj_type].kind) == 9) {
				gm_AddObjekt(rec_a.entity_id, obj_type,
					*(int*) (node + 0xe));
			}
		}
		node = *(char**) (node + 0x3f);
	}

	*(int*) ((char*) g_slot_table + 0x1a8 + p_slot * 0x21c) = value;
	*(int*) ((char*) g_slot_table + 0x194 + p_slot * 0x21c) = 4;
	*(int*) ((char*) g_slot_table + 0x1c8 + p_slot * 0x21c) = 0;
	gm_KillSpieler(rec_b.entity_index, 0);
	return p_slot;
}
