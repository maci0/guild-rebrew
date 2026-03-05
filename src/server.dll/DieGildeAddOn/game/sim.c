#include "Units/Error/error.h"
extern unsigned short gm_RandomMod(unsigned int);
extern unsigned int __cdecl gm_CreateEntityFromParents(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
extern void __cdecl table_lookup(unsigned int a, unsigned short* b);
extern int DAT_100a8c30;
extern void __cdecl gm_StartEntityQuery(int, int, int, ...);
extern unsigned int __cdecl FindAndMatchParents(int param);
extern unsigned char DAT_10035a04;
extern unsigned char DAT_10035a05;
extern unsigned char DAT_100358a0;

// STATUS: MATCHING
// BLOCKER: instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout, zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 535
// FUNCTION: SERVER 0x100151e0
// FindAndMatchParents

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 469

unsigned int FindAndMatchParents(unsigned int param_1)
{
	unsigned short candidate_slot1;
	unsigned short candidate_slot2;
	unsigned int rand_roll;
	int* parent_slot_ptr;
	int entity_offset;
	unsigned int search_seed;
	int occupied_count;
	int attempt_count;
	unsigned int attempt2_count;
	int prob_thresholds[6];

	attempt_count = 0;
	prob_thresholds[0] = 0x60;
	prob_thresholds[1] = 0x4b;
	prob_thresholds[2] = 0x28;
	prob_thresholds[3] = 0x17;
	prob_thresholds[4] = 9;
	prob_thresholds[5] = 0;
	search_seed = 0x300;
	do {
		candidate_slot1 = gm_RandomMod(search_seed);
		rand_roll = candidate_slot1 * 0xf;
		entity_offset = candidate_slot1 * 0x21c;
		if (*(int*) (entity_offset + 0x100358a0) == -1) {
			rand_roll = search_seed * 3 + (search_seed * 3 >> 0x1f & 3U) >> 2;
			search_seed = rand_roll;
		}
		else if (((5 < *(unsigned int*) (entity_offset + 0x100358a2)) ||
				  (rand_roll = 0, *(unsigned int*) (entity_offset + 0x100358aa) < *(unsigned int*) (entity_offset + 0x100358c0))) ||
				 (rand_roll = 0, *(char*) (entity_offset + 0x100358a8) == '\0')) {
			candidate_slot1 = 0xffff;
		}
		else {
			parent_slot_ptr = (int*) (entity_offset + 0x10035908);
			occupied_count = 0;
			entity_offset = 5;
			do {
				if (*parent_slot_ptr != -1) {
					occupied_count = occupied_count + 1;
				}
				parent_slot_ptr = parent_slot_ptr + 1;
				entity_offset = entity_offset + -1;
			} while (entity_offset != 0);
			rand_roll = gm_RandomMod(0x100);
			rand_roll = (rand_roll & 0xffff) + 1;
			if (rand_roll < prob_thresholds[occupied_count]) {
				break;
			}
		}
		attempt_count = attempt_count + 1;
	} while (attempt_count < 0x10);
	if (candidate_slot1 == 0xffff) {
		return rand_roll & 0xffff0000;
	}
	attempt2_count = 0;
	do {
		candidate_slot2 = gm_RandomMod(search_seed);
		attempt_count = candidate_slot2 * 0x21c;
		if (*(int*) (attempt_count + 0x100358a0) == -1) {
			search_seed = search_seed * 3 + (search_seed * 3 >> 0x1f & 3U) >> 2;
		}
		else if (((5 < *(unsigned int*) (attempt_count + 0x100358a2)) ||
				  (*(unsigned int*) (attempt_count + 0x100358aa) < *(unsigned int*) (attempt_count + 0x100358c0))) ||
				 (*(char*) (attempt_count + 0x100358a8) == '\0')) {
			candidate_slot2 = 0xffff;
		}
		else {
			parent_slot_ptr = (int*) (attempt_count + 0x10035908);
			entity_offset = 0;
			attempt_count = 5;
			do {
				if (*parent_slot_ptr != -1) {
					entity_offset = entity_offset + 1;
				}
				parent_slot_ptr = parent_slot_ptr + 1;
				attempt_count = attempt_count + -1;
			} while (attempt_count != 0);
			rand_roll = gm_RandomMod(0x100);
			rand_roll = (rand_roll & 0xffff) + 1;
			if (rand_roll < prob_thresholds[entity_offset]) {
				break;
			}
		}
		rand_roll = attempt2_count + 1;
		attempt2_count = rand_roll;
	} while (rand_roll < 0x10);
	if (candidate_slot2 != 0xffff) {
		search_seed = gm_CreateEntityFromParents(
			0,
			*(unsigned int*) (candidate_slot1 * 0x21c + 0x100358a4),
			*(unsigned int*) (candidate_slot2 * 0x21c + 0x100358a4),
			param_1,
			0,
			0,
			0,
			2
		);
		return search_seed;
	}
	return rand_roll & 0xffff0000;
}

// ORIGIN: GAME
// STATUS: RELOC
// SIZE: 83
// ANALYSIS: Updates priority tracking for dynamic entity dispatch/update lists. Limits simultaneous update weight using GetStatPair constraints.
// FUNCTION: SERVER 0x10015400
// sim_PriorityUpdate

void __cdecl sim_PriorityUpdate(char* ctx, char* entity)
{
	unsigned short info[2];
	unsigned char type;
	unsigned short prio;
	char* current;
	type = *(unsigned char*) entity;
	table_lookup((unsigned int) type, info);
	prio = (unsigned char) *(entity + 0x65);
	if (prio >= (unsigned short) info[0]) {
		return;
	}
	current = *(char**) (ctx + 0x170);
	if (current) {
		if (*(unsigned char*) (current + 0x65) > 0) {
			*(unsigned char*) (current + 0x65) -= 1;
		}
	}
	*(char**) (ctx + 0x170) = entity;
	*(unsigned char*) (entity + 0x65) += 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 145
// FUNCTION: SERVER 0x10015460
// sim_StartEntityQueryByType

void __cdecl sim_StartEntityQueryByType(unsigned char* param_1)
{
	char entity_kind;
	int owner;

	entity_kind = *(char*) (DAT_100a8c30 + (unsigned int) *param_1 * 0x24d);
	owner = *(int*) (param_1 + 0x5d);
	if (entity_kind == '\x01') {
		gm_StartEntityQuery(owner, 1, 0, 0x12);
		return;
	}
	if (entity_kind == '\x02') {
		gm_StartEntityQuery(owner, 1, 0, 0x13);
		return;
	}
	if (entity_kind == '\x1d') {
		gm_StartEntityQuery(owner, 1, 0, 0xfd);
		return;
	}
	if (entity_kind == '\x16') {
		gm_StartEntityQuery(owner, 1, 0, 0x120);
	}
	return;
}

// STATUS: RELOC
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), zero-extend pattern (xor vs mov)
// BLOCKER_DELTA: 138
// SIZE: 180
// FUNCTION: SERVER 0x10015500
// sim_CreateCitizen

void* __cdecl sim_CreateCitizen(
	unsigned char param_1,
	int param_2,
	int param_3,
	unsigned char param_4,
	unsigned char param_5
)
{
	unsigned int new_entity_slot;

	if ((param_1 & 1) != 0) {
		new_entity_slot = FindAndMatchParents(param_3) & 0xffff;
		if (new_entity_slot == 0xffff) {
			goto error;
		}
		if ((param_1 & 2) != 0) {
			(&DAT_10035a05)[new_entity_slot * 0x21c] = param_5;
			(&DAT_10035a04)[new_entity_slot * 0x21c] = param_4;
		}
	}
	else {
		new_entity_slot =
			gm_CreateEntityFromParents(param_2, -1, -1, param_3, 0, (unsigned int) param_4, (unsigned int) param_5, 2) &
			0xffff;
	}
	if (new_entity_slot == 0xffff) {
		goto error;
	}
	return &DAT_100358a0 + new_entity_slot * 0x21c;
error:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\sim.c",
		0x127d,
		"sim_CreateCitizen(): could not alloc spieler",
		1
	);
	return (void*) 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 197
// BLOCKER_DELTA: 164
// FUNCTION: SERVER 0x100155c0
// AdvanceGameClock

#pragma pack(push, 1)
typedef struct {
	int days;    /* 0x00 */
	short hours; /* 0x04 */
	int minutes; /* 0x06 */
	int seconds; /* 0x0a */
} TimeStruct;
#pragma pack(pop)

int __cdecl AdvanceGameClock(int* param_1, int param_2, int param_3, int param_4)
{
	int minutes_carry;
	unsigned int day_carry;
	unsigned int total_hours;

	param_4 = param_4 + *(int*) ((int) param_1 + 10);
	*(int*) ((int) param_1 + 6) = *(int*) ((int) param_1 + 6) + param_4 / 0x3c;
	*(int*) ((int) param_1 + 10) = param_4 % 0x3c;
	param_3 = *(int*) ((int) param_1 + 6) + param_3;
	*(short*) (param_1 + 1) = *(short*) (param_1 + 1) + (short) (param_3 / 0x3c);
	minutes_carry = param_3 / 0x3c;
	*(int*) ((int) param_1 + 6) = param_3 % 0x3c;
	total_hours = (unsigned int) *(unsigned short*) (param_1 + 1) + param_2;
	if (0x17 < (int) total_hours) {
		day_carry = total_hours / 0x18;
		total_hours = total_hours % 0x18;
		do {
			minutes_carry = *param_1 + 1;
			day_carry = day_carry - 1;
			*param_1 = minutes_carry;
		} while (day_carry != 0);
	}
	if ((int) total_hours < 0) {
		day_carry = (0x17 - total_hours) / 0x18;
		minutes_carry = total_hours + day_carry * 0x18;
		do {
			day_carry = day_carry - 1;
			*param_1 = *param_1 + -1;
		} while (day_carry != 0);
		*(short*) (param_1 + 1) = (short) minutes_carry;
		return minutes_carry;
	}
	*(short*) (param_1 + 1) = (short) total_hours;
	return minutes_carry;
}

// ORIGIN: GAME
// STATUS: EXACT
// SIZE: 41
// FUNCTION: SERVER 0x10015690
// sim_SetSyncParams

void __cdecl sim_SetSyncParams(int param_1, unsigned char param_2, unsigned int param_3, unsigned int param_4)
{
	*(unsigned int*) (param_1 + 10) = param_4 & 0xff;
	*(unsigned short*) (param_1 + 4) = (unsigned short) param_2;
	*(unsigned int*) (param_1 + 6) = param_3 & 0xff;
}
