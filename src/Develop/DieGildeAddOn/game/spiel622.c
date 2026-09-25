#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"
#pragma intrinsic(memcpy, memset)

extern int g_query_limit;
extern unsigned char g_slot_table[2];
extern int g_next_object_id; 
int g_current_year;
extern char s_D__Develop_DieGildeAddOn_game_sp_10031004[]; 
extern int g_citizen_count;
int __cdecl gm_GetBuildingTypeCategory(int btype);
int __cdecl gm_WalkEntityChain(int);
extern float g_const_1_5; 
extern float g_const_2_2; 
extern float g_const_0_06875; 
extern float g_const_896_0; 
extern double g_const_1_over_720; 
extern float g_const_0_0; 
extern float g_gv_const_57c8; 
extern double g_const_half; 
double __cdecl gm_CalculateProductionValue(int, unsigned char);
extern unsigned char g_current_season;
int __cdecl gm_SumBuildingProductionValues(char*, int);
int __cdecl gm_EntityQuerySum(int);
int __cdecl compute_size(char*); 
char* __cdecl gm_FindEntityByOwner(int); 
int __cdecl gm_GetMsgField(char*, char*); 
int __cdecl ahm_LookupEntityInTable(int); 

// DATA: SERVER 0x10031628
char s_gm_KannObjektHergestellt___pCObj_10031628[] = "gm_eval_SlotVoll(): Lager ist in keinem Geb\344ude";
// FUNCTION: GOLD 0x00508660
// SIZE: 77
// FUNCTION: GOLDTL 0x50b7c0
// SIZE: 77
// FUNCTION: SERVER 0x100196c0

// gm_QueryEntitySum

int __cdecl gm_QueryEntitySum(int entity, unsigned int obj_type)
{
	short* ent;
	int total;

	total = 0;
	ent = gm_ff_Objekt(entity, 1, 4, 9);
	if (ent != (short*) 0) {
		do {
			if ((short) g_entity_slot_table[(obj_type & 0xff) * 189] == *ent) {
				total = total + *(int*) (ent + 7);
			}
			ent = gm_NextEntityQueryMatch();
		} while (ent != (short*) 0);
	}
	return total;
}

/* Calculates the production value for a building. Sums
 * worker skill, building quality, and recipe bonuses to
 * determine output rate. */


// FUNCTION: SERVER 0x10019720
// gm_CalculateProductionValue
//   Byte-exact at the link.  The last residue, `fxch st(1)` / `cmp byte
//   ptr [esi],0x17` at 0x10019804, is explained at the merge statement.
//   Compiled size is 396 bytes, equal to the target's 396 bytes of code; the
//   `size = 400` in the metadata is the padded slot, not a code-size shortfall.
//
//   Codegen rules established by compiling isolated probes with the project
//   toolchain (rebrew-cmake-cl /O2 /Gd) and reading the objects:
//   - `fimul`/`fidiv` against a memory operand require the integer operand to
//     be LIVE PAST the FPU op. When its last use is the multiply/divide itself,
//     msvc6 keeps it in a register and emits `fild` + `fmulp`/`fdivp`. Neither
//     `*(int*) &param2` nor an assignment through an `int*` alias changes this
//     by itself; only a genuine later read does.
//   - The target's `fxch st(1)` + `faddp st(1)` loop shape requires the
//     accumulator to be `float`, not `double`: rounding each iteration back to
//     float leaves the running sum in st(1) and produces the exchange. With a
//     `double` accumulator msvc6 emits `faddp` alone. Hence `mod_value` is
//     declared `float` and the loop body carries the explicit `(float)` cast.
//
//   Resolved 2026-09-04: a *volatile* alias keeps the integer operand
//   memory-resident without emitting extra code ahead of the FPU op, which a
//   plain `int*` alias does not. Applied to `param2` (fimul) and `divisor`
//   (fidiv); reading the 0x21 byte through `volatile char` likewise stops
//   msvc6 folding the load into `cmp byte ptr [mem],3` and restores the
//   target's `mov al` / `fimul` / `cmp al,3` order. 132 -> 263 matched
//   instructions. See docs/msvc6-c-shapes.md sections 8a and 8b.
//
//   Resolved 2026-09-04 (263 -> 322): the numerator/divisor order and the
//   fidiv both fall out of two distinct aliasing levers, one per site.
//   - A volatile READ of the numerator (`*(volatile int*) (entity + 0x22)`)
//     pins that load ahead of the divisor computation, giving the target's
//     `mov edx,[esi+0x22]` / `mov ax,[esi+0x36]` order and the qword home at
//     [esp+8]/[esp+0xc].
//   - The divisor then needs a PLAIN `int*` alias, not a volatile one. Both
//     produce `fidiv <mem>`, but the volatile store is ordered against the
//     numerator's volatile read and so is forced ahead of the `fild qword`;
//     a plain alias leaves msvc6 free to sink `mov [esp+0x14],edx` after the
//     fild, which is what the target does. This is the generalisable point:
//     volatile forces residency AND ordering, a plain alias forces residency
//     only, so pick the weaker lever when the target's schedule is looser.
//   Instructions 30..47 (the whole numerator/divisor/fidiv block) now match.
//
//   Resolved 2026-09-04 (322 -> 374), all four by probe:
//   - The composite loop's `fimul [esp+0x20]` / `fidiv [esp+0x20]` on ONE
//     reused slot needs MIXED aliasing on that slot: a plain `int*` store for
//     the numerator and a volatile store for the divisor. Both-plain leaves
//     `fild` + `fdivr`; both-volatile also works for the pair but the earlier
//     note that a single slot could not produce both ops was wrong. Feeding
//     the quotient through a `double*` alias (`*sub = *sub * ...`) makes the
//     quotient the destination of the add, so the accumulation is
//     `fadd [esp+0x1c]` / `fstp [esp+0x1c]` with no leftover stack entry.
//   - The loop-advance order (`inc ebx` before `add edi,2`) comes from a
//     `while` with the counter incremented ahead of the pointer; a `for`
//     header emits them the other way round.
//   - Copying `value` into a float temp before each of the two float
//     multiplies makes `value` the memory operand, giving the target's
//     `fld [esp+N]` / `fmul <const>` instead of `fld <const>` / `fmul [esp+N]`.
//   - The epilogue's `fild [esp+0x1c]` / `fmul [esp+0x14]` needs the masked
//     `param2` homed through a PLAIN `int*` alias and widened in a separate
//     statement. A volatile alias there is ordered against the +0x38 store and
//     schedules the `and` before the ftol call, which the target does not do.
//
//   Resolved 2026-09-08 (378 -> 386): `#pragma optimize("a", on)` around the
//   function. Three of the seven residual instructions were the epilogue
//   transposition, and the obstacle was the aliasing assumption, not any
//   statement order: msvc6 must assume the `[esi+0x38]` store may alias the
//   frame slots it reads, so it keeps source order and sinks `pop edi` below
//   both stores. With "a" it emits the target's `pop edi` / `mov [esp+0x1c],ebp`
//   / `mov [esi+0x38],eax` / `fild` sequence with no source change at all. See
//   docs/msvc6-c-shapes.md section 44. File-mates hold their status; the flag
//   is scoped by the closing `#pragma optimize("", on)` after the body.
//   Layering a second flag on top of "a" is inert or worse ("g"/"t"/"w"/"y" on
//   and "record_cursor"/"s"/"w" off all hold 386; "record_cursor" on, "s" on, "t" off, "y" off and
//   "g" off collapse the body). CFLAGS remain inert at both 378 and 386:
//   /G3 /G4 /G5 /Ox /Gy /Oi- /Ob0 all score identically, /G6 /Op /O1 /Ot
//   collapse.
//
//   The `unsigned char` second parameter in the forward declaration above is
//   load-bearing for gm_SumBuildingProductionValues (0x100198b0, 218/355) and
//   gm_EntityQuerySum (0x10019a70, RELOC); widening it to `int` regresses both.
#pragma optimize("a", on)
double __cdecl gm_CalculateProductionValue(int entity_index, int param2)
{
	char* entity;
	char* record;
	float value;
	double quot;
	float mod_value;
	float quot_f;
	int i;
	int min_val;
	int divisor;
	int weight;
	int* divisor_ptr;
	unsigned short comp;
	unsigned short* ingredient_cursor;
	double* sub;
	int slot;
	int* slot_p;
	volatile int* slot_v;
	int* p2_home;
	double p2_wide;
	double acc;

	entity = (char*) g_item_def_table + entity_index * 0x41;
	if (*(int*) (entity + 0x38) != 0) {
		double cached;
		volatile int* p2_alias;
		char kind;

		/* The volatile alias keeps param2 memory-resident past the multiply,
		   which makes msvc6 fuse it into `fimul <mem>` rather than emitting a
		   separate fild + fmulp, and schedules the mask after the fild.
		   See docs/msvc6-c-shapes.md. */
		entity_index = *(int*) (entity + 0x38) << 5;
		cached = entity_index;
		p2_alias = (volatile int*) &param2;
		*p2_alias = param2 & 0xff;
		kind = *(volatile char*) (entity + 0x21);
		cached = cached * (int) *p2_alias;
		cached = cached * g_const_0_01;
		if (kind == 3) {
			cached = cached * g_const_1_5;
		}
		return cached;
	}

	/* Reading the numerator through a volatile lvalue pins its load ahead of
	   the divisor computation, and assigning the divisor through a volatile
	   alias keeps it memory-resident, so msvc6 emits `fild qword` on the homed
	   numerator followed by `fidiv <mem>` rather than fild + fdivrp.
	   See docs/msvc6-c-shapes.md. */
	quot = (double) (unsigned int) *(volatile int*) (entity + 0x22);
	divisor = (*(unsigned short*) (entity + 0x36) == 0) + *(unsigned short*) (entity + 0x36);
	divisor_ptr = &divisor;
	quot = quot / *divisor_ptr;
	quot_f = (float) quot;
	min_val = *(int*) (entity_index * 4 + 0x101dd8e0);
	record = g_entity_type_table + min_val * 0x24d;
	if (min_val != 0) {
		mod_value = g_const_0_0;
		for (i = 0; i < 2; i++) {
			weight = *(unsigned char*) (record + i + 0x233);
			mod_value = (float) ((double) weight * g_const_896_0 * g_const_1_over_720 + mod_value);
		}
	} else {
		mod_value = g_gv_const_57c8;
	}
	/* The quotient is scaled in place as a float register variable that
	   is its own destination, as the composite loop does with `mod_value`:
	   msvc6 fetches the old value (`fxch st(1)`, c2 opcode 95, paired with
	   the qword `fmul`) straight into the `fmulp`, with no copy node after
	   the fetch.  The scheduler's hold after a fetch (c2 0x10727d01) delays
	   integer work only while an x87 node is ready within one cycle; here
	   none is until the `fmul` latency ends, so the 0x17 byte load and
	   compare issue between the `fxch` and the `fmulp`, as at 0x10019804.
	   A double copy (`acc = quot`) adds a copy node the hold waits on and
	   puts the compare after the `fstp`; scaling `mod_value` instead leaves
	   the fetch behind the compare.  The float rounding emits no code. */
	quot_f = (float) (quot_f * ((double) mod_value * g_const_half));
	value = quot_f;
	if (*(char*) entity == 0x17) {
		mod_value = value;
		return (float) ((double) mod_value * g_const_2_2);
	}
	ingredient_cursor = (unsigned short*) (entity + 0x2e);
	/* A `while` with the counter incremented ahead of the pointer gives the
	   target's `inc ebx` / `add edi,2` order; a `for` header emits them the
	   other way round. */
	i = 0;
	while (i < 4) {
		comp = *ingredient_cursor;
		if (comp == 0) {
			break;
		}
		if (comp != 0xffff) {
			/* One reused stack slot feeds both `fimul` and `fidiv`: the
			   numerator store goes through a plain alias, the divisor store
			   through a volatile one. Accumulating through `sub` keeps the
			   quotient the destination, giving `fadd <mem>` + `fstp <mem>`
			   with no leftover stack entry. `quot` is dead once `value` is
			   computed, so it doubles as the sub-result home rather than
			   costing another slot. */
			slot_p = &slot;
			slot_v = (volatile int*) &slot;
			sub = &quot;
			*sub = gm_CalculateProductionValue(comp, param2);
			*slot_p = (int) ingredient_cursor[-4];
			*sub = *sub * *slot_p;
			*slot_v = (int) *(unsigned short*) (entity + 0x36);
			*sub = *sub / *slot_v;
			*sub = *sub + value;
			value = (float) *sub;
		}
		i++;
		ingredient_cursor++;
	}
	/* Homing the masked param2 through a PLAIN int alias and widening it in a
	   separate statement makes it the FPU stack top, so the epilogue is
	   `fild <slot>` / `fmul <value>` as in the target rather than
	   `fld value` / `fimul param2`. A volatile alias here is ordered against
	   the +0x38 store and schedules the `and` before the ftol call, which the
	   target does not do. The store must precede the mask for the same reason.
	   `mod_value` is dead by this point and is reused as the float temp so the
	   frame does not grow another slot. */
	p2_home = &param2;
	mod_value = value;
	*(int*) (entity + 0x38) = (int) (mod_value * g_const_0_06875);
	*p2_home = param2 & 0xff;
	p2_wide = *p2_home;
	acc = p2_wide;
	acc = acc * value;
	acc = acc * g_const_0_01;
	return acc * g_const_2_2;
}
#pragma optimize("", on)

/* Sums production values across all buildings of a type.
 * Aggregates daily/weekly output for economic reporting. */

// FUNCTION: SERVER 0x100198b0
// gm_SumBuildingProductionValues
//   RELOC 355/355. Four fixes took it from 218: indexing the item table inline
//   rather than through a `char*` local emits the original's folded
//   `mov al,[eax+edx]`; the second query result must go to its own local
//   instead of overwriting `query_result`, because the original keeps the outer query in
//   esi across the branch; the epilogue multiply order is
//   `(param2 * g_const_0_01) * total`, which emits fild/fmul/fimul, where the
//   `(double)` casts emitted fld/fimul/fimul; and the inner call's `query_result+0x14`
//   load stays inside the argument list, which is what emits the original's
//   `push eax` / `mov eax,[esi+0x14]` / ... / `push eax` schedule. Hoisting
//   that load into a local (`qbase`) materialises it into ecx before the
//   pushes and costs 5 bytes.
//   The last fix was the whole-function esi/edi role swap that made the hoist
//   look necessary. It is decided by the OUTER call's first argument: reading
//   `*query_result` into an `int` local and passing that, instead of passing `*query_result`
//   directly, puts the query in esi and the cursor in edi as the original has
//   them, and it also reproduces the original's
//   `mov dl,[esi+0x12]` / `xor eax,eax` / `mov ax,[esi]` order. The local's
//   width matters: `unsigned short` emits an `and eax,0xffff` widen and
//   reorders the two field reads (SIZE_MISMATCH, 167); `int` is exact.
//   Dead ends measured on the hoisted shape (all 350, register swap right but
//   schedule wrong): dead-hoist beside the inline load, `register int`,
//   comma/assignment folded into the argument, address-only and `int*`/`char*`
//   alias hoists, `((int*) query_result)[5]`, `*(int*)(query_result + 0xa)` in short units, hoisting
//   the masked id instead, and hoisting the outer call's `obj+0x5d`.
//   Dead ends on the inline shape (all 343, schedule right but registers
//   swapped): declaration order (all 10 positions for comp_ptr), `register`
//   qualifiers on either pointer, swapping the init order of `query_result` and
//   `comp_ptr` (336), a `volatile int*` inline load (337), `query_result`/`sub`/
//   `have_query` retyped, a `!=` loop bound, an end-pointer loop bound, and
//   hoisting `next_comp` above the branch. A redundant `if (query_result != 0)` guard
//   around the inner call flips the registers but reverts the schedule, and
//   `query_result == comp_ptr` style dead compares flip them at the cost of a
//   `sub esp,8` frame and a `have_query` spill.
int __cdecl gm_SumBuildingProductionValues(char* obj, int param2)
{
	char* record;
	unsigned short* query_result;
	int total;
	char have_query;
	unsigned short* comp_ptr;
	unsigned short* sub;
	int i;
	unsigned short comp;
	unsigned short next_comp;
	int q_slot;
	char* comp_record;

	record = (char*) g_entity_type_table + (unsigned char) obj[0] * 0x24d;
	total = *(int*) (record + 0x249) * 0xf00;
	query_result = NULL;
	have_query = 0;
	i = 0;
	comp_ptr = (unsigned short*) (record + 0x25);
	while (i < 0x40) {
		comp = comp_ptr[-1];
		if (comp == 0) {
			break;
		}
		comp_record = (char*) g_item_def_table + (comp & 0x7fff) * 0x41;
		if (have_query == 0) {
			if (*comp_record == 2 || *comp_record == 6) {
				query_result = gm_ff_Objekt(*(int*) (obj + 0x5d), 1, 0, comp & 0x7fff);
				if (query_result != NULL) {
					q_slot = *query_result;
					total = (int) (gm_CalculateProductionValue(q_slot, *(unsigned char*) ((char*) query_result + 0x12)) + (double) total);
					if (i < 0x3f) {
						next_comp = *comp_ptr;
						if (((char*) g_item_def_table)[(next_comp & 0x7fff) * 0x41] != 2 && ((char*) g_item_def_table)[(next_comp & 0x7fff) * 0x41] != 6) {
							have_query = 1;
						}
					}
				}
			}
		} else if (query_result != NULL) {
			sub = gm_ff_Objekt(*(int*) ((char*) query_result + 0x14), 1, 0, comp & 0x7fff);
			if (sub != NULL) {
				total = (int) (gm_CalculateProductionValue(*sub, *(unsigned char*) ((char*) sub + 0x12)) + (double) total);
			}
			if (i < 0x3f) {
				next_comp = *comp_ptr;
				if (((char*) g_item_def_table)[(next_comp & 0x7fff) * 0x41] == 2 || ((char*) g_item_def_table)[(next_comp & 0x7fff) * 0x41] == 6) {
					have_query = 0;
				}
			}
		}
		i++;
		comp_ptr++;
	}
	return (int) ((param2 * g_const_0_01) * total);
}

// FUNCTION: GOLDTL 0x0050d2a0
// SIZE: 74
// FUNCTION: SERVER 0x10019A20
// gm_AccumulateTyped2

int __cdecl gm_AccumulateTyped2(char* entity)
{
	int sum;
	int result;
	unsigned int idx;
	sum = 0;
	idx = (unsigned int) (unsigned char) g_current_season * 189;
	result = (int) gm_ff_Objekt(
	    *(int*) (entity + 0x178), 1, 0, (int) (unsigned short) g_entity_slot_table[idx]);
	if (result) {
		do {
			sum += *(int*) (result + 0xe);
			result = (int) gm_NextEntityQueryMatch();
		} while (result);
	}
	return sum;
}

// FUNCTION: GOLDTL 0x0050d3c0
// SIZE: 102
// FUNCTION: SERVER 0x10019a70
// gm_EntityQuerySum

int __cdecl gm_EntityQuerySum(int arg1)
{
	int sum;
	void* head;
	unsigned short* query_result;

	sum = 0;
	head = gm_ff_Objekt(*(int*) (arg1 + 0x5d), 2, 6, sum, 0x2a);
	if (head != NULL) {
		query_result = gm_ff_Objekt(*(int*) ((char*) head + 0x14), 1, 5);
		if (query_result != NULL) {
			do {
				sum = (int) (gm_CalculateProductionValue(*(unsigned short*) query_result, *(unsigned char*) ((char*) query_result + 0x12)) + (double) sum);
				query_result = gm_NextEntityQueryMatch();
			} while (query_result != NULL);
		}
	}
	return sum;
}

/* Resolves a parent entity reference. Follows entity chain
 * links to find the parent. Returns parent pointer. */

// FUNCTION: GOLDTL 0x0050d490
// SIZE: 96
// FUNCTION: SERVER 0x10019ae0
// gm_ResolveParentEntity

short* __cdecl gm_ResolveParentEntity(short* entity)
{
	void* dynamic_ent;

	gm_ResolveEntityById(&dynamic_ent, (void**) 0, (void**) &entity, *(int*) (entity + 5));
	if (entity == (short*) 0) {
		if (dynamic_ent != (void*) 0 && *(unsigned short*) ((int) dynamic_ent + 0x27) != 0xffff) {
			return (short*) ((char*) &g_slot_table +
			    (unsigned int) *(unsigned short*) ((int) dynamic_ent + 0x27) * 0x21c);
		}
		entity = (short*) 0;
	}
	return entity;
}

/* Gets the type (class) of an entity as an unsigned short.
 * Reads from the entity's type field. */

// FUNCTION: GOLDTL 0x0050d530
// SIZE: 64
// FUNCTION: SERVER 0x10019b40
// gm_GetEntityType

unsigned short __cdecl gm_GetEntityType(short* entity)
{
	void* dynamic_ent;

	gm_ResolveEntityById(&dynamic_ent, (void**) 0, (void**) &entity, *(int*) (entity + 5));
	if (entity != (short*) 0) {
		return *entity;
	}
	if (dynamic_ent != (void*) 0) {
		return *(unsigned short*) ((int) dynamic_ent + 0x27);
	}
	return (short) 0xffff;
}

/* Walks an entity chain, calling a callback for each node.
 * Traverses linked entity lists for processing. */

// FUNCTION: GOLDTL 0x0050d570
// SIZE: 83
// FUNCTION: SERVER 0x10019b80
// gm_EntityAccumulate

int __cdecl gm_EntityAccumulate(void* entity)
{
	int result;
	int entity_id;
	void* existing_ent;
	void* static_ent;

	entity_id = *(int*) ((int) entity + 6);
	while (entity_id != -1) {
		result = gm_ResolveEntityById((void**) &entity, &static_ent, &existing_ent, entity_id);
		if (result == 0) {
			return 0;
		}
		if (entity != (void*) 0) {
			return (int) entity;
		}
		if (existing_ent != (void*) 0) {
			return 0;
		}
		if (static_ent != (void*) 0) {
			entity_id = *(int*) ((int) static_ent + 6);
		}
	}
	return 0;
}

/* Runs an entity query and sums a field across all results.
 * Combines query iteration with field accumulation. */

// FUNCTION: SERVER 0x10019BE0
// gm_WalkEntityChain

int __cdecl gm_WalkEntityChain(int raw_idx)
{
	unsigned short idx;
	int slot;
	int ent;
	int total;
	idx = (unsigned short) raw_idx;
	if (idx >= 0x300) {
		return -1;
	}
	slot = (unsigned int) idx * 0x21c + 0x100358a0;
	if (*(unsigned short*) slot == 0xFFFF) {
		return -1;
	}
	total = gm_AccumulateTyped2((char*) slot);
	ent = (int) gm_StartFilteredEntitySearch(1, 3, (int) idx);
	if (ent) {
		do {
			total += gm_SumBuildingProductionValues((char*) ent, (int) *(signed char*) (ent + 0x5c));
			total += gm_EntityQuerySum(ent);
			ent = (int) gm_FindNextFilteredEntity();
		} while (ent);
	}
	return total;
}

/* Accumulates values along an entity chain. Walks linked
 * entities and sums a specified field. */

// FUNCTION: SERVER 0x10019c60
// gm_FindEntityByOwner

/* The walk is a pointer sweep bounded by the end address, with the
 * index carried alongside only to build the result; an indexed loop
 * emits the address recomputation inside the body instead.  The result
 * local zeroed before the arg1 test lets both no-match exits share one
 * `xor eax,eax` and puts arg1 in edi / the index in esi. */
char* __cdecl gm_FindEntityByOwner(int arg1)
{
	int i;
	int record_cursor;
	char* record;

	record = NULL;
	if (arg1 == 0) {
		return record;
	}
	i = 0;
	record_cursor = 0x100358a2;
	while (record_cursor < 0x1009aca2) {
		if (*(char*) (record_cursor + 0x162) != 0 && *(int*) (record_cursor + 0x16a) == arg1) {
			if (*(char*) record_cursor == 6 || *(char*) record_cursor == 7 || *(char*) record_cursor == 1 ||
			    *(char*) record_cursor == 2) {
				record = (char*) (0x100358a0 + i * 0x21c);
				break;
			}
		}
		record_cursor += 0x21c;
		i++;
	}
	return record;
}

/* Finds an entity by its owner. Searches for an entity
 * whose owner field matches the given ID. */

// FUNCTION: GOLDTL 0x0050df70
// SIZE: 48
// FUNCTION: SERVER 0x10019CD0
// gm_GetMsgField
int __cdecl gm_GetMsgField(char* msg, char* pkt)
{
	unsigned short type;

	type = *(unsigned short*) msg;
	if (type == 0x2a || type == 0x116 || type == 0x1db || type == 0x1dc) {
		return *(int*) (pkt + 0xe) - 1;
	}
	return *(int*) (pkt + 0xe);
}

/* Gets a message field from a command packet. Reads a
 * specific field from the packet's payload section. */

// FUNCTION: SERVER 0x10019d00
// compute_size
int __cdecl compute_size(char* pkt)
{
	if (*(short*) pkt == 0x1dd) {
		return (*(int*) (pkt + 0xe) + 2) * 5;
	}
	if (*(int*) (pkt + 0xe) == 3) {
		return 0x50;
	}
	return *(int*) (pkt + 0xe) * 0x14;
}

/* Checks if an object can be produced (Kann Objekt Hergestellt).
 * Validates recipe requirements, ingredient availability,
 * worker skills, and building capability. */

// FUNCTION: SERVER 0x10019d30
// gm_eval_SlotVoll
//   RELOC 407/407. The earlier note blaming register allocation was wrong; the
//   source had three separate bugs, each costing the rest of the function:
//   the second and third arguments were transposed (the item id is arg2, not
//   arg3, so the query and item-table index used the wrong value), the
//   gm_GetMsgField arguments were in the wrong order, and the three
//   "cap reached" exits were spelled as separate returns. Merging them into
//   one shared tail (the goto below) gives the single `xor eax,eax` epilogue
//   and the single min() block the original emits, closing 146/407 to 407/407.

int __cdecl compute_size(char* pkt, int param2);

int __cdecl gm_eval_SlotVoll(char* obj, int item_id, int requested)
{
	char* pkt;
	char* ent;
	char* record;
	int is_cat2;
	int is_producer;
	int size;
	int count;
	int msg_field;
	void* query_result;
	int q_id;

	pkt = obj;
	ent = (char*) gm_EntityAccumulate((void*) pkt);
	if (ent == NULL) {
		LogMessageInternal((char*) 0x10031004, 0x31de, (char*) 0x10031628, 1);
		return 0;
	}
	is_cat2 = (gm_GetBuildingTypeCategory((unsigned char) *ent) == 2);
	size = compute_size(pkt, item_id);
	query_result = gm_ff_Objekt(*(int*) (pkt + 0x14), 1, 0, item_id);
	if (query_result != NULL) {
		msg_field = gm_GetMsgField(pkt, (char*) query_result);
		if (size - msg_field > requested) {
			return requested;
		}
		return size - msg_field;
	}
	record = (char*) g_item_def_table + item_id * 0x41;
	if (is_cat2) {
		is_producer = (*record == 0x17);
	} else {
		if (*record == 0x17 || *record == 0x25) {
			is_producer = 1;
		} else {
			is_producer = 0;
		}
	}
	if (*(unsigned short*) pkt == 0x2a) {
		count = 0;
		query_result = gm_ff_Objekt(*(int*) (pkt + 0x14), 1, 5);
		if (query_result != NULL) {
			do {
				q_id = *(unsigned short*) query_result;
				record = (char*) g_item_def_table + q_id * 0x41;
				if (is_cat2) {
					if (is_producer) {
						if (*record == 0x17) {
							count++;
						}
					} else {
						if (*record != 0x17) {
							count++;
						}
					}
				} else {
					if (is_producer) {
						if (*record == 0x17 || *record == 0x25) {
							count++;
						}
					} else {
						if (*record != 0x17 && *record != 0x25) {
							count++;
						}
					}
				}
				query_result = gm_NextEntityQueryMatch();
			} while (query_result != NULL);
		}
		if (is_producer) {
			if (count >= *(unsigned char*) (pkt + 0x1c)) {
				return 0;
			}
			goto limited;
		}
		if (count >= *(unsigned char*) (pkt + 0x1d)) {
			return 0;
		}
		goto limited;
	}
	count = 0;
	query_result = gm_ff_Objekt(*(int*) (pkt + 0x14), 1, 5);
	if (query_result != NULL) {
		do {
			count++;
			query_result = gm_NextEntityQueryMatch();
		} while (query_result != NULL);
	}
	if (count >= *(unsigned char*) (pkt + 0x1c)) {
		return 0;
	}
limited:
	return size < requested ? size : requested;
}

// FUNCTION: SERVER 0x10019ed0
// gm_CheckInventoryCapacity
/* Byte-exact.  The scan is a plain index loop over the zero-terminated
 * list: msvc6 folds the first `list[i] != 0` test (list[0] is the
 * constant 8), keeps 8 in eax as the loop-carried element and walks a
 * pointer from &list[0], which is the reference's `mov eax,8` /
 * `lea ecx,[esp+0x10]` head.  The entity byte is read twice through one
 * `entity` pointer (the 9 test and the scan compare); msvc6 CSEs both
 * into one `mov al,[eax]` kept in eax across the list stores.  Naming the
 * byte in a local instead spills it to [esp+0x38] (97 linked bytes).
 *
 * Two paths were read out of the binary rather than inferred: `count >= 6`
 * returns 0 (the `jge` at 0x1001a02d skips `mov ebp,3`), and the query,
 * used+requested and count paths share one clamp epilogue at 0x1001a03f,
 * so they all fall into `return ((cap < 0) - 1) & cap;`. */
int __cdecl gm_CheckInventoryCapacity(char* obj, int entity_index, int requested)
{
	int list[8];
	char* entity;
	int i;
	int in_list;
	int used;
	void* query_result;
	int count;
	int cap;

	in_list = 0;
	cap = 0;
	list[0] = 8;
	list[1] = 0xc;
	list[2] = 0x12;
	list[3] = 0x19;
	list[4] = 0x22;
	list[5] = 0x20;
	list[6] = 0x27;
	list[7] = 0;
	entity = (char*) g_item_def_table + entity_index * 0x41;
	if (*entity == 9) {
		return requested;
	}
	for (i = 0; list[i] != 0; i++) {
		if (list[i] == (unsigned char) *entity) {
			in_list = 1;
			break;
		}
	}
	if (obj[2] == 6 || obj[2] == 7) {
		if (ahm_LookupEntityInTable(entity_index) != 0) {
			return 0;
		}
	}
	if (entity_index == 0x179 || entity_index == 0x17a) {
		return 0;
	}
	if (in_list == 0) {
		return 0;
	}
	query_result = gm_ff_Objekt(*(int*) (obj + 0x178), 1, 0, entity_index);
	if (query_result != NULL) {
		ahm_LookupEntityInTable(entity_index);
		used = *(int*) ((char*) query_result + 0xe);
		if (used + requested > 3) {
			cap = 3 - used;
		} else {
			cap = requested;
		}
	} else {
		count = 0;
		query_result = gm_ff_Objekt(*(int*) (obj + 0x178), 1, 5);
		if (query_result != NULL) {
			do {
				if (*(char*) ((char*) g_item_def_table + *(unsigned short*) query_result * 0x41) != 9) {
					count++;
				}
				query_result = gm_NextEntityQueryMatch();
			} while (query_result != NULL);
		}
		if (count < 6) {
			if (requested > 3) {
				cap = 3;
			} else {
				cap = requested;
			}
		}
	}
	return ((cap < 0) - 1) & cap;
}

// FUNCTION: SERVER 0x1001A060
// gm_EntitySetField

void __cdecl gm_EntitySetField(void)
{
	int entity;
	int sub;
	entity = (int) gm_StartFilteredEntitySearch(1, 0, 0x1e);
	if (!entity) {
		return;
	}
	do {
		sub = (int) gm_ff_Objekt(*(int*) (entity + 0x5d), 1, 0, 0xff);
		if (sub) {
			sub = (int) gm_ff_Objekt(*(int*) (sub + 0x14), 1, 5);
			if (sub) {
				do {
					if (*(int*) (sub + 0xe) != 2) {
						*(int*) (sub + 0xe) = 2;
					}
				} while ((sub = (int) gm_NextEntityQueryMatch()) != 0);
			}
		}
		entity = (int) gm_FindNextFilteredEntity();
	} while (entity);
}

/* Returns a random integer in [0, max). Uses the game's
 * internal random number generator for deterministic
 * simulation results. */

// FUNCTION: SERVER 0x1001A0D0
// gm_RandomMod

int __cdecl gm_RandomMod(unsigned short n)
{
	if (n) {
		return rand() % n;
	}
	return 0;
}

/* Returns a random float in [0.0, 1.0). Converts the
 * integer RNG output to a normalized float value. */

/* Returns a random value with quadratic distribution.
 * Produces values biased toward lower numbers. Used for
 * stat rolls and probability curves. */
