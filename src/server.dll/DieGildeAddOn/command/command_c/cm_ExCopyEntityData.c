// FUNCTION: SERVER 0x1000ec00

#include "../command_internal.h"
#include "../../game/entity.h"


/* Execution handler: copies a block of raw data from the command
 * payload into a resolved entity's memory. Used for bulk entity
 * state synchronization across network.
 *
 * Conversion state (2026-09-13 probe): 443/912 matched, 567
 * matched-reloc, obj 912.  The "525/901 at obj 880" figure above and
 * the 11-bytes-padding theory predated later work that grew the object
 * to 912; retired.  Each
 * dated pass below records the score it started and ended at.
 *
 * The duplicated dispatch guard IS steerable from C.  MSVC6 collapses the
 * reference's second `test edi,edi; jbe default; cmp edi,ebx` pair only while
 * it can prove `level` unchanged between the two pairs.  Re-reading `level`
 * from cmd_ptr+0x24 between them makes the second load opaque to that
 * analysis, so both pairs survive and instructions 20-27 match one for one.
 *
 * Fixes landed in this pass, each measured:
 *   - the decay arms spelled `val = val + decay_high/low` instead of storing
 *     into a `delta` temp and adding after the merge.  Removing that live
 *     local fixes the whole register rotation in the matrix loop
 *     (outer_idx->edi, outer_ent->ebx, mat_row->edx, inner_ent->esi, all
 *     matching the reference) and brings the compile to exactly 901 bytes.
 *     402 -> 431.
 *   - both slot scans rewritten as `while (ptr < bound)` with the bound at
 *     the top and the hit leaving via goto.  That emits the reference's
 *     single `cmp [ptr],key` and `jb` back edge instead of a duplicated
 *     compare around the edge.  431 -> 417 positionally but removes the
 *     2-byte cascade that shifted everything from index 96 onward.
 *   - the matrix clamp spelled with an empty in-range middle case
 *     (`if (val > -0x7f && val < 0x7f) {} else if ... else ...`), which
 *     gives the reference's `jle` polarity with the low arm cold.  +3.
 *   - the type-2 arm accumulates into `dst_slot` itself rather than a
 *     separate `idx`, giving the reference's `add ecx,eax` with the array
 *     base as displacement, and reads primary into a temp BEFORE zeroing
 *     secondary, matching the reference's load/store order.
 *   - the type-0 arm keeps the store address in a pointer local taken after
 *     the load, matching the reference's `lea ecx,[eax+ecx+base]`.  +1.
 *
 * Residual: 173 structural, 7 instructions short of the target.  The whole
 * deficit is the cold clamp arms: the reference materializes the constant in
 * eax and jumps to a shared store (`mov eax,0x7f; jmp; mov eax,-0x7f; jmp`),
 * where MSVC6 collapses ours into a fallthrough that saves one jmp per arm.
 *
 * Dead ends measured this pass, none kept: per-arm stores inside the matrix
 * loop, `goto`-labelled stores, arms placed after the store, an unsigned
 * range test (compiles to setg/dec/and, far worse), a switch on a ternary
 * (branchless expansion), the empty-middle form on the type-1 first clamp
 * (417, msvc6 emits setge/dec/and there), and a merged single store in the
 * type-2 arm (418 at 874).  The matrix loop's remaining `[ecx+edx]` against
 * the reference's `[edx+ecx]` is SIB base/index role only: four subscript
 * spellings were probed (pointer arithmetic both operand orders, unsigned
 * subscript, integer-cast address) and all four compile identically, so per
 * msvc6-c-shapes.md section 34 it follows the induction variable's form and
 * is not steerable at zero byte cost.
 *
 * 2026-09-06 pass (421/901, obj 877, no change kept): row-multiply inner
 * access `base[outer*0x300+inner]` gives the reference SIB order in isolation
 * but regresses the whole function to 358 at obj 888; funneling the five
 * `return 1` sites through one `fail` label leaves output byte-identical
 * (msvc6 duplicates the block per goto site); explicit `goto low/high/store`
 * labels, a 3-arm 32-bit-temp shared store (cm_ExAllocWarEvent section 23
 * shape), and high-arm-first order all compile to the 25-byte collapsed form,
 * never the reference 27-byte `cmp/jle/cmp/jge/jmp/LOW/HIGH/store` layout.
 *
 * 2026-09-06 pass 2 (421/901, obj 877, frame fix kept): narrowing the
 * else-arm locals and the matrix-loop locals into their block scopes drops
 * one frame dword (sub esp,0x10 -> 0xc) and aligns the loop head through the
 * dispatch spills (IDX 55-63 now ==, was a 3-byte spill cascade). The W2
 * per-arm-store clamp scores 420 with only 98 structural and aligns the
 * whole loop tail and both scans, but keeps movb-imm arms. The row multiply
 * (`mat_row = MAT + outer_idx * 0x300` at loop top) flips the movsx/store
 * SIB to the reference order but spills outer_ent and STUBs at 335, so it
 * was reverted. Per-cluster size map: one cascade cluster 82-248 (+24B =
 * the whole gap). Next: combine W2 stores with a spill-free SIB flip, or
 * crack the cold-high-arm layout (30+ probed shapes in .scratch/probe_ec00*.c,
 * probe_clamp*.c, probe_sib*.c, probe_mataddr*.c, probe_type1*.c).
 *
 * 2026-09-06 pass 3 (421/901, obj 877, nothing kept): SIB roles probed to
 * exhaustion, all inert at 421 unless noted. Reversed subscripts
 * (inner_idx[mat_row]) and pointer-arithmetic access (*(mat_row+ii)) leave
 * [ecx+edx] unchanged; init-order swaps cost (row-first 409, mat_row/outer
 * swapped 413, both reorder the ebx/edx movs without flipping the SIB);
 * declaration order inert. Goto-decay arms compile identically (421). W2
 * per-arm-store matrix clamp scores 415 with 99 structural: it emits jg
 * entry polarity and movb-imm arms, losing the target jle/jge pair. Goto
 * type-1/type-2 clamps inert (type-2 at obj 874). Type-0 load through
 * scan_ptr 419. Shared-miss epilogue for the guards, temp-after-scale in
 * type-1, and save_dst live-range split all inert. The [edx+ecx]-vs-[ecx+edx]
 * byte differs only in the ModRM reg field; the roles follow which value the
 * allocator keeps as base (row pointer in edx) and no probed spelling flips
 * them at zero cost.
 *
 * 2026-09-08 pass (421 -> 463, obj 877 -> 887): the deficit was a raw-literal
 * spelling of addresses that have declared symbols, not the clamp shapes.
 * A literal like `(char*) 0x10035ab0` makes msvc6 materialize the address in
 * a register; the symbol form `g_slot_table + ... + 0x210` lets it fold the
 * base into the instruction's displacement, which is what the reference does.
 * All three are the same address, so the change is behaviour-preserving.
 *   - `owner_id` read as `g_slot_table + dst_slot * 0x21c + 0x210` instead of
 *     `dst_slot * 0x21c + 0x10035ab0`, giving the reference's
 *     `mov ebp,[eax+0x10035ab0]` at 0x1000edda.  421 -> 425.
 *   - `ebx_ptr` as `g_relationship_matrix_secondary + dst_slot` instead of
 *     `(char*) (dst_slot + 0x1014d8e0)`.  425 -> 429.
 *   - all three slot-scan bases as `g_slot_table + 4` instead of
 *     `(char*) 0x100358a4`.  429 -> 462.  They must move together: esi_ptr
 *     alone is 434, esi_ptr with the dst scan 458, esi_ptr with the src scan
 *     409.
 *   - the type-0 clamp as a two-arm `if (< -0x7f) else if (>= 0x7f)` with the
 *     store after the join, instead of the empty-middle three-arm form.
 *     462 -> 463.
 *
 * The empty-middle form is still correct for the matrix loop and the type-1
 * and type-2 arms: the two-arm rewrite scores 460, 459 and 429 there.
 * Also measured and reverted: the scan bounds written symbolically
 * (`g_slot_table + 4 + 0x300 * 0x21c`) 437-454, the dst guard read as
 * `*(ushort*)(0x100358a0 + dst_slot * 0x21c)` 417, `rel_value >= 0x7f` for
 * the type-1 first clamp (inert, msvc6 normalizes `0x7e <`).  The matrix
 * loop's own bases (outer_ent, inner_ent, mat_row) are inert either way;
 * they are written symbolically because it removes the literals, not for
 * a score.  The CFLAGS header is not consumed by the build (the toml owns
 * cflags): /Od through /Ox in the header all produce the identical object,
 * so the flag sweep on this function is a no-op, not a plateau.
 *
 * 2026-09-08 pass 2 (463 -> 512, obj 887 -> 883): the dst slot scan spelled
 * `do { } while (ptr < bound)` instead of `while (ptr < bound) { }`.  The
 * symbolic base from the previous pass made the bound a compile-time constant
 * again, so the top-tested form re-grew an entry guard (`mov esi,edx; cmp
 * esi,bound; jae`) that the reference does not have; the bottom-tested form
 * drops it and re-aligns the whole type-3 arm.  Both scans start at
 * `g_slot_table + 4`, which is never the bound, so skipping the entry test is
 * behaviour-preserving.
 *
 * The two scans do NOT move together here: the src scan converted to
 * `do/while` as well scores 443, so it stays top-tested.  Also measured on the
 * 512 body and reverted: a nested `if (val > -0x7f) { if (val < 0x7f) }` matrix
 * clamp 510, the src guard split into two separate returns (inert).
 *
 * Residual: 18 bytes, still the cold clamp arms.  The reference materializes
 * each constant and jumps to a shared store; msvc6 lays our type-0 arm out of
 * line with a backward jmp, which is the layout pass (section 17), not a
 * source-steerable choice.
 *
 * 2026-09-08 pass 3 (512, nothing kept).  The loop-shape lever that took
 * cm_ExProdObjekt from 457 to 964 does not transfer: every loop here was
 * converted to the top-tested `for (; bound; step)` form and all four are
 * inert or worse (matrix inner 512, matrix outer 512, dst scan 463 at obj
 * 887, src scan 512, type-3 decay walk 449 at obj 897).  cm_ExProdObjekt's
 * gain came from a body too long for a short back edge, which is not the
 * case in any loop here.  Also re-probed on the 512 body and reverted:
 * explicit `goto clamp_low/clamp_high/clamp_store` labels for the matrix
 * clamp (509 - the empty-middle three-arm form is still the best shape), a
 * shared `0xffff` constant local feeding the two slot guards, both as
 * `ushort` and as `int` (byte-identical output, msvc6 rematerializes the
 * immediate either way).
 *
 * 2026-09-08 pass 4 (512, nothing kept).  Located the size gap exactly: the
 * reference has THREE epilogues, this object has TWO.  The reference routes
 * all four slot guards (dst >= 0x300, dst 0xffff, src >= 0x300, src 0xffff)
 * into one shared `return 1` at 0x1000eda8 and gives each scan-exhausted
 * fallthrough its own; msvc6 cross-jumps all six sites here into a single
 * epilogue.  That merge plus the collapsed cold clamp arms is the whole
 * 18-byte deficit, and both are the same backend cross-jump pass.  Probed
 * against it and reverted: the two dst guards merged with `||` (inert), the
 * two src guards split into separate returns (inert), a distinct guarded
 * `return 1` ahead of the src fallthrough to defeat the merge (inert, msvc6
 * folds the redundant test).  The CFLAGS sweep does not reach it either:
 * /O2, /Ox, /O2 /Ob0, /Ox /Ob0, /O2 /Gy and /O2 /Gf all produce the identical
 * 883-byte object, and /O1, /Og, /Oaxs, /Oit and /Oity are far worse
 * (78-139).  Also re-probed on the 512 body and reverted: the type-1
 * secondary clamp as the empty-middle three-arm form (510 - the per-arm
 * store is correct there, the reference really stores in each arm at
 * 0x1000ef16/ef23/ef30), the matrix clamp as a two-arm `<= -0x7f` /
 * `>= 0x7f` (509), `inner_ent` declared before `inner_idx` (505), the inner
 * loop tail with the counter bumped before the pointer (inert, the reference
 * order is `add esi` then `inc ecx`), the inner access as `*(mat_row +
 * inner_idx)` (inert).
 *
 * 2026-09-08 pass 5 (512 -> 523, obj 883 -> 880): `#pragma optimize("a", on)`
 * on the function.  Assume-no-aliasing lets msvc6 keep the matrix-loop values
 * in registers across the byte stores, which realigns the type-1 and type-2
 * arms; the CFLAGS sweep never reaches it because the toml cflags apply to the
 * whole translation unit and /Oa is not part of /O2 or /Ox.  Confirmed
 * separately that the cflags themselves are inert: /O2 /Gd, /Ox /Gd, /Ox,
 * /O2 /Gy /Gd and /Ob0 /Ox /Gd all produce the identical object through
 * `rebrew test --cflags`, and /Oxs craters to 132.  Sweep of the other pragma
 * letters on this body: "w",on ties at 523/880, "p",on 462, "s",on and "t",off
 * 132, "g",off 78, "y",off 139, the rest inert; "a"+"w" together add nothing
 * over "a" alone.
 *
 * Residual at 523: 21 bytes, all in the cold clamp arms.  The reference
 * materializes each constant in eax and jumps to a shared store
 * (`mov eax,0x7f; jmp` / `mov eax,-0x7f; jmp`); msvc6 folds ours into
 * byte-immediate stores (`mov byte ptr [ecx],0x7f`) and cross-jumps the tails.
 * Re-probed on the 523 body and reverted: eight matrix-clamp spellings
 * (empty-middle low-first is still best at 523; two-arm `<=`/`>=` 520, goto
 * arms 520, nested 521), the type-2 arm as a shared store after the join
 * (511 at obj 880), as an empty-middle three-arm (511), a ternary (511) and
 * with goto labels (509).  Forcing the arms through a `volatile int` view of
 * the clamp value does grow the object to 899 of the target 901, but for the
 * wrong reason: it homes the value in `[esp+0x1c]` and the block becomes
 * `mov dword ptr [esp+0x1c],0x7f` / `mov al,[esp+0x1c]`, not the reference's
 * register materialization (377).  The epilogue count is unchanged at two
 * against the reference's three; every guard split, merge and volatile
 * formulation probed leaves it at two, consistent with the pass-4 finding
 * that this is the backend cross-jump pass.
 *
 * 2026-09-08 pass 6 (523 -> 525, obj unchanged at 880).  The type-0 clamp
 * spelled as an empty-middle three-arm with `>= -0x7f && < 0x7f` as the
 * in-range test, instead of the two-arm `< -0x7f` / `>= 0x7f` form.  That
 * emits the reference's `jl` / `jge` pair at 0x1000ee8e-0x1000ee93 with both
 * cold arms out of line, where the two-arm form gave `jl` plus a fallthrough.
 * The pass-5 note recording the two-arm form as better was measured before
 * the `#pragma optimize("a", on)` landed.
 *
 * The same polarity does NOT transfer to the other three clamps: the matrix
 * loop scores 524, the type-1 secondary 519 and the type-2 519, so each keeps
 * the form already recorded for it.  Also measured on the 525 body and
 * reverted: the type-2 arm rewritten with a shared store after the join (504
 * at obj 877), a volatile view of the type-2 secondary zero store (inert),
 * the src slot scan as do/while (436 at obj 890, the pass-2 finding still
 * holds after the pragma), and the dst scan written as a top-tested
 * `while (*ptr != key)` with the bound test in the tail (byte-identical
 * output, msvc6 normalizes it to the same rotation).  The pragma sweep is
 * also exhausted as a pair: "aw", "at", "ag", "ay" and "aq" all tie at 523
 * on the pre-pass body, "ap" is 464 and "as" 132.
 *
 * 2026-09-08 pass 7 (525, nothing kept).  The levers that took the siblings
 * cm_ExProdObjekt to 98% and ahm_ExAllocAlchemist to 82% were ported and none
 * applies here, each measured on the 525 body:
 *   - the volatile-pointer reload (`*(char* volatile*) &cmd_ptr`) on the
 *     type-2 arm's 0x18 read 497 at obj 884.
 *   - `*(volatile int*)` on the type-1 arm's SECOND 0x18 read does reproduce
 *     the reference's re-read (`mov edx,[edi+0x18]` at 0x2f7) and its `esi`
 *     role at 0x2c8, and grows the object 880 -> 883 of the target 901, but
 *     the block below it shifts and the score falls to 512.  Combined with
 *     the empty-middle first clamp 513, with the first 0x18 read volatile too
 *     512.  This is the closest anything has come to the missing bytes and is
 *     worth re-measuring if the cold-arm layout is ever cracked.
 *   - the type-2 index split into its own `idx` local, so the matrix base
 *     stops folding into ecx, 524.
 *   - volatile on the type-2 secondary zero store (inert), the type-1 first
 *     clamp as an empty-middle three-arm 524, the matrix clamp as a two-arm
 *     `<= -0x7f` / `>= 0x7f` 522, and the four slot guards routed through one
 *     explicit `guard_fail` label to force the reference's third epilogue
 *     (byte-identical output: msvc6 duplicates the block per goto site, so
 *     the epilogue count stays at two against the reference's three). */
/* 2026-09-13 (round 110): THE THIRD POSITION BREAK, FIXED -- and it was
 * source-shape after all.  Two clamps are now spelled "in range first, then
 * HIGH, then low" instead of "in range first, then low, then high": the
 * `ebx_type == 0` arm and the matrix loop.  That is a pure reordering of the
 * same three arms, and it is what makes msvc6 materialise the clamp constants
 * in eax (`mov eax,0x7f` / `mov eax,0xffffff81`) in four more arms instead of
 * folding them into byte-immediate stores.
 *
 *   obj  880 -> 904        COMDAT span 880 -> 912  (= the reference's)
 *   positional match 196 -> 198
 *   register-agnostic 202 matched / 31 target-only -> 204 / 25
 *
 * Either clamp alone gives obj 892, whose span is 896 -- one byte short of the
 * window.  The three open spans (this one, vfs_ReadCompressed and CrashDump)
 * only work as a set; see docs/TODO.md round 110.
 */
/* 2026-09-14 (round 242 pass): the type-2 arm re-spelled "in range first, then
 * HIGH, then low" -- arms in that source order, per-arm stores kept:
 *
 *   if (rel_value >= -0x7f && rel_value < 0x7f)      { store }
 *   else if (rel_value >= 0x7f) { rel_value = 0x7f;  store }
 *   else                        { rel_value = -0x7f; store }
 *
 * (was `if (< -0x7f) low else if (< 0x7f) in-range else high`).  Exhaustive and
 * mutually exclusive, so it is the same three cases with the same three stores.
 * The reference emits this arm as `jl low / jge high / store / jmp` and we were
 * emitting a two-arm `jge` fold; the reorder gives the reference's `jl`/`jge`
 * pair with the in-range store in the middle, which is the shape the type-0 arm
 * has had since round 110 (see that note).
 *
 *   honest matched 430 -> 443, object 912 -> 912, real body 900 -> 905
 *   (COMDAT 912 either way: cl pads a COMDAT to 16, so real in 897..912 is
 *   composition-neutral -- see docs/msvc6-allocator.md Finding 58)
 *   matched-reloc 584 -> 567 and aligned 185 -> 184: both are fixed-offset
 *   artefacts of the +5 body, the type-2 arm now emits one block per arm where
 *   the fold emitted two.
 *
 * Measured on this body and reverted (each object-level probe, one at a time):
 * the same arm with a single shared store after the join 897 B / 420 / 578;
 * with the type-0 arm also per-arm 904 B / 440 / 572; adding the type-1
 * secondary clamp reordered the same way 905 B (holds real 900 exactly) /
 * 437 / 573 with aligned 195, the best alignment measured here; a shared
 * `ushort empty = 0xffff` local feeding all four slot guards is byte-identical
 * (msvc6 rematerialises the immediate); the dst slot scan top-tested restores
 * the reference's unrotated loop but adds the entry guard, 904 B / 383 / 537
 * with aligned 191; src scan bottom-tested 910 B / 350 / 514.  The matrix
 * clamp's per-arm store form is a wash (429/583/187). */
/* /Oa is not implied by the toml cflags and is worth 11 bytes here: see the
 * pass-5 note above. */
#pragma optimize("a", on)
int __cdecl cm_ExCopyEntityData(char* cmd_ptr, char* response)
{
	int rel_value;
	int target_field;
	int ebx_type;
	uint src_slot;
	uint dst_slot;
	int threshold_high;
	int threshold_low;
	int decay_high;
	int decay_low;
	uint level;

	{
		char* cmd = (char*) cmd_ptr;
		rel_value = gm_GetFieldByType(cmd, *(int*) (cmd + 0x10));
		*(int*) (cmd + 0x10) = rel_value;
		target_field = gm_GetFieldByType(cmd, *(int*) (cmd + 0x14));
		*(int*) (cmd + 0x14) = target_field;
		ebx_type = *(int*) (cmd + 0x1c);
	}

	if (ebx_type == 4) {
		int outer_idx;
		int inner_idx;
		char* outer_ent;
		char* inner_ent;
		char* mat_row;
		int val;
		level = *(uint*) (cmd_ptr + 0x24);

		/* The reference keeps BOTH guard pairs at 0x1000ec37-0x1000ec4d:
		 * `test edi,edi; jbe default; cmp edi,ebx; jae set28` followed by
		 * an identical `test edi,edi; jbe default; cmp edi,ebx; jne lvl3`.
		 * MSVC6 collapses the second pair in every straightforward
		 * formulation (it proves `level` unchanged and the test subsumed).
		 * Re-reading `level` from cmd_ptr+0x24 between the two pairs
		 * defeats that: the load is opaque to the analysis, so both pairs
		 * survive and the block matches the reference instruction for
		 * instruction.  The re-read is behaviour-preserving - nothing
		 * between the two guards writes cmd_ptr+0x24 or calls out. */
		if (level > 0) {
			if (level >= (uint) ebx_type) {
				goto set28;
			}
		}
		else {
			goto level_default;
		}
		level = *(uint*) (cmd_ptr + 0x24);
		if (level > 0) {
			if (level == (uint) ebx_type) {
				goto set28;
			}
		}
		else {
			goto level_default;
		}
		goto level_3;
set28:
		threshold_high = 0x28;
		threshold_low = -115;
		decay_high = -20;
		decay_low = 3;
		goto level_done;
level_3:
		if (level == 3) {
			threshold_high = 0x37;
			threshold_low = -105;
			decay_high = -16;
			decay_low = 5;
		}
		else if (level == 2) {
			threshold_high = 0x46;
			threshold_low = -95;
			decay_high = -12;
			decay_low = 7;
		}
		else if (level == 1) {
			threshold_high = 0x55;
			threshold_low = -85;
			decay_high = -8;
			decay_low = 9;
		}
		else {
level_default:
			threshold_high = 0x64;
			threshold_low = -75;
			decay_high = -5;
			decay_low = 11;
		}
level_done:

		outer_idx = 0;
		outer_ent = (char*) 0x100358a0;
		mat_row = (char*) 0x100a9820;
		do {
			inner_idx = 0;
			inner_ent = (char*) 0x100358a0;
			do {
				val = (int) (signed char) mat_row[inner_idx];
				if (outer_idx != inner_idx &&
					*(ushort*) outer_ent != (ushort) 0xffff &&
					*(ushort*) inner_ent != (ushort) 0xffff) {
					if (val > threshold_high) {
						val = val + decay_high;
					}
					else if (val < threshold_low) {
						val = val + decay_low;
					}
					if (val > -0x7f && val < 0x7f) {
						/* in range */
					}
					else if (val <= -0x7f) {
						val = -0x7f;
					}
					else {
						val = 0x7f;
					}
					mat_row[inner_idx] = (char) val;
				}
				inner_ent += 0x21c;
				inner_idx++;
			} while ((int) inner_ent < 0x1009aca0);
			mat_row += 0x300;
			outer_idx++;
			outer_ent += 0x21c;
		} while ((int) mat_row < 0x10139820);
	}
	else {
		int owner_id;
		char* esi_ptr;
		char* ebx_ptr;
		char* scan_ptr;
		int idx;
		int temp;
		int src_key;
		dst_slot = 0;
		scan_ptr = g_slot_table + 4;
		do {
			if (*(int*) scan_ptr == target_field) {
				goto dst_found;
			}
			scan_ptr += 0x21c;
			dst_slot++;
		} while ((uint) scan_ptr < 0x1009aca4);
		/* The reference reaches its epilogue at 0x1000eda8 by FALLING OUT of
		 * this loop, inline (`pop edi; pop esi; pop ebp; mov eax,1; pop ebx;
		 * add esp,0xc; ret`), where our build jumps to a shared exit that the
		 * three `return 1;` sites below also use.  Probe A4 (round 1095)
		 * measured both ways to break the fold: giving this site a distinct
		 * value (`temp = 1; return temp;`) compiles the object 7 bytes SHORT
		 * (905 against 912), and a value-preserving expression
		 * (`return (int) (dst_slot == 0x300) | 1;`) compiles it 44 bytes LONG
		 * (956).  Both change codegen and neither reaches the reference's
		 * layout, so the merge is not breakable by respelling the value.
		 * Matching the reference needs the three returns to differ
		 * STRUCTURALLY -- see codegen-walls section 39. */
		return 1;
dst_found:
		if (dst_slot >= 0x300) {
			return 1;
		}
		if (((ushort*)g_slot_table)[dst_slot * 0x10e] == (ushort) 0xffff) {
			return 1;
		}
		if (ebx_type == 3) {
			owner_id = *(int*) (g_slot_table + dst_slot * 0x21c + 0x210);
			esi_ptr = g_slot_table + 4;
			ebx_ptr = g_relationship_matrix_secondary + dst_slot;
			do {
				if (*(int*) esi_ptr != owner_id) {
					temp = (int) (signed char) *ebx_ptr;
					*ebx_ptr = (char) (int) ((float) temp * *(float*) (cmd_ptr + 0x20));
				}
				esi_ptr += 0x21c;
				ebx_ptr += 0x300;
			} while ((int) esi_ptr < 0x1009aca4);
		}
		else {
			src_key = *(int*) (cmd_ptr + 0x10);
			src_slot = 0;
			scan_ptr = g_slot_table + 4;
			while ((uint) scan_ptr < 0x1009aca4) {
				if (*(int*) scan_ptr == src_key) {
					goto src_found;
				}
				scan_ptr += 0x21c;
				src_slot++;
			}
			return 1;
src_found:
			if (src_slot >= 0x300 || ((ushort*)g_slot_table)[src_slot * 0x10e] == (ushort) 0xffff) {
				return 1;
			}
			if (ebx_type == 2) {
				dst_slot = dst_slot + src_slot * 0x300;
				temp = (int) (signed char) g_relationship_matrix_primary[dst_slot];
				g_relationship_matrix_secondary[dst_slot] = 0;
				rel_value = *(volatile int*) (cmd_ptr + 0x18) + temp;
				if (rel_value >= -0x7f && rel_value < 0x7f) {
					g_relationship_matrix_primary[dst_slot] = (char) rel_value;
				}
				else if (rel_value >= 0x7f) {
					rel_value = 0x7f;
					g_relationship_matrix_primary[dst_slot] = (char) rel_value;
				}
				else {
					rel_value = -0x7f;
					g_relationship_matrix_primary[dst_slot] = (char) rel_value;
				}
			}
			else if (ebx_type == 1) {
				temp = *(int*) (cmd_ptr + 0x18);
				dst_slot = dst_slot + src_slot * 0x300;
				rel_value = (int) (signed char) g_relationship_matrix_primary[dst_slot] + temp;
				if (rel_value < -0x7f) {
					rel_value = -0x7f;
				}
				else if (0x7e < rel_value) {
					rel_value = 0x7f;
				}
				g_relationship_matrix_primary[dst_slot] = (char) rel_value;
				if (*(volatile int*) (cmd_ptr + 0x18) >= 0) {
					rel_value = rel_value / 2;
				}
				rel_value = rel_value + (int) (signed char) g_relationship_matrix_secondary[dst_slot];
				if (rel_value >= -0x7f && rel_value < 0x7f) {
					g_relationship_matrix_secondary[dst_slot] = (char) rel_value;
				}
				else if (rel_value >= 0x7f) {
					rel_value = 0x7f;
					g_relationship_matrix_secondary[dst_slot] = (char) rel_value;
				}
				else {
					rel_value = -0x7f;
					g_relationship_matrix_secondary[dst_slot] = (char) rel_value;
				}
			}
			else if (ebx_type == 0) {
				idx = (int) (src_slot * 0x300 + dst_slot);
				temp = (int) (signed char) g_relationship_matrix_primary[idx];
				scan_ptr = &g_relationship_matrix_primary[idx];
				rel_value = *(int*) (cmd_ptr + 0x18) + temp;
				if (rel_value >= -0x7f && rel_value < 0x7f) {
					/* in range, keep rel_value */
				}
				else if (rel_value >= 0x7f) {
					rel_value = 0x7f;
				}
				else {
					rel_value = -0x7f;
				}
				*scan_ptr = (char) rel_value;
			}
		}
	}
	if (response != (char*) 0) {
		*response = '\x01';
	}
	return 0;
}
