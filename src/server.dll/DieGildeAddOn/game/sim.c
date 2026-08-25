#include "../../Units/Error/error.h"
extern unsigned short gm_RandomMod(unsigned int);
unsigned int __cdecl gm_CreateEntityFromParents(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
void __cdecl table_lookup(unsigned int a, unsigned short* b);
extern int g_entity_type_table;
unsigned int __cdecl FindAndMatchParents(unsigned int param);
extern unsigned char g_entity_type_bytes[];
extern unsigned char g_stat_b_array[];
extern unsigned char g_slot_table;
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);

/* Simulation entity: 0x21c-byte records at 0x10035800. */
typedef struct {
	char pad[0xa0];
	unsigned short field_a0;    /* +0xa0: slot id (0xffff = free) */
	unsigned char field_a2;     /* +0xa2: state byte */
	char pad2;
	int field_a4;               /* +0xa4 */
	unsigned char field_a8;     /* +0xa8: usable flag */
	char pad3;
	unsigned short field_aa;    /* +0xaa */
	char pad4[0x14];            /* +0xac..0xc0 */
	float field_c0;             /* +0xc0 */
	char pad5[0x108 - 0xc4];
	int field_108[5];           /* +0x108: linked children */
	char pad6[0x21c - 0x11c];
} SIM_ENT;

extern SIM_ENT g_sim_ents[];

/* Searches for matching parent entities by type and creates
 * family tree linkages. Used in citizen creation to find
 * compatible parents for stat inheritance. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x100151e0
// FindAndMatchParents

unsigned int __cdecl FindAndMatchParents(unsigned int param)
{
	SIM_ENT* ent;
	int weights[6];
	unsigned int rnd;
	unsigned int count;
	unsigned int parentA;
	unsigned int parentB;
	int i;
	int j = 0;
	int k;
	float f1;
	float f2;

	weights[0] = 0x60;
	weights[1] = 0x4b;
	weights[2] = 0x28;
	weights[3] = 0x17;
	weights[4] = 9;
	weights[5] = 0;
	i = 0x300;
	for (; j < 0x10; j++) {
		rnd = gm_RandomMod(i);
		parentA = rnd;
		ent = &g_sim_ents[rnd & 0xffff];
		if (ent->field_a0 == 0xffff) {
			i = i * 3 / 4;
			continue;
		}
		f1 = (float) ent->field_aa;
		if (ent->field_a2 < 6 && f1 >= ent->field_c0 && ent->field_a8 != 0) {
			count = 0;
			for (k = 0; k < 5; k++) {
				if (ent->field_108[k] != -1) {
					count++;
				}
			}
			if ((gm_RandomMod(0x100) & 0xffff) + 1 < (unsigned int) weights[count]) {
				goto done1;
			}
		} else {
			parentA = 0xffff;
		}
	}
done1:
	if (parentA == 0xffff) {
		return 0;
	}

	for (j = 0; j < 0x10; j++) {
		rnd = gm_RandomMod(i);
		parentB = rnd;
		ent = &g_sim_ents[rnd & 0xffff];
		if (ent->field_a0 == 0xffff) {
			i = i * 3 / 4;
			continue;
		}
		f2 = (float) ent->field_aa;
		if (ent->field_a2 < 6 && f2 >= ent->field_c0 && ent->field_a8 != 0) {
			count = 0;
			for (k = 0; k < 5; k++) {
				if (ent->field_108[k] != -1) {
					count++;
				}
			}
			if ((gm_RandomMod(0x100) & 0xffff) + 1 < (unsigned int) weights[count]) {
				goto done2;
			}
		} else {
			parentB = 0xffff;
		}
	}
done2:
	if (parentB == 0xffff) {
		return 0;
	}

	return gm_CreateEntityFromParents(
		0,
		g_sim_ents[parentA & 0xffff].field_a4,
		g_sim_ents[parentB & 0xffff].field_a4,
		(int) param,
		0, 0, 0, 2);
}

/* Updates entity priority/scheduling. Called during simulation
 * tick to adjust entity processing order based on game state. */

// FUNCTION: SERVER 0x10015400
// sim_PriorityUpdate

void __cdecl sim_PriorityUpdate(char* ctx, char* entity)
{
	unsigned short tmp[4];
	char* old;

	table_lookup((unsigned char) entity[0], tmp);
	if ((unsigned short) (unsigned char) entity[0x65] < tmp[0]) {
		old = *(char**) (ctx + 0x170);
		if (old != 0) {
			if ((unsigned char) old[0x65] > 0)
				old[0x65]--;
		}
		*(char**) (ctx + 0x170) = entity;
		entity[0x65]++;
	}
}

/* Starts an entity query filtered by type byte from arg1.
 * Dispatches entity iteration across buildings, citizens, or
 * other entity categories based on the type selector. */

// FUNCTION: SERVER 0x10015460
// sim_StartEntityQueryByType

void __cdecl sim_StartEntityQueryByType(unsigned char* arg1)
{
	unsigned char cls;
	int zero;

	zero = 0;
	cls = *((unsigned char*) g_entity_type_table + arg1[0] + arg1[0] * 588);
	switch (cls) {
	case 1:
		gm_StartEntityQuery(*(int*) (arg1 + 0x5d), 1, zero, 0x12);
		break;
	case 2:
		gm_StartEntityQuery(*(int*) (arg1 + 0x5d), 1, 0, 0x13);
		break;
	case 0x1d:
		gm_StartEntityQuery(*(int*) (arg1 + 0x5d), 1, 0, 0xfd);
		break;
	case 0x16:
		gm_StartEntityQuery(*(int*) (arg1 + 0x5d), 1, 0, 0x120);
		break;
	}
}

/* Creates a new citizen entity with initial stats generated
 * from parent entities. Allocates entity memory, assigns random
 * stats via gm_CreateEntityFromParents, and links to home. */

// FUNCTION: SERVER 0x10015500
// sim_CreateCitizen

void* __cdecl sim_CreateCitizen(unsigned char flags, int citizen_type, int parent_id, unsigned char stat_a, unsigned char stat_b)
{
	unsigned int new_entity_slot;

	if ((flags & 1) != 0) {
		new_entity_slot = FindAndMatchParents(parent_id) & 0xffff;
		if (new_entity_slot == 0xffff) {
			goto error;
		}
		if ((flags & 2) != 0) {
			g_stat_b_array[new_entity_slot * 0x21c] = stat_b;
			g_entity_type_bytes[new_entity_slot * 0x21c] = stat_a;
		}
	}
	else {
		new_entity_slot =
			gm_CreateEntityFromParents(citizen_type, -1, -1, parent_id, 0, (unsigned int) stat_a, (unsigned int) stat_b, 2) &
			0xffff;
	}
	if (new_entity_slot == 0xffff) {
		goto error;
	}
	return &g_slot_table + new_entity_slot * 0x21c;
error:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\sim.c",
		0x127d,
		"sim_CreateCitizen(): could not alloc spieler",
		1
	);
	return (void*) 0;
}

/* Advances the game clock by one tick. Updates day/hour/minute
 * counters, triggers periodic events (taxes, production cycles),
 * and notifies connected clients of time changes. */

// FUNCTION: SERVER 0x100155c0
// AdvanceGameClock

#pragma pack(push, 1)
// SIZE 0xe
typedef struct {
	int x00;             /* +0x00 */
	unsigned short x04;  /* +0x04 */
	int x06;             /* +0x06 */
	int x0a;             /* +0x0a */
} SIM_CLOCK;
#pragma pack(pop)

int __cdecl AdvanceGameClock(SIM_CLOCK* clock, int arg2, int arg3, int arg4)
{
	int minutes;
	int hour;
	int days;

	minutes = arg4 + clock->x0a;
	clock->x06 += minutes / 60;
	clock->x0a = minutes % 60;
	minutes = arg4 + clock->x06;
	clock->x04 += minutes / 60;
	clock->x06 = minutes % 60;
	hour = clock->x04 + arg3;
	if (hour >= 24) {
		days = (unsigned int) hour / 24;
		hour = hour - days * 24;
		do {
			clock->x00++;
		} while (--days != 0);
	}
	if (hour < 0) {
		days = (unsigned int) (23 - hour) / 24;
		hour = hour + days * 24;
		do {
			clock->x00--;
		} while (--days != 0);
	}
	clock->x04 = (unsigned short) hour;
}

/* Sets the simulation sync parameters for the entity query
 * engine. Stores target, type, and field values for later use
 * by the query dispatcher. */

// FUNCTION: SERVER 0x10015690
// sim_SetSyncParams

void __cdecl sim_SetSyncParams(int target, unsigned char type_id, unsigned int field_6, unsigned int field_10)
{
	*(unsigned int*) (target + 10) = field_10 & 0xff;
	*(unsigned short*) (target + 4) = (unsigned short) type_id;
	*(unsigned int*) (target + 6) = field_6 & 0xff;
}
