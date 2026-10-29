#include <string.h>

#include "Develop/DieGildeAddOn/game/entity.h"

extern char* g_773da8;
extern char* lpObjektePROT;
extern unsigned char* g_entity_ptr;

extern void* __cdecl fcn_00508e40(int id);
extern void* __cdecl fcn_004b3c00(void* entity);
extern int __cdecl gm_GetBuildingTypeCategory(int type);
extern int __cdecl fcn_005059b0(void* record, int a, int b);
extern int __cdecl gm_WalkEntityChain(unsigned int slot);
extern void __cdecl fcn_00546ce0(void* entity);
extern void __cdecl fcn_0055bc40(void* entity);
extern void __cdecl fcn_004e8940(void* entity);
extern int __cdecl gm_MapEntityStatRange(int age);
extern void* __cdecl gm_GetEntityTableEntry(void* entity);
extern int __cdecl gm_CheckStatLevel(unsigned int slot, int kind);
extern int __cdecl gm_GetOppositeStatIndex(int value);
extern char* __cdecl fcn_004fd9d0(int a, int b);
extern void __cdecl gm_AddObjekt(int record, unsigned int item, int value);
extern void __cdecl gm_KillSpieler(int slot, int value);

/* ADDRESS: GOLDTL 0x00509620 */
int __cdecl fcn_00509620(int a0, int a1)
{
	EntityStruct* slots;
	EntityStruct* p;
	EntityStruct* q;
	EntityStruct rec_a;
	EntityStruct rec_b;
	char* name;
	char* item;
	void* node;
	void* found;
	int off;
	int n;
	int i;
	int j;
	int p_slot;
	int q_slot;
	int kind;
	int value;
	int rank;
	unsigned char state;
	unsigned char* ep;

	slots = (EntityStruct*) g_slot_table;
	p = (EntityStruct*) fcn_00508e40(a0);
	if (p == 0)
		return -1;
	kind = (int) fcn_004b3c00(p);
	for (off = 0, n = 0x100; n != 0; n--, off += 0xa9) {
		ep = g_entity_ptr + off;
		if (ep[0] != 0) {
			kind = gm_GetBuildingTypeCategory(ep[0]);
			if (kind == 2 && *(unsigned short*) (ep + 0x27) == p->entity_index)
				kind = fcn_005059b0(ep,
					*(unsigned short*) g_773da8, *(unsigned short*) g_773da8);
		}
	}
	p_slot = p->entity_index;
	value = gm_WalkEntityChain(p_slot);
	q = (EntityStruct*) fcn_00508e40(a1);
	if (q == 0)
		return -2;
	q_slot = q->entity_index;
	fcn_00546ce0(p);
	fcn_0055bc40(p);
	fcn_0055bc40(q);
	if (p->max_hp != q->max_hp)
		q->max_hp = p->max_hp;
	fcn_004e8940(p);

	rec_a = *q;
	rec_a.entity_state = p->entity_state;
	rec_a.entity_id = p->entity_id;
	rec_a.entity_index = p->entity_index;
	rec_a.is_active = p->is_active;
	rec_a.current_building = p->current_building;

	rank = gm_MapEntityStatRange(q->age);
	if (rank != 0) {
		found = gm_GetEntityTableEntry(p);
		if (found != 0) {
			item = (char*) gm_CheckStatLevel(p->entity_index, rank);
			if (item != 0) {
				if (gm_GetOppositeStatIndex(q->age) <= gm_GetOppositeStatIndex((int) item))
					state = p->age;
				else
					*(char*) ((char*) found + 0x74 + rank) = q->age;
			}
		}
	} else {
		state = p->age;
	}

	name = (char*) &rec_a + 0x1f4;
	if (p->gender == q->gender) {
		strcpy(name, (char*) p + 0x1f4);
		*(int*) ((char*) &rec_a + 0x18c) = p->target_id;
	} else {
		name[0] = 0;
		item = fcn_004fd9d0(q->gender, state);
		if (item != 0) {
			strcpy(name, item + 4);
			*(int*) ((char*) &rec_a + 0x18c) = *(int*) (item + 0x34) + 0x639;
		}
	}

	rec_b = *p;
	rec_b.entity_index = q->entity_index;
	rec_b.entity_id = q->entity_id;
	rec_b.entity_state = 9;
	slots[p_slot] = rec_a;
	slots[q_slot] = rec_b;

	for (node = *(void**) ((char*) &slots[p_slot] + 0x178); node != 0;
		node = *(void**) ((char*) node + 0x3f))
		*(int*) ((char*) node + 6) = slots[p_slot].entity_id;
	for (node = *(void**) ((char*) &slots[q_slot] + 0x178); node != 0;
		node = *(void**) ((char*) node + 0x3f))
		*(int*) ((char*) node + 6) = slots[q_slot].entity_id;

	for (i = 0; i < 0x300; i++) {
		for (j = 0; j < 8; j++) {
			if (slots[i].ref_table[j] == a0)
				slots[i].ref_table[j] = a1;
			else if (slots[i].ref_table[j] == a1)
				slots[i].ref_table[j] = a0;
		}
	}

	for (node = *(void**) ((char*) &rec_b + 0x178); node != 0;
		node = *(void**) ((char*) node + 0x3f)) {
		unsigned short id;
		id = *(unsigned short*) node;
		if (id != 0 && lpObjektePROT[id * 0x41] == 9)
			gm_AddObjekt(*(int*) ((char*) &rec_a + 4), id,
				*(int*) ((char*) node + 0xe));
	}

	*(int*) ((char*) &slots[p_slot] + 0x1a8) = value;
	*(int*) ((char*) &slots[p_slot] + 0x194) = 4;
	*(int*) ((char*) &slots[p_slot] + 0x1c8) = 0;
	gm_KillSpieler(rec_b.entity_index, 0);
	return p_slot;
}
