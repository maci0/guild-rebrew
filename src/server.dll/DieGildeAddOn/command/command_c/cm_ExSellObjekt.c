// FUNCTION: SERVER 0x1000d930

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern unsigned int g_entity_slot_table[];
extern char* g_unknown_1de450;
extern unsigned char g_current_season;

extern PlayerSlot g_player_slots_base[8];
extern char g_error_msg_sell_no_source[];
extern char g_error_msg_sell_no_dest[];
extern char g_error_msg_sell_failed[];

short* __cdecl gm_ResolveParentEntity(short*);
int __cdecl compute_size(char*, int);
int __cdecl gm_RemoveObjectWrapper(int, uint);
void* __cdecl gm_AddObjekt(int, uint, int);
void* __cdecl gm_AllocRaum(char*, uint);
int __cdecl sprintf(char*, const char*, ...);

extern char s_cm_ExSellObjekt___Invalid__quell_1002cec4[];
extern char s_cm_ExSellObjekt___Invalid__gm_ev_1002ce90[];
extern char s_cm_ExSellObjekt____Object_not_fo_1002ce4c[];
extern char s_cm_ExSellObjekt___Not_enough_Obj_1002cdfc[];
extern char s_cm_ExSellObjekt___Invalid__ziel__1002cdcc[];
extern char s_cm_ExSellObjekt___Lager_voll_1002cdac[];
extern char s_cm_ExSellObjekt___Not_enough_Cre_1002cd78[];
extern char s_cm_ExSellObjekt____gm_AllocRaum_f_1002ccc0[];
extern char s_cm_ExSellObjekt____gm_AllocObjek_1002cce8[];
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

/* Execution handler: sells an object (Objekt) from one entity
 * to another. Handles object type validation, inventory transfers,
 * production slot updates, and building ownership changes.
 *
 * Error handling uses the reference's inline-call shape: each failure
 * site calls LogMessageInternal(...) and returns 1, and MSVC6 /O2
 * tail-merges the identical call+return into the target's shared call
 * tail (stack-pushed args at each site + one shared call/epilogue).
 * The earlier goto-through-capacity_check/error_code formulation
 * compiled to register-passed args at a single push site and matched
 * only 229 bytes.
 *
 * Conversion state: pure C (naked wrapper removed).  The frame matches the
 * reference exactly as of 2026-09-13.  CORRECTION 2026-09-13 (object-level
 * probe + full-diff check): the head zero hunk described here is CLOSED —
 * both sides emit `xor edi,edi`, the nine edi zero-stores (indices 13-21)
 * and `cmp eax,edi` at index 43.  The live divergence is the downstream
 * spill-slot permutation ([esp+0x18]<->[esp+0x14],
 * [esp+0x20]<->[esp+0x24], index 29) cascading from the dest-call
 * out-param reuse, plus scheduling drift from index 222 on.  Two further
 * zero-spelling probes (struct-member init: 127/2057, desync; short-pointer
 * init: byte-identical, no effect) confirm the zero itself is not the
 * lever.  Best-effort 613/2057 matched (861 matched-reloc), obj 2064
 * (docs/msvc6-allocator.md GRA class) — the 392 figure quoted here
 * previously predated the frame fix; current probe 2026-09-13 — but read
 * them as slot-permutation + schedule, not zero-register.
 *
 * Frame layout, fixed 2026-09-13: the reference's 0x228 frame carries a
 * 4-byte hole between the spill block and the 512-byte log buffer.  It is
 * not an alignment pad (MSVC6 packs stack objects on 4 bytes; char[512],
 * __int64[64], double[64] and a struct-of-__int64 array all give the same
 * frame) and not a plain unused local (eliminated outright).  Modelling the
 * buffer as the 516-byte `struct SLogBuffer` below allocates the whole
 * aggregate, so its first dword stays reserved and untouched while `text`
 * lands on 0x38 -- reproducing `sub esp,0x228`, the [esp+0x38] buffer base
 * and the [esp+0x238] param slot byte for byte.  See docs/TODO.md round 86.
 *
 * Rechecked 2026-08-27: the call inventory matches the reference
 * 1:1 (error-path restructure did not add or drop a call), so the
 * residual delta is pure codegen (no missing block).  Variants tried
 * and rejected: g_current_season int, unused pad locals (eliminated),
 * declaration reordering (verified: byte-identical), local merges
 * (container_ptr/source_container_ptr/linked_list_ptr), entity_type /
 * obj_category as int, dest-call out-param order swap (203B),
 * /O1 (ebp frame), /Ox (larger, different global allocation), /O2 /G5
 * /G6 /Oy- (no change).  No flag or formulation shifts the zero-store
 * register off ebx to the reference's edi; /O2 /Gd stays the best
 * committed state.
 *
 * The dest-resolution call passes its out-params in the reference's
 * register order: gm_ResolveEntityById(&dest_existing_entity,
 * &resolved_dynamic, &source_static_entity, ...).  The reference reuses the
 * SOURCE's resolved_dynamic slot for the dest call's second out-param, so
 * the dest block's second branch re-checks the DEST's dynamic entity (the
 * dest call overwrites the source's value) — the earlier formulation passed
 * (&dest_dynamic_entity, &dest_existing_entity, ...), which left the source's
 * resolved_dynamic untouched and made branch 2 test the wrong entity (real
 * semantic bug; the old code failed symbolic proving with EAX=1 vs 0).
 *
 * Deduction 2026-09-13: the spill-slot permutation is NOT downstream of
 * this reuse — the reference reuses the same slot and still gets its own
 * permutation.  The permutation comes from the global slot assignment
 * (other locals' homes), which eleven initializer rotations left
 * byte-identical.  Do not chase the permutation through the out-params.
 *
 * Byte-level: still SIZE_MISMATCH (obj 2059 vs target 2057 — the "2055"
 * figure here predated the weight_fraction fix; span-neutral at COMDAT
 * 2064) — the residual
 * deltas are the register-role/slot cascade (the frame itself now
 * matches; see above) and whatever case-block order remains after the
 * season-block move below.
 *
 * CORRECTED round 179: this paragraph used to blame a "tail-merge shape
 * (candidate inlines the two error tails; reference shares one tail at
 * 0x1000e00e)".  That is misleading and sent readers down a dead end.
 * The reference has FIVE `add esp,0x228; ret` epilogues (0x1000daa9,
 * 0x1000db06, 0x1000db56, 0x1000e024, 0x1000e10a) and our build has the
 * same five; the eight `jmp 0x1000e00e` sites are shared by both.  The
 * tail-merge shape already matches -- it is not part of the residual.
 *
 * Round-179 census of the residual, for whoever picks this up:
 * only ~43% of it is real codegen.  Of ~1,221 fixed-offset differing
 * bytes, ~525 sit inside instruction hunks; ~644 (53%) are
 * byte-identical instructions at the wrong address.  ALL of that
 * displacement traces to ONE cliff: the offset delta runs 0..+8 for the
 * first 0x5d0 bytes, then jumps to -147 at 0x1000dfc1 and stays there.
 * The cause is a single block-placement decision -- the reference runs
 * the slot-table update + gm_SubObjekt body inline at 0x1000df2a
 * (verified: `xor ecx,ecx; mov cl,[esi+3];` ... `mov [eax*4+0x10442d08],ecx`)
 * while ours jumps away and emits it ~147 bytes later at 0x1000e0cc.
 * Moving that body up is the highest-value untried lever here.  The
 * remaining clusters (the nine-slot zero-store permutation at
 * 0x1000d959 and the ~30 register/slot-name pairs) are measured walls.
 *
 * CORRECTED round 182: this paragraph used to call [esp+0x44] a "dead
 * spill the reference materialises at 0x1000dd1f".  Both halves are
 * wrong.  The reference WRITES it at 0x1000dd2a and READS IT BACK at
 * 0x1000dd33, across the intervening call -- a live cross-call spill.
 * And we already occupy the same physical slot: tracking esp depth
 * through the pushes, the reference's [esp+0x44] and our [esp+0x3c] are
 * both frame+0x468.  The actual difference is that the reference
 * computes the imul/shr AFTER `push ebx` and interleaves the spill
 * between `push ebx` and `push edi`, while we compute it all before the
 * pushes: an instruction-scheduling difference around a call setup, not
 * a spill-materialisation one.  Aiming at "eliminate a store" instead of
 * "push interleaving" is how two earlier rounds were burned.
 *
 * ALSO SUPERSEDED: the round-179 census paragraph above still asserts in
 * the present tense that all displacement traces to one cliff and that
 * moving that body up is the highest-value untried lever.  That lever
 * was spent by the round-180 win.  Re-censused round 182: no second
 * cliff exists.  The §86 screen fails at both steps -- the delta returns
 * to zero five times and finishes at -1 (45 constant-delta runs across
 * 557 aligned pairs, none holding to the end), and the jmp census is
 * 22 against 22 with no built-only surplus (the one discrepancy at
 * 0x1000dc16/dc20 is a swap: we jump to the store, the reference falls
 * into it).  The residual is now 71.5% byte-identical instructions at
 * the wrong address with NO dominant source -- four independent 1-4
 * byte accumulations, the largest worth 163B -- and every cluster >=48B
 * is register allocation or intra-block scheduling with no shapes-doc
 * lever.  This function is retired for shape work.
 *
 * 2026-09-13 (round 93): the dest-season `if (*(cmd+0x23))` block (both
 * FindSlotById arms) moved above `dest_object = dest_game_object`, ahead
 * of source-finalize — the reference runs the season loops (FindSlotById
 * at 0x1000ddc8/df9) before source-finalize (0x1000de10+), and ours ran
 * them after.  Object 613/861 → 684/910, linked 1404 → 1346 (-58, plus
 * -2 outside = -60 total).  Kept: same reads, the moved block touches
 * none of source-finalize's inputs, and the order now matches the
 * reference's own execution sequence.
 *
 * 2026-09-13 (round 121): source-block category guard tests '\x06'
 * first (`'\x06' || '\x02'`; dest-side twin keeps '\x02'-first) —
 * object +1/+1 both rulers, linked 1346 -> 1345 (-1, confirmed after
 * full rebuild).  Kept for the byte.
 *
 * 2026-09-14 (round 173): `dest_object = dest_game_object` moved from
 * top level INTO the `cmd+0x10` dest-finalize block, as its first
 * statement.  The reference defers that load to 0x1000df0a, inside the
 * guard; source-finalize at 0x1000de10 runs entirely on the source
 * object.  Hoisting it above source-finalize put that whole region on
 * the dest pointer's slot and drifted the schedule to the function's
 * end.  Object 685/911 -> 829/1047, rebrew test 796 -> 971, linked
 * 1345 -> 1172 (-173, confirmed after a full clean rebuild).  Largest
 * win on this function after the season move.  Note the object SHRANK
 * (2053 -> 2025, span 2064 -> 2032): a real body below the reference
 * span is legal (allocator Finding 58) and the link is what ranked it.
 * Placement is load-bearing: the same assignment written at top level
 * immediately BEFORE the `if` scores 92/2057 — msvc6 sinks the load
 * into the taken arm only when it is written inside the guard.
 *
 * 2026-09-14 (round 179): the `gm_AllocRaum` null check is written
 * success-first (`!= 0` with the error in the `else`) rather than
 * error-first.  The reference lays its three error tails out in REVERSE
 * source order -- 0x2e5d at 0x1000e009, 0x2e39 at 0x1000e0c2, 0x2e45 at
 * 0x1000e12f past the ret -- and the error-first spelling put 0x2e45
 * ahead of 0x2e39.  This form reproduces the reference order exactly:
 * object 829/1047 -> 836/1052, rebrew test 971 -> 977, span-neutral,
 * linked 1172 -> 1167 (-5, confirmed after a full clean rebuild).
 * Semantics are unchanged -- same two branches, inverted test.
 * Note `if (cond) goto L;` normalises back to the same object (shapes
 * §59), so only real block restructuring moves this class.
 *
 * 2026-09-14 (round 180): the post-join `dest_dynamic_entity` test is a
 * VOLATILE reload (see the comment at the site).  This killed the -147
 * placement cliff that the round-179 census named as the function's
 * highest-value lever: object 836/1052 -> 1037/1217 with the instruction
 * count landing on the reference's 667 exactly and the COMDAT span on
 * 2064 exactly, rebrew test 977 -> 1149, linked 1167 -> 967 (-200,
 * confirmed after a full clean rebuild).  Semantics unchanged: reading a
 * local through a volatile-qualified pointer to its own address yields
 * the same value and only forbids enregistration.
 *
 * Semantically PROVEN equivalent (Z3, EAX) as of 2026-08-29.
 * The round-173 move preserves that: `dest_object` is read only inside
 * the same `cmd+0x10` guard, so the assignment cannot be observed
 * before its new position. */



// SIZE 0x204
struct SLogBuffer { uint weight_fraction; char text[512]; };

uint cm_ExSellObjekt(char* cmd, uchar* result)
{
	int amount;
	int resolve_result;
	char* capacity_check;
	short* parent_check;
	ushort* dest_object;
	short* source_owner_entity;
	int* linked_list_ptr;
	short* source_dynamic_ref;
	short* dest_owner_entity;
	short* resolved_dynamic;
	short* source_dynamic_entity;
	char* dest_existing_entity;
	short* dest_dynamic_entity;
	short* source_static_entity;
	char** source_container_ptr;
	ushort* dest_game_object;
	void* source_existing_entity;
	/* The reference's frame is 0x228, 4 bytes more than a bare
	 * `char log_buffer[512]` gives (0x224), and the extra dword sits
	 * between the spill block and the buffer: the reference's
	 * `lea ecx,[esp+0x38]` addresses the buffer where a plain array
	 * yields 0x34, and no instruction anywhere in 0x1000d930 touches
	 * [esp+0x34].  MSVC6 packs stack locals on 4 bytes with no
	 * alignment pad (measured: char[512], __int64[64], double[64] and
	 * a struct-of-__int64 array all give the same frame), and a plain
	 * unused local is eliminated outright, so the hole is an aggregate
	 * with a leading member the reference never reads -- modelling the
	 * buffer as a 516-byte struct reproduces both the frame and the
	 * buffer base exactly. */
	struct SLogBuffer log_buffer;
	short entity_type;
	char obj_category;

	source_owner_entity = (short*)0;
	*(int*)(cmd + 0x1a) = g_next_object_id;
	dest_owner_entity = (short*)0;
	source_dynamic_entity = (short*)0;
	dest_game_object = (ushort*)0;
	resolved_dynamic = (short*)0;
	dest_object = (ushort*)0;
	dest_existing_entity = (char*)0;
	source_container_ptr = (char**)0;
	source_existing_entity = (void*)0;
	dest_dynamic_entity = (short*)0;
	source_static_entity = (short*)0;
	if (*(int*)(cmd + 0x14) != -1) {
		resolve_result = gm_GetFieldByType(cmd, *(int*)(cmd + 0x14));
		*(int*)(cmd + 0x14) = resolve_result;
		resolve_result = gm_ResolveEntityById(
			&source_existing_entity,
			(void**)&resolved_dynamic,
			(void**)&source_static_entity,
			resolve_result
		);
		if (resolve_result == 0) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c05, "cm_ExSellObjekt() Invalid 'quell_besitzer_id'", 8);
			return 1;
		}
		if (source_existing_entity != (void*)0) {
			source_container_ptr = (char**)((int)source_existing_entity + 0x5d);
			if (*(ushort*)((int)source_existing_entity + 0x27) != 0xffff) {
				source_owner_entity = (short*)(g_slot_table +
					(uint)*(ushort*)((int)source_existing_entity + 0x27) * 0x21c);
			} else {
				source_owner_entity = (short*)0;
			}
		} else if (resolved_dynamic != (short*)0) {
			entity_type = *resolved_dynamic;
			if (entity_type == 0x2a || entity_type == 0x1db ||
				entity_type == 0x1dc || entity_type == 0x116 ||
				entity_type == 0x1dd) {
				source_dynamic_entity = resolved_dynamic;
			}
			source_container_ptr = (char**)(resolved_dynamic + 10);
			source_owner_entity = gm_ResolveParentEntity(resolved_dynamic);
			if (source_owner_entity == (short*)0) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c2f, "cm_ExSellObjekt() Invalid 'gm_eval_ObjektBesitzer'", 8);
				return 1;
			}
		} else {
			source_owner_entity = source_static_entity;
			source_container_ptr = (char**)(source_static_entity + 0xbc);
		}
		dest_object = (ushort*)gm_ff_Objekt((int)*source_container_ptr, 1, 0, (uint)*(ushort*)(cmd + 0x18));
		if (dest_object == (ushort*)0) {
			sprintf(
				log_buffer.text,
				"cm_ExSellObjekt(): Object not found: ObjProt:%i Menge:%i CmdCnt:",
				(uint)*(ushort*)(cmd + 0x18),
				*(int*)(cmd + 0x1f),
				*(int*)(cmd + 8)
			);
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c53, log_buffer.text, 8);
			return 1;
		}
		if (source_dynamic_entity != (short*)0) {
			resolve_result = *(int*)(cmd + 0x1f);
			amount = gm_GetMsgField((int)source_dynamic_entity, (int)dest_object);
			if (amount < resolve_result) {
				sprintf(
					log_buffer.text,
					"cm_ExSellObjekt() Not enough Objekts at source: ObjProt:%i Menge:%i CmdCnt:%i",
					(uint)*(ushort*)(cmd + 0x18),
					resolve_result,
					*(int*)(cmd + 8)
				);
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c75, log_buffer.text, 8);
				return 1;
			}
		}
		if (*(int*)(dest_object + 7) < *(int*)(cmd + 0x1f)) {
			sprintf(
				log_buffer.text,
				"cm_ExSellObjekt() Not enough Objekts at source: ObjProt:%i Menge:%i CmdCnt:%i",
				(uint)*(ushort*)(cmd + 0x18),
				*(int*)(cmd + 0x1f),
				*(int*)(cmd + 8)
			);
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c97, log_buffer.text, 8);
			return 1;
		}
		if (*(int*)(cmd + 0x23) != 0 && source_owner_entity != (short*)0) {
			/* The reference loads this byte with `mov al,[cmd+0x1e]`
			 * (zero-extended), not `movsx`; the two differ for values
			 * >= 0x80 and the target's codegen picks the unsigned one.
			 * Fixing both QueryEntitySum call sites makes cm_ExSellObjekt's
			 * obj_size exactly 2057 (was 2055) and moves the split
			 * pipeline's masked differing bytes 6,515 -> 6,495. */
			gm_QueryEntitySum(*(int*)(source_owner_entity + 0xbc), (unsigned char) cmd[0x1e]);
		}
	}
	if (*(int*)(cmd + 0x10) != -1) {
		resolve_result = gm_GetFieldByType(cmd, *(int*)(cmd + 0x10));
		*(int*)(cmd + 0x10) = resolve_result;
		resolve_result = gm_ResolveEntityById(
			(void**)&dest_existing_entity,
			(void**)&resolved_dynamic,
			(void**)&source_static_entity,
			resolve_result
		);
		if (resolve_result == 0) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2cdd, "cm_ExSellObjekt() Invalid 'ziel_besitzer_id'", 8);
			return 1;
		}
		if (dest_existing_entity != (char*)0) {
			linked_list_ptr = (int*)(dest_existing_entity + 0x5d);
			if (*(ushort*)(dest_existing_entity + 0x27) != 0xffff) {
				dest_owner_entity = (short*)(g_slot_table +
					(uint)*(ushort*)(dest_existing_entity + 0x27) * 0x21c);
			} else {
				dest_owner_entity = (short*)0;
			}
		} else if (resolved_dynamic != (short*)0) {
			entity_type = *resolved_dynamic;
			if (entity_type == 0x2a || entity_type == 0x1db ||
				entity_type == 0x1dc || entity_type == 0x116) {
				dest_dynamic_entity = resolved_dynamic;
			check_producible:
				resolve_result = gm_eval_SlotVoll(
					(char*)resolved_dynamic,
					(uint)*(ushort*)(cmd + 0x18),
					*(int*)(cmd + 0x1f)
				);
				if (resolve_result < *(int*)(cmd + 0x1f)) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2d1b, "cm_ExSellObjekt() Lager voll", 8);
					return 1;
				}
			} else if (entity_type == 0x1dd) {
				goto check_producible;
			}
			linked_list_ptr = (int*)(resolved_dynamic + 10);
			dest_owner_entity = gm_ResolveParentEntity(resolved_dynamic);
		} else {
			linked_list_ptr = (int*)(source_static_entity + 0xbc);
			dest_owner_entity = source_static_entity;
		}
		if (*(g_unknown_1de450 + (uint)*(ushort*)(cmd + 0x18) * 0x41) == '\x1d') {
			dest_game_object = (ushort*)0;
		} else {
			dest_game_object = (ushort*)gm_ff_Objekt(*linked_list_ptr, 1, 0, (uint)*(ushort*)(cmd + 0x18));
		}
		if (*(int*)(cmd + 0x23) != 0 && dest_owner_entity != (short*)0) {
			resolve_result = gm_QueryEntitySum(*(int*)(dest_owner_entity + 0xbc), (unsigned char) cmd[0x1e]);
			if (resolve_result < *(int*)(cmd + 0x1f) * *(int*)(cmd + 0x23)) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2d4f, "cm_ExSellObjekt() Not enough Credits at destination", 8);
				return 1;
			}
		}
	}
	source_dynamic_ref = source_dynamic_entity;
	if (source_dynamic_entity != (short*)0) {
		if (dest_owner_entity != (short*)0) {
			parent_check = gm_ResolveParentEntity((short*)dest_object);
			if (parent_check != dest_owner_entity && *(int*)(dest_object + 0xe) != 0) {
				resolve_result = compute_size((char*)source_dynamic_ref, (int)*(ushort*)dest_object);
				*(volatile uint*)&log_buffer.weight_fraction = (uint)(resolve_result * *(int*)(dest_object + 0xe)) >> 2;
				amount = gm_GetMsgField((int)source_dynamic_ref, (int)dest_object);
				source_dynamic_ref = source_dynamic_entity;
				if ((uint)amount - *(volatile uint*)&log_buffer.weight_fraction < (uint)*(int*)(cmd + 0x1f)) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2d79, g_error_msg_sell_no_source, 8);
					return 1;
				}
			}
			goto finalize_transfer;
		}
	} else {
	finalize_transfer:
		if (dest_owner_entity != (short*)0 &&
			dest_existing_entity == (char*)0 &&
			dest_dynamic_entity == (short*)0 &&
			resolved_dynamic == (short*)0) {
			resolve_result = gm_CheckInventoryCapacity(
				(char*)dest_owner_entity,
				(uint)*(ushort*)(cmd + 0x18),
				*(int*)(cmd + 0x1f)
			);
			*(int*)(cmd + 0x1f) = resolve_result;
			if (resolve_result == 0) {
				return 1;
			}
		}
	}
	if (*(int*)(cmd + 0x23) != 0) {
		if (dest_dynamic_entity == (short*)0 && resolved_dynamic != (short*)0 &&
			*resolved_dynamic == 0x1dd) {
			capacity_check = gm_FindSlotById((uint)g_current_season, (uint)*(ushort*)(cmd + 0x18));
			if (capacity_check != (char*)0) {
				*(int*)(capacity_check + 0x18) = *(int*)(capacity_check + 0x18) + *(int*)(cmd + 0x1f);
			}
		}
		if (source_dynamic_ref != (short*)0 && *source_dynamic_ref == 0x1dd) {
			capacity_check = gm_FindSlotById((uint)g_current_season, (uint)*(ushort*)(cmd + 0x18));
			if (capacity_check != (char*)0) {
				*(int*)(capacity_check + 0x1c) = *(int*)(capacity_check + 0x1c) + *(int*)(cmd + 0x1f);
			}
		}
	}
	if (*(int*)(cmd + 0x14) != -1) {
		resolve_result = *(int*)(cmd + 0x1f);
		amount = *(int*)(dest_object + 7) - resolve_result;
		*(int*)(dest_object + 7) = amount;
		if (amount <= 0) {
			obj_category = *(g_unknown_1de450 + (uint)*(ushort*)(cmd + 0x18) * 0x41);
			if (obj_category == '\x06' || obj_category == '\x02') {
				if (source_existing_entity != (void*)0) {
					gm_RemoveObjectWrapper((int)source_existing_entity, (uint)*(ushort*)(cmd + 0x18));
				} else {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2def, g_error_msg_sell_no_dest, 8);
					return 1;
				}
			} else {
				gm_RemoveObjectByType(source_container_ptr, (uint)*(ushort*)(cmd + 0x18));
			}
		}
		if (*(int*)(cmd + 0x23) != 0) {
			gm_AddObjekt(
				*(int*)(source_owner_entity + 2),
				(uint) (unsigned short) g_entity_slot_table[(unsigned char) cmd[0x1e] * 189],
				*(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f)
			);
			if (source_dynamic_ref != (short*)0) {
				if (*source_dynamic_ref == 0x1db) {
					*(int*)(source_owner_entity + 0xd2) =
						*(int*)(source_owner_entity + 0xd2) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
				} else if (*source_dynamic_ref == 0x1dc) {
					*(int*)(source_owner_entity + 0xd0) =
						*(int*)(source_owner_entity + 0xd0) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
				} else {
					goto LAB_1000def2;
				}
			} else {
			LAB_1000def2:
				*(int*)(source_owner_entity + 0xce) =
					*(int*)(source_owner_entity + 0xce) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
			}
		}
	}
	if (*(int*)(cmd + 0x10) != -1) {
		/* The reference defers this load to 0x1000df0a, inside the
		 * dest-finalize guard: source-finalize at 0x1000de10 runs
		 * entirely on the source object.  Hoisting it above that
		 * block puts the whole source-finalize region on the dest
		 * pointer's slot and drifts the schedule to the end. */
		dest_object = dest_game_object;
		if (dest_game_object != (ushort*)0) {
			*(int*)(dest_game_object + 7) = *(int*)(dest_game_object + 7) + *(int*)(cmd + 0x1f);
		} else {
			obj_category = *(g_unknown_1de450 + (uint)*(ushort*)(cmd + 0x18) * 0x41);
			if (obj_category == '\x02' || obj_category == '\x06') {
				/* Success-first form (shapes §59): the reference lays
				 * its error tails out in REVERSE source order --
				 * 0x2e5d at 0x1000e009, 0x2e39 at 0x1000e0c2, then
				 * 0x2e45 at 0x1000e12f, past the ret.  Writing the
				 * null check as `== 0` first put 0x2e45 ahead of
				 * 0x2e39; this form reproduces the reference's
				 * order exactly. */
				if (dest_existing_entity != (char*)0) {
					dest_object = (ushort*)gm_AllocRaum(dest_existing_entity, (uint)*(ushort*)(cmd + 0x18));
					if (dest_object == (ushort*)0) {
						LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2e39, "cm_ExSellObjekt(): gm_AllocRaum failed", 8);
						return 1;
					}
				} else {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2e45, g_error_msg_sell_failed, 8);
					return 1;
				}
			} else {
				dest_object = (ushort*)gm_AllocObjekt(*(int*)(cmd + 0x10), (uint)*(ushort*)(cmd + 0x18), *(int*)(cmd + 0x1f));
				if (dest_object == (ushort*)0) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2e5d, "cm_ExSellObjekt(): gm_AllocObjekt failed", 8);
					return 1;
				}
				if (dest_dynamic_entity != (short*)0) {
					*(int*)(dest_object + 7) = *(int*)(dest_object + 7) + 1;
					obj_category = *(g_unknown_1de450 + (uint)*(ushort*)(cmd + 0x18) * 0x41);
					if ((obj_category == '\x17' || obj_category == '%') &&
						(*dest_dynamic_entity == 0x2a || *dest_dynamic_entity == 0x116) &&
						dest_owner_entity != (short*)0 &&
						((char)dest_owner_entity[1] == '\x06' || (char)dest_owner_entity[1] == '\a')) {
						*(int*)(dest_object + 0xe) = 4;
					}
				}
			}
		}
		*(int*)(g_player_slots_base[(unsigned char)cmd[3]].data + 0x264200) = *(int*)(dest_object + 1);
		if (*(int*)(cmd + 0x23) != 0 && dest_owner_entity != (short*)0) {
			gm_SubObjekt(
				*(void**)(dest_owner_entity + 2),
				(uint) (unsigned short) g_entity_slot_table[(unsigned char) cmd[0x1e] * 189],
				*(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f)
			);
			/* Volatile reload, not a spelling: without it msvc6 keeps
			 * dest_dynamic_entity in ebp across this join, so the
			 * cmd+0x10 then-arm has to end `mov edi,[esp+0x10];
			 * mov ebp,[esp+0x18]; jmp <join>` -- and a block ending
			 * in jmp cannot be the join's fall-through predecessor.
			 * msvc6 then lays the else-region inline and exiles this
			 * join (the player-slot store + gm_SubObjekt body) 147
			 * bytes past it.  The reference keeps nothing live here:
			 * it reloads from [esp+0x2c] at 0x1000df97 and falls
			 * straight through into 0x1000df2a.  Forcing that one
			 * reload restores the reference's block order. */
			if (*(short* volatile*)&dest_dynamic_entity != (short*)0) {
				if (*dest_dynamic_entity == 0x1db) {
					*(int*)(dest_owner_entity + 0xd0) =
						*(int*)(dest_owner_entity + 0xd0) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
					goto LAB_1000e0e7;
				}
				if (*dest_dynamic_entity == 0x1dc) {
					*(int*)(dest_owner_entity + 0xd2) =
						*(int*)(dest_owner_entity + 0xd2) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
					goto LAB_1000e0e7;
				}
			}
			*(int*)(dest_owner_entity + 0xcc) =
				*(int*)(dest_owner_entity + 0xcc) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
		}
	}
LAB_1000e0e7:
	if (result != (uchar*)0) {
		*result = 1;
		if (*(int*)(cmd + 0x10) != -1) {
			result[1] = 3;
			*(ushort**)(result + 6) = dest_object;
		}
	}
	return 0;
}
