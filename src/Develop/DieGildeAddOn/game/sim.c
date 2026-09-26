#include "../../Units/Error/error.h"
#include "rebrew_types.h"
#include "rebrew_globals.h"
extern int __cdecl gm_RandomMod(unsigned short range);
unsigned int __cdecl gm_AllocSpieler(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
void __cdecl plt_TableLookup(unsigned int a, unsigned short* b);
unsigned short __cdecl sim_FindAndMatchParents(unsigned int param);
extern unsigned char g_entity_type_bytes[1];
extern unsigned char g_slot_table[2];
/* 0x10035a05: the byte at +0x165 of each 0x21c-byte g_slot_table record. */
#define g_stat_b_array ((unsigned char*) g_slot_table + 0x165)
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);

/* Simulation entity records are 0x21c bytes, based at g_slot_table
 * (0x100358a0).  Fields used here: +0x00 slot id (0xffff = free),
 * +0x02 state byte, +0x04 entity id, +0x08 usable flag, +0x0a weight,
 * +0x20 float threshold, +0x68 five linked children.
 *
 * Records are addressed by byte offset into g_slot_table rather than
 * through a struct pointer.  Subscripting the array keeps the pure record
 * offset in a register and leaves the symbol as each access's displacement
 * (`lea ecx,[eax+eax*8]` / `shl ecx,2` / `cmp word[ecx+g_slot_table+0x0]`),
 * which is what the target does.  A struct pointer built from the address
 * of a scalar folds the final *4 into the SIB scale and adds the symbol
 * into the pointer instead, which cost every access in both scan loops. */
#define SIM_ENT_OFF(i) (((i) & 0xffff) * 0x21c)

/* Searches for matching parent entities by type and creates
 * family tree linkages. Used in citizen creation to find
 * compatible parents for stat inheritance. */

// FUNCTION: SERVER 0x100151e0
// sim_FindAndMatchParents

unsigned short __cdecl sim_FindAndMatchParents(unsigned int param)
{
	int weights[6];
	unsigned int off;
	unsigned int rnd;
	unsigned int count;
	unsigned short parentA;
	unsigned short parentB;
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
		off = SIM_ENT_OFF(rnd);
		if (*(unsigned short*) &g_slot_table[off] == 0xffff) {
			i = i * 3 / 4;
			continue;
		}
		f1 = (float) *(unsigned short*) &g_slot_table[off + 0xa];
		if (g_slot_table[off + 0x2] < 6 && f1 >= *(float*) &g_slot_table[off + 0x20] &&
		    g_slot_table[off + 0x8] != 0) {
			count = 0;
			for (k = 0; k < 5; k++) {
				if (((int*) &g_slot_table[off + 0x68])[k] != -1) {
					count++;
				}
			}
			if ((int) ((gm_RandomMod(0x100) & 0xffff) + 1) < weights[count]) {
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
		off = SIM_ENT_OFF(rnd);
		if (*(unsigned short*) &g_slot_table[off] == 0xffff) {
			i = i * 3 / 4;
			continue;
		}
		f2 = (float) *(unsigned short*) &g_slot_table[off + 0xa];
		if (g_slot_table[off + 0x2] < 6 && f2 >= *(float*) &g_slot_table[off + 0x20] &&
		    g_slot_table[off + 0x8] != 0) {
			count = 0;
			for (k = 0; k < 5; k++) {
				if (((int*) &g_slot_table[off + 0x68])[k] != -1) {
					count++;
				}
			}
			if ((int) ((gm_RandomMod(0x100) & 0xffff) + 1) < weights[count]) {
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

	return (unsigned short) gm_AllocSpieler(
		0,
		*(int*) &g_slot_table[SIM_ENT_OFF(parentA) + 0x4],
		*(int*) &g_slot_table[SIM_ENT_OFF(parentB) + 0x4],
		(int) param,
		0, 0, 0, 2);
}

/* Updates entity priority/scheduling. Called during simulation
 * tick to adjust entity processing order based on game state. */

// FUNCTION: GOLD 0x004fda10
// SIZE: 83
// FUNCTION: GOLDTL 0x5001e0
// SIZE: 83
// FUNCTION: SERVER 0x10015400
// sim_PriorityUpdate

void __cdecl sim_PriorityUpdate(char* ctx, char* entity)
{
	unsigned short tmp[4];
	char* old;

	plt_TableLookup((unsigned char) entity[0], tmp);
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

// FUNCTION: GOLD 0x4fdc10
// SIZE: 160
// FUNCTION: GOLDTL 0x005003e0
// SIZE: 160
// FUNCTION: SERVER 0x10015460
// sim_StartEntityQueryByType

unsigned short* __cdecl sim_StartEntityQueryByType(unsigned char* arg1)
{
	unsigned short* result = 0;
	unsigned char cls;
	unsigned char* base;
	unsigned char* slot;
	unsigned int idx;
	unsigned int off;

	/* The function returns the query handle, and that is what produced the
	 * `xor eax,eax` that ten earlier probing rounds chased as a constant-0
	 * argument.  eax holds the fall-through return value 0, materialised
	 * before the dispatch; the cls==1 arm reuses that still-live register for
	 * its third argument (`push eax`) while the three later arms, whose eax
	 * was clobbered by the preceding call, push the literal.  The extra live
	 * value across all four calls is also what forces the second callee-saved
	 * register (edi) the target saves.  Nothing about the argument spelling
	 * was ever reachable; the signature was wrong.
	 *
	 * Prior rounds measured a ceiling of 18/145 on the void signature and
	 * logged the zero argument as unreachable; that conclusion was an artefact
	 * of the missing return value.  Also confirmed while closing this: the
	 * volatile record read gives the target's `lea` + `mov cl,[ecx]` pair where
	 * a plain read folds into a scaled `mov cl,[edi+ecx*4]`, and the table must
	 * be read as a plain pointer, not through a volatile alias, or
	 * `mov ecx,[esp+4]` sinks below `push edi`. */
	idx = arg1[0];
	base = (unsigned char*) g_entity_type_table + idx;
	off = idx * 588;
	slot = base + off;
	cls = *(volatile unsigned char*) slot;
	if (cls == 1) {
		result = gm_ff_Objekt(*(int*) (arg1 + 0x5d), 1, 0, 0x12);
	} else if (cls == 2) {
		result = gm_ff_Objekt(*(int*) (arg1 + 0x5d), 1, 0, 0x13);
	} else if (cls == 0x1d) {
		result = gm_ff_Objekt(*(int*) (arg1 + 0x5d), 1, 0, 0xfd);
	} else if (cls == 0x16) {
		result = gm_ff_Objekt(*(int*) (arg1 + 0x5d), 1, 0, 0x120);
	}
	return result;
}

/* Creates a new citizen entity with initial stats generated
 * from parent entities. Allocates entity memory, assigns random
 * stats via gm_AllocSpieler, and links to home. */

// FUNCTION: SERVER 0x10015500
// sim_CreateCitizen

void* __cdecl sim_CreateCitizen(unsigned char flags, int citizen_type, int parent_id, unsigned char stat_a, unsigned char stat_b)
{
	unsigned int new_entity_slot;

	if ((flags & 1) != 0) {
		new_entity_slot = sim_FindAndMatchParents(parent_id) & 0xffff;
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
			gm_AllocSpieler(citizen_type, -1, -1, parent_id, 0, (unsigned int) stat_a, (unsigned int) stat_b, 2) &
			0xffff;
	}
	if (new_entity_slot == 0xffff) {
		goto error;
	}
	return g_slot_table + new_entity_slot * 0x21c;
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
// sim_AdvanceGameClock

#pragma pack(push, 1)
// SIZE 0xe
typedef struct {
	int x00;             /* +0x00 */
	unsigned short x04;  /* +0x04 */
	int x06;             /* +0x06 */
	int x0a;             /* +0x0a */
} SIM_CLOCK;
#pragma pack(pop)

#pragma optimize("a", on)
void __cdecl sim_AdvanceGameClock(SIM_CLOCK* clock, int arg2, int arg3, int arg4)
{
	unsigned short* p4 = &clock->x04;
	int minutes;
	int days;

	/* Each of the three carries takes its own argument: the target reads
	 * [esp+0x10] before `push esi` (arg4), [esp+0x10] after the push
	 * (arg3) and [esp+0xc] after it (arg2).
	 *
	 * Three shapes are load-bearing for the byte match:
	 *   - `#pragma optimize("a", on)` (assume no aliasing) lets msvc6 hoist
	 *     the x04 read above the x06 store at 0x64, matching the target's
	 *     `xor esi,esi; mov si,[ecx+4]; mov [ecx+6],edx` order.  Without it
	 *     the two are transposed and the body scores 187/197.
	 *   - The two 60-minute carries are written without temporaries: each
	 *     sum appears twice, once under `/ 60` and once under `% 60`, and
	 *     msvc6 CSEs the pair into one imul/idiv chain.  Naming a sum in a
	 *     local costs 5 bytes (192 against the 197-byte target).
	 *   - Both `minutes < 0` and the fallthrough exit through one tail store
	 *     to x04.  With a `return` inside the branch and a duplicated store,
	 *     loop 2's `mov [ecx],esi` schedules ahead of `dec edx` (194/197);
	 *     merged, the store sinks below the decrement as the target has it.
	 *
	 * `minutes += *(volatile int*) &arg2` is required: read plain, msvc6
	 * folds the load into `add esi,[esp+0xc]` and the tail loses 76 bytes.
	 * `p4`, a plain `unsigned short*` alias of x04, gives the target's
	 * `xor esi,esi` + `mov si,word[ecx+4]`; a volatile ushort read emits a
	 * 6-byte `and esi,0xffff` instead. */
	clock->x06 = clock->x06 + (arg4 + clock->x0a) / 60;
	clock->x0a = (arg4 + clock->x0a) % 60;
	clock->x04 = (unsigned short) (clock->x04 + (arg3 + clock->x06) / 60);
	clock->x06 = (arg3 + clock->x06) % 60;
	minutes = *p4;
	minutes += *(volatile int*) &arg2;
	if (minutes >= 24) {
		days = (unsigned int) minutes / 24;
		minutes = minutes - days * 24;
		do {
			clock->x00++;
		} while (--days != 0);
	}
	if (minutes < 0) {
		days = (unsigned int) (23 - minutes) / 24;
		minutes = minutes + days * 24;
		do {
			clock->x00--;
		} while (--days != 0);
	}
	clock->x04 = (unsigned short) minutes;
}
#pragma optimize("", on)

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
