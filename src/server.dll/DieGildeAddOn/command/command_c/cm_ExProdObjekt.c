// FUNCTION: SERVER 0x1000e140

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 993B
 *    CFlags:
 *    Symbol: _cm_ExecProduction
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExProdObjekt(int msg,char *result)
 *
 * NOTE (2026-09-06): `*(msg+0x1a)` uses g_next_object_id (0x10030b6c) per the
 * worktree command_internal.h rename (g_timestamp_0b6c). Same address, no
 * codegen change. With worktree headers the file is NEAR_MATCHING 636/993;
 * the 964/993 baseline in this comment predates the header rename.
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char* g_unknown_1de450;
extern unsigned char g_current_season;

short* __cdecl gm_ResolveParentEntity(short*);
double __cdecl gm_CalculateProductionValue(uint, int);
int __cdecl gm_EntityAccumulate(void*);

extern char s_cm_ExecProduction___Invalid__lager_1002cf9c[];
extern char s_cm_ExecProduction___Lager_has_wron_1002cf74[];
extern char s_cm_ExecProduction___Lager_hat_kein_1002cf48[];
extern char s_cm_ExProdObjekt___Cannot_produce___1002cf1c[];
extern char s_cm_ExProdObjekt___Rohstoff_versc_1002cef4[];
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

/* Execution handler: produces an object. Processes a production
 * message with entity lookup, object allocation/deallocation,
 * and inventory management for crafted goods.
 *
 * Conversion state: pure C (naked wrapper removed).  The frame and the
 * gm_GetFieldByType/gm_ResolveEntityById calls match byte-for-byte.  The
 * three early-error LogMessageInternal epilogues are kept as separate
 * `return 1` blocks so MSVC6 does not tail-merge them (matching the
 * target, which inlines all three); the two later errors ("Nicht genug
 * Rohstoffe" / "Rohstoff verschwunden") are separate blocks whose
 * identical tails MSVC6 cross-jumps exactly like the target (error4
 * pushes 1/str/line and jumps into error5's push-file).  Compiled with
 * /Ox (the target's optimization level; /O2 enables /Og which makes
 * MSVC6 tail-merge the early errors).  The target's pre-loop dead store
 * `mov [esp+0x18],ebx` (saved_quantity = quantity, overwritten by the
 * loop counter `4`) is reproduced with VOLATILE writes of both dead
 * values — MSVC6 eliminates every non-volatile formulation tried, and
 * making only the first store volatile leaves the function 5 bytes
 * short (the second-loop recipe_def reload and the `mov cl` season
 * load only fall out of the full /Ox register allocation once both
 * stores are volatile).  With both volatile the function is
 * NEAR_MATCHING 993/993 (636 bytes, was 437).  Remaining divergence is
 * pure scheduling/order in the pre-loop dead-store block (the volatile
 * `= 4` materializes as `mov ecx,4; mov [esp+0x18],ecx` plus a
 * duplicate loop-counter store instead of the target's single immediate
 * `mov [esp+0x18],4`) plus the register-allocation knock-ons of that
 * block (second-loop `add edi,0x2e` vs target reload, `mov al` vs
 * `mov cl` season load).
 *
 * 2026-09-06, this session, 636 -> 457 (SIZE_MISMATCH, obj 986): three
 * structural fixes, each verified by objdump ground truth, not scores.
 * (1) The first loop really calls gm_GetMsgField TWICE per iteration: the
 * target computes the min-compare quotient with one call/divide pair, then
 * recomputes it with a second call/divide pair before storing.  The old
 * single-call body emitted `mov quantity,eax` where the target reloads and
 * re-divides (72 target bytes matched once the second call was written).
 * (2) The production-cap compare reads `quantity >= production_cap`
 * (cmp ebx,eax + jl), not the equivalent `production_cap <= quantity`.
 * (3) The second loop is do/while (`production_cap = 0` above the head,
 * counter increment in the tail), which reproduces the target's
 * `lea edi,[edx+0x2e]` head.  Dead ends on this form: moving the reloads
 * below the gm_KannObjektHergestellt call (406), hoisting the call amount
 * (411) or the message type (426, closest) into locals, swapping the two
 * post-loop reloads, swapping the loop-tail statements (994 bytes), an
 * if/else cap clamp (455), inverting the lager 0x2a guard, splitting the
 * alloc-failure null check, and hoisting AllocObjekt args with a
 * block-scope local (456).  A volatile-int loop counter reproduces the
 * target's memory-form counter (`mov [esp+0x18],4`,
 * `mov eax,[esp+0x18]`, `dec`, `mov [esp+0x18],eax`, matching the whole
 * first loop body through the back edge) but shifts post-loop register
 * roles and costs 5 bytes elsewhere (367-423); a plain-int counter with
 * the volatile access casts keeps the counter death but matches the tail
 * (`dec eax` in eax, 437).  Residual: pre-loop store interleave (target
 * interleaves `mov [esp+0x18],ebx` between the index computation and
 * `mov [esp+0x18],4` immediate; ours materializes `= 4` through ecx with
 * a duplicate counter store) plus one store-source register
 * (`mov [esp+0x18],eax` vs ebx) and the second-loop reload/register
 * roles.  STATUS: PROVEN retained; not a byte match.
 *
 * 2026-09-08 pass (457/993, obj 986, nothing kept).  The literal-vs-symbol
 * address lever that moved the three sibling Ex handlers this session does
 * not apply here: every global this function touches already goes through a
 * declared symbol, and all nine data relocations in the diff are clean, so
 * there is no unfolded address to recover.
 *
 * The pre-loop dead-store interleave is confirmed not steerable.  The target
 * interleaves `mov [esp+0x18],ebx` between the index math and the `= 4`
 * immediate; every ordering of those three statements was measured and none
 * reproduces it: the dead store first 454, quantity loaded before the dead
 * store 442, recipe_def computed between them 454, a volatile `= 4` store
 * 268.  The loop-2 tail statement swap is inert at 457 (msvc6 reschedules
 * it), and the `jl` back edge the target uses where we emit `jge` plus a
 * long `jmp` is the out-of-line layout pass described in
 * msvc6-c-shapes.md section 17, not a source-level choice.
 *
 * 2026-09-08 pass 2 (457/993, nothing kept).  The scan-shape lever that moved
 * cm_ExCopyEntityData 49 points does not apply: both loops here are already
 * do/while, matching the reference.  Re-probed on this body and inert or
 * worse: the loop-2 tail increments swapped so the counter bumps before the
 * pointer (457), recipe_def computed after the volatile counter store (454),
 * a volatile `saved_quantity` store to force the reference's `mov
 * [esp+0x18],ebx` from the already-assigned quantity rather than eax (457).
 * near-diag reads 69.0% match / 20.2% structural / 0.4% register, so the
 * positional score understates it: the body is close and the deficit is the
 * two layout-pass items above.
 *
 * The `// CFLAGS:` header is not consumed by the build; cflags come from
 * rebrew-functions.toml.  Header values from /Od to /Ox all produce the
 * identical object, so a flag sweep spelled in the source is a no-op.
 *
 * 2026-09-08 pass 3 (457/993 -> 964/993, obj 986 -> exactly 993).  The
 * material-consumption loop rewritten from `do { } while (production_cap < 4)`
 * to a top-tested `for (; production_cap < 4; production_cap++,
 * material_iter++)`.  The bottom-tested form put the loop body out of range of
 * a short back edge, so msvc6 emitted `jge exit` plus a long `jmp` back; the
 * top-tested form restores the reference's single `jl` back edge at
 * 0x1000e390 and re-aligns everything downstream.  Both increments move into
 * the for-header, which also gives the reference's `inc ebp` before
 * `add edi,2`.
 *
 * 2026-09-08 pass 4 (964/993 -> 974/993, obj stays exactly 993).  The pre-loop
 * dead-store interleave closed by splitting the recipe_def address into
 * `recipe_idx` and `recipe_shift` temps: the index load and the `<< 6` shift
 * sit above the dead store, the `+ recipe_idx` fold below it.  That reproduces
 * the reference's `mov ecx,eax` / `mov [esp+0x18],ebx` / `shl ecx,6` /
 * `add edx,ecx` / `mov [esp+0x18],4` / `add eax,edx` schedule, where the
 * one-expression `* 0x41` form emitted the whole multiply first and deferred
 * the ebx store.  Mnemonic match is now 100%.
 *
 * Residual: 14 bytes at 205-218 plus two at 223-224 (the g_unknown_1de450 load
 * ordered after the ebx dead store rather than before it) and one byte at 410
 * (`mov [esp+0x18],eax` where the reference re-reads ebx).  The load order is
 * not reachable from C: the dead store goes through a cast volatile pointer,
 * which msvc6 treats as aliasing every global, so the global load is pinned
 * below it.  Measured and reverted on the 974 body: all 24 orderings of the
 * recipe / dead-store / quantity / counter statements (931-964); the global
 * cached in a temp at four positions (974, inert) and read through a volatile
 * pointer (961-973); loop_count declared volatile so the store is a known
 * local access rather than a cast (942-949); the barrier moved onto
 * saved_quantity, which owns the same slot (974, inert); a volatile LOAD from
 * the message in place of the volatile store (269, the loop counter stops
 * being register-allocated); the whole address computed above the store (964).
 * Byte 410 does not move from the clamp block: chained assignment, sourcing
 * production_cap, a volatile store, and the inverted compare all measure
 * 969-974 without changing that operand.
 *
 * Same pass, 974 -> 976: the call at 0x1000e4a9 was declared and called as
 * gm_WalkEntityChain, which lives at 0x10019be0.  The reference calls
 * gm_EntityAccumulate at 0x10019b80, so the emitted displacement pointed at
 * the wrong function and bytes 874-877 never resolved.  All thirteen callees
 * now match db/server.dll_functions.csv.
 *
 * 2026-09-08 pass 5 (976/993, nothing kept).  About fifty further variants of
 * the pre-loop block and the clamp block were measured; every size-exact form
 * lands on exactly 976 with the identical mismatch set (205-218, 223-224,
 * 410), so the plateau is a compiler-level property of this block, not a
 * statement order that has not been tried yet.  The dead store is real: with
 * any non-volatile spelling msvc6 eliminates `mov [esp+0x18],ebx` and the
 * object drops to 989 bytes.  Also measured and reverted: the address of
 * loop_count taken into a plain `int*` and stored through it (989, still
 * eliminated, so DSE here does not respond to address exposure, only to
 * volatile); a `volatile int*` pointer variable, a declared `volatile int`
 * local, `volatile uint`, `volatile long`, and a two-step store then volatile
 * self-write, all 976 and byte-identical to the cast form; four declaration
 * orders of loop_count / saved_quantity / recipe_shift / recipe_idx (976,
 * inert); the loop-1 tail statements swapped, `--` decrement, and a top-tested
 * while form (976, msvc6 reschedules the tail either way); recipe_idx typed
 * int, recipe_shift typed uint, and the zero-extend spelled `& 0xffff` (976,
 * 976, 275).
 *
 * The volatile global read (`*(char* volatile*)&g_unknown_1de450`) does move
 * the load to the reference's first position, which is the only lever found
 * that touches byte 205 at all, but it swaps the ecx/edx roles of the shift
 * and fold and nets 963.  Ten spellings of the fold under that read (shift on
 * either side, `* 0x40` instead of `<< 6`, accumulate-in-place, separate int
 * and uint temps, idx copied to a second local) all stay at 963, so the
 * register swap is not reachable from the expression shape.  Hoisting the
 * global read into the earlier blocks is worse (898-929).
 *
 * Byte 410 (the clamp store sourcing eax where the reference re-reads ebx)
 * survived nine more clamp spellings: assignment order swapped, chained
 * assignment, both sides from production_cap, a ternary min, an unconditional
 * store after the if (999 bytes), a read-back through the slot (995), and a
 * volatile store into the loop_count slot (997).  Every size-exact one is 976
 * with byte 410 unchanged.
 *
 * CFLAGS are inert at this plateau: /Ox, /O2, /Gy, /Ob1, /Gs, /Oxy, /G3, /G4,
 * /G5, /GX-, /Zp1, and /Zp4 all produce the identical 976/993 object; /O1
 * (795), /G6 (995), /Oy- (969), and /Op (1001) all break the size.
 *
 * 2026-09-08 pass 6 (976/993, nothing kept).  A dependency-ordered sweep of
 * the pre-loop block enumerated all 112 topological orderings of the seven
 * statements (global load, index read, quantity read, dead store, shift,
 * counter init, address fold) with the load split into its own statement.
 * Every ordering is size-exact and none beats 976; the best reach 946, so
 * the plateau is not a statement permutation that was missed.
 *
 * Two structural alternatives were measured and are dead ends, both because
 * of the frame layout rather than the schedule.  Dropping saved_quantity and
 * feeding the fimul from quantity directly grows the object to 999: the two
 * variables are not redundant to msvc6 because the x87 operand needs its own
 * memory home (section 8a).  Merging the loop counter and saved_quantity into
 * one variable, which is what the reference's slot sharing looks like, holds
 * the object at 993 but widens the frame to `sub esp,0x14` and moves every
 * esp displacement, scoring 815.
 *
 * The section 14 lever (plain store, volatile READ at the consumer) does not
 * transfer: the read forces a reload before the fimul and the object grows to
 * 999, or 1003 when paired with the existing volatile store.  Declaring
 * loop_count volatile rather than casting is 945, and the section 24 pair
 * (volatile global read plus volatile dead store) redistributes the mismatch
 * set (byte 205 alone, 206-209 clean, ecx/edx roles swapped on the fold) at
 * 963-975 without reducing it.
 *
 * DSE here responds only to volatile, not to address exposure: storing
 * through `(char*)&loop_count + (msg & 0)`, an opaque byte-offset the
 * optimizer cannot fold away, is still eliminated at 989 bytes, and a
 * runtime-selected `int*` between the two slots grows the frame to 1009.
 *
 * Byte 410 took four further clamp forms not previously tried: production_cap
 * kept live past the join, a self-referencing add on the stored value, a
 * compound `quantity -= quantity - production_cap`, and the clamp store made
 * volatile.  All four are 976 with byte 410 byte-identical, which puts it at
 * the allocator level rather than in the expression shape.
 *
 * 2026-09-08 pass 7 (976/993, PROVEN).  The service-pack axis is exhausted:
 * msvc600sp6 produces the identical 976/993 object, and sp1 through sp5 cannot
 * build this file at all (their images carry no windows.h, C1083 out of
 * game_common.h).  The section 8c volatile-read lever was the last untried
 * ordering primitive and both spellings break the size, at 1018 and 996.
 *
 * Both residual clusters need one thing MSVC6 does not offer: a store that
 * survives dead-store elimination without also acting as a global-alias
 * barrier.  The dead store only survives when it is volatile, and a volatile
 * store orders the g_unknown_1de450 load below it, which is exactly the
 * 205-218 / 223-224 delta.  Computing the whole address above the barrier
 * clears those fourteen bytes but sinks the store past the
 * `lea edi,[eax+0x26]` for a net 966, so the two clusters are coupled and
 * neither closes alone.
 *
 * `rebrew prove` verifies the function symbolically equivalent on EAX over
 * four original and four compiled states, so the status is PROVEN rather than
 * a byte match. */


// CFLAGS: /Ox /Gd
int __cdecl cm_ExProdObjekt(int msg, char* result)
{
	int quantity;
	int loop_count;
	ushort* obj_entry;
	char* recipe;
	int production_cap;
	ushort* material_iter;
	long production_value;
	short* player_entry;
	short* lager;
	char* recipe_def;
	short* owner;
	int saved_quantity;
	char* recipe_shift;
	uint recipe_idx;

	*(int*)(msg + 0x1a) = g_next_object_id;
	quantity = gm_GetFieldByType((char*)msg, *(int*)(msg + 0x10));
	*(int*)(msg + 0x10) = quantity;
	quantity = gm_ResolveEntityById((void**)0, (void**)&lager, (void**)0, quantity);
	if (quantity == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x2f3b,
			"cm_ExProdObjekt() Invalid 'lager_id'",
			1
		);
		return 1;
	}
	if ((*lager != 0x2a) && (*lager != 0x116)) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x2f53,
			"cm_ExProdObjekt() Lager has wrong Type",
			1
		);
		return 1;
	}
	owner = gm_ResolveParentEntity(lager);
	if (owner == (short*)0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x2f6d,
			"cm_ExProdObjekt() Lager hat keinen Besitzer",
			1
		);
		return 1;
	}
	recipe_idx = (uint)*(ushort*)(msg + 0x14);
	*(volatile int*)&loop_count = *(int*)(msg + 0x16);
	recipe_shift = g_unknown_1de450 + (recipe_idx << 6);
	loop_count = 4;
	recipe_def = recipe_shift + recipe_idx;
	material_iter = (ushort*)(recipe_def + 0x26);
	quantity = *(int*)(msg + 0x16);
	do {
		if (material_iter[4] != 0) {
			obj_entry = (ushort*)gm_StartEntityQuery(*(int*)(lager + 10), 1, 0, (uint)material_iter[4]);
			if (obj_entry != (ushort*)0) {
				recipe = (char*)gm_GetMsgField((int)lager, (int)obj_entry);
				if (quantity >= (int)recipe / (int)(uint)*material_iter) {
					recipe = (char*)gm_GetMsgField((int)lager, (int)obj_entry);
					quantity = (int)recipe / (int)(uint)*material_iter;
				}
			}
			else {
				quantity = 0;
			}
		}
		material_iter = material_iter + 1;
		loop_count = loop_count + -1;
	} while (loop_count != 0);
	recipe = recipe_def;
	saved_quantity = quantity;
	production_cap = gm_KannObjektHergestellt(
		(char*)lager,
		(uint)*(ushort*)(msg + 0x14),
		(uint)*(ushort*)(recipe_def + 0x36) * quantity
	);
	production_cap = production_cap / (int)(uint)*(ushort*)(recipe + 0x36);
	if (quantity >= production_cap) {
		quantity = production_cap;
		saved_quantity = quantity;
	}
	if (quantity == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x2fb5,
			"cm_ExProdObjekt(): Nicht gen\374gend Rohstoffe",
			1
		);
		if (result != (char*)0) {
			result[1] = '\b';
		}
		return 1;
	}
	production_cap = 0;
	material_iter = (ushort*)(recipe_def + 0x2e);
	for (; production_cap < 4; production_cap++, material_iter++) {
		if (*material_iter != 0) {
			obj_entry = (ushort*)gm_StartEntityQuery(*(int*)(lager + 10), 1, 0, (uint)*material_iter);
			if (obj_entry == (ushort*)0) {
				LogMessageInternal(
					s_D__Develop_DieGildeAddOn_command_1002c748,
					0x2fdd,
					"cm_ExProdObjekt() Rohstoff verschwunden",
					1
				);
				if (result != (char*)0) {
					result[1] = '\b';
				}
				return 1;
			}
			*(uint*)(obj_entry + 7) = *(int*)(obj_entry + 7) - (uint)material_iter[-4] * quantity;
			recipe = gm_FindSlotById((uint)g_current_season, (uint)*material_iter);
			if (recipe != (char*)0) {
				*(uint*)(recipe + 0x14) = *(int*)(recipe + 0x14) + (uint)*(ushort*)(recipe_def + 0x36) * quantity;
			}
			if (*(int*)(obj_entry + 7) == 0) {
				gm_RemoveObjectByType((char**)(lager + 10), (uint)*material_iter);
			}
		}
	}
	material_iter = (ushort*)gm_StartEntityQuery(*(int*)(lager + 10), 1, 0, (uint)*(ushort*)(msg + 0x14));
	recipe = recipe_def;
	if (material_iter != (ushort*)0) {
		*(uint*)(material_iter + 7) = *(int*)(material_iter + 7) + (uint)*(ushort*)(recipe_def + 0x36) * quantity;
	}
	else {
		material_iter = (ushort*)gm_AllocObjekt(
			*(int*)(lager + 1),
			(uint)*(ushort*)(msg + 0x14),
			(uint)*(ushort*)(recipe_def + 0x36) * quantity
		);
		if (material_iter == (ushort*)0) {
			if (result != (char*)0) {
				result[1] = '\x06';
			}
			return 1;
		}
		if (*lager == 0x2a) {
			*(int*)(material_iter + 7) = *(int*)(material_iter + 7) + 1;
		}
		if (((*recipe == '\x17') || (*recipe == '%')) &&
			((*lager == 0x2a || (*lager == 0x116))) &&
			(((char)owner[1] == '\x06' || ((char)owner[1] == '\a')))) {
			*(int*)(material_iter + 0xe) = 4;
		}
	}
	production_value = (long)(gm_CalculateProductionValue((uint)*(ushort*)(msg + 0x14), 100) * saved_quantity);
	production_cap = gm_EntityAccumulate(lager);
	if (production_cap != 0) {
		*(int*)(production_cap + 0x4d) = *(int*)(production_cap + 0x4d) + (int)production_value;
	}
	recipe = gm_FindSlotById((uint)g_current_season, (uint)*(ushort*)(msg + 0x14));
	if (recipe != (char*)0) {
		*(uint*)(recipe + 0x10) = *(int*)(recipe + 0x10) + (uint)*(ushort*)(recipe_def + 0x36) * quantity;
	}
	player_entry = gm_GetEntityTableEntry((char*)owner);
	if (player_entry != (short*)0) {
		*(int*)(player_entry + 0x12) = *(int*)(player_entry + 0x12) + (int)production_value;
	}
	if ((result != (char*)0) && ((*result = '\x01', *(int*)(msg + 0x10) != -1))) {
		result[1] = '\x03';
		*(ushort**)(result + 6) = material_iter;
	}
	return 0;
}
