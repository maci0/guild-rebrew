/* spiel fragment D — object list helpers (gm_AddObjekt,
 * gm_SubObjekt, gm_SubObjectNoKill) and the filtered entity scanner. */


#include "../../Units/Error/error.h"

#include <stdio.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void* list, int obj_id);

extern unsigned char* g_query_filter_base; /* 0x10035464 */
extern short g_query_filter_extra2; /* 0x10030b8c */
extern short g_query_filter_extra3; /* 0x10030b8e */
extern unsigned char g_filter_extra5; /* 0x10030b84 */
extern int g_query_filter_extra1; /* 0x10030b88 */
extern unsigned char g_query_filter_extra4; /* 0x10030b90 */
extern char g_dynasty_field_48; /* 0x10035448 */
extern char g_dynasty_field_49; /* 0x10035449 */
extern int g_dynasty_field_4c; /* 0x1003544c */

/* Adds b units of object a to the list reachable from the resolved parent
 * entity, or accumulates the amount into an existing entry.  Returns the
 * entry pointer (or the result of gm_AllocObjekt when a new entry was
 * created). */

// FUNCTION: SERVER 0x10016cd0
// gm_AddObjekt

int __cdecl gm_AddObjekt(int a, int b, int c)
{
	char* list_head;
	void* dyn;
	void* exi;
	void* sta;

	if (b == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xdf4,
		                   "gm_AddObjekt(): obj == ob_NULL", 1);
		return 0;
	}
	if (!gm_ResolveEntityById(&dyn, &exi, &sta, a)) {
		char buf[0x200];
		sprintf(buf, "gm_AddObjekt(): Parent not found. ObjProt:%i Menge:%i", b, c);
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xdfd, buf, 8);
		return 0;
	}
	if (dyn != 0) list_head = (char*) dyn + 0x5d;
	else if (exi != 0) list_head = (char*) exi + 0x14;
	else if (sta != 0) list_head = (char*) sta + 0x178;
	else return 0;
	exi = (void*) gm_ff_Objekt(*(int*) list_head, 1, 0, b);
	if (exi == 0) {
		return (int) gm_AllocObjekt(a, b, c);
	}
	*(int*) ((char*) exi + 0xe) += c;
	return (int) exi;
}

/* Removes c units of object b from the list reachable from the resolved
 * parent entity.  When the entry's count drops to zero the entry is
 * removed from the list.  Returns 1 on success, 0 on failure. */

// FUNCTION: SERVER 0x10016de0
// gm_SubObjekt

int __cdecl gm_SubObjekt(int a, int b, int c)
{
	char* list_head;
	void* dyn;
	void* sta;

	if (!gm_ResolveEntityById(&dyn, (void**) &a, &sta, a)) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xe2d,
		                   "gm_SubObjekt(): Parent not found", 1);
		return 0;
	}
	if (dyn != 0) list_head = (char*) dyn + 0x5d;
	else if (a != 0) list_head = (char*) a + 0x14;
	else if (sta != 0) list_head = (char*) sta + 0x178;
	else return 0;
	a = (int) gm_ff_Objekt(*(int*) list_head, 1, 0, b);
	if (a == 0) {
		return 0;
	}
	if (*(int*) (a + 0xe) < c) {
		return 0;
	}
	*(int*) (a + 0xe) -= c;
	if (*(int*) (a + 0xe) <= 0) {
		gm_RemoveObjectByType(list_head, b);
	}
	return 1;
}

/* Like gm_SubObjekt but keeps the list entry alive: a missing entry is
 * allocated with a negative count instead of failing.  Returns 1.
 *
 * The query result reuses `exi` (the resolve out-param) rather than a
 * separate `int r`: the extra local claimed its own frame slot and shifted
 * the whole stack layout.  Reusing `exi` gives the target's slot
 * assignment (exi = [esp+0x18]) and its lazy `push esi` before the query
 * call.  The tail is one merged `if (count == 0) remove;` + `return 1`,
 * not an early `return 1` on the non-zero path. */

// FUNCTION: SERVER 0x10016ea0
// gm_SubObjectNoKill

int __cdecl gm_SubObjectNoKill(int a, int b, int c)
{
	char* list_head;
	void* exi;
	void* dyn;
	void* sta;

	if (!gm_ResolveEntityById(&dyn, &exi, &sta, a)) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xe5c,
		                   "gm_SubObjectNoKill(): Parent not found", 1);
		return 0;
	}
	if (dyn != 0) list_head = (char*) dyn + 0x5d;
	else if (exi != 0) list_head = (char*) exi + 0x14;
	else if (sta != 0) list_head = (char*) sta + 0x178;
	else return 0;
	exi = (void*) gm_ff_Objekt(*(int*) list_head, 1, 0, b);
	if (exi == 0) {
		exi = (void*) gm_AllocObjekt(a, b, 1);
		*(int*) ((char*) exi + 0xe) = 0;
	}
	*(int*) ((char*) exi + 0xe) -= c;
	if (*(int*) ((char*) exi + 0xe) == 0) {
		gm_RemoveObjectByType(list_head, b);
	}
	return 1;
}


/* Scans the entity array for the next entity matching the active filter
 * state (set up by gm_StartFilteredEntitySearch).  Advances the search
 * cursor, counts inspected candidates, and returns the first match or
 * NULL once the array is exhausted.
 *
 * 2026-09-06 session, all re-measured in-file against the 99 baseline and
 * reverted unless noted. Loop B as `do { p += a9; store; } while (global <
 * end && *p == 0)` (global in the condition instead of the local) reaches
 * 171 with the volatile candidate reload kept: the global condition keeps
 * the bound test live so the reload survives, and the back edge lands one
 * instruction closer to the target. The same loop with a plain reload folds
 * the candidate test away (144). Hoisting extra1/extra2/extra4 into caller
 * locals read once before the scan loop (171) beats the block-scope and
 * function-scope variants tried this session (104: the hoists sink the
 * prologue pushes when their first use dominates the entry guards). The
 * `match in dl vs cl` wall stands: the candidate reload picks ecx for the
 * cursor, evicting match to dl, and no decl-order, init-spelling, peel-form,
 * param-order, or N1-style cursor-as-parameter variant moves it (163-169).
 * The flag48-once (peel) vs flag48-each-iteration shapes are provably
 * equivalent here because the filter globals are static across iterations:
 * any entry-value difference washes out at the next pass/fail. File kept at
 * best score; no code change from this session.
 * 2026-09-06 (this session, s7 probe series + in-file verifies, file held at
 * 99/346, PROVEN re-passing, siblings RELOC): two tail restructures KEPT for
 * target-faithfulness (score-neutral, entry-blocked): the advance loop now
 * splits its exits (bound-fail `goto adv_fail` -> base=0/return 0, byte-found
 * `goto b5`), the pre-loop match test joins b5 (`if (match == 0)` wraps the
 * loop), and b5 ends `if (match == 0) continue; return p;` -- the loop is
 * tight (no peel) and the ca redundant match test is kept, matching the
 * target's a2/b5/ca/ce/d5 flow; Loop A is now `while (*p == 0)` (top-check,
 * target's fc4/jb shape) with the trailing `goto candidate` kept (target
 * keeps its redundant jmp at fd7). Ruled out this session: initializer-form
 * and reordered match/end inits (inert, 99); merged/nested entry guards
 * (inert); extra1/2/4 hoists at candidate:, before-scan, or reverse-decl
 * order (82-96, spills); do/for advance variants (peeled, 99); epilogue
 * gotos (still merge to one far block). The entry wall stands: this
 * toolchain emits all four pushes at entry with one shared far epilogue and
 * no C shape (init order, guard form, hoist position, goto-fail) triggers
 * the shrink-wrapping the target shows (push esi early, inline pop-esi-only
 * exits, ebx/ebp/edi sunk to ff9); the binary's own 0x1001d425 proves the
 * original compiler does it, so the lever is structural and still unprobed
 * (best guess: entry-guard exits as fall-through-into-inline-code, which
 * needs inverted conditions the current ifs do not produce).
 *
 * The shrink-wrap trigger was isolated by direct-docker bisection
 * (.scratch/l2lane/pr, cl 12.00.8168, /O2 /Gd).  Building the function up
 * from a minimal skeleton, msvc6 sinks push ebx/ebp/edi below the entry
 * guards right up to the point where a bound re-test `if (p >= end) return 0;`
 * sits at the BOTTOM of the outer loop, after the inner advance loop.  Probes
 * k3 (no bottom test) sinks all three; j1 (k3 plus that one line) pushes all
 * four at entry.  j2 shows the sibling `if (match != 0) ...` side effect in the
 * same position is harmless, so it is specifically the loop-bottom compare
 * against `end` that pins the callee-saved set live across the guards.  The
 * target reaches its equivalent test at 0x100170b5 by falling through from the
 * advance loop's byte-found exit, never as a loop-bottom test, and this
 * toolchain re-synthesises the loop-bottom form from every C spelling probed:
 * do/while advance, while(p < end && *p == 0), goto-based advance, folding the
 * test into the match test, moving it onto the else arm, and dropping it on the
 * advance path (probes ta/tb/tc/u1/u2/s1/s2, all four pushes at entry).
 *
 * Explicit preheader hoists of extra1/extra2/extra4 into locals do move the
 * push offsets (probe g1: 00005 00006 0000f 00012 against the baseline 00005
 * 00006 00007 00015) but never sink any push below the guards, and in-file the
 * same hoist scores 75/346 against the baseline 99 because msvc6 additionally
 * caches g_entity_type_table in ebp across the entry guards.  Volatile reads
 * that suppress the hoists reduce the eager set on the minimal skeleton
 * (probe d0 reaches the target's single `push esi`) but are inert once all five
 * filter checks are present (probes z1-z4, w2/w3/w6, v1-v5).  A /O1 or /Oxs
 * build gives 3 pushes instead of 4, still all at entry, and CFLAGS are per-TU
 * here so the RELOC file-mates would pay for it.
 *
 * With every post-entry byte positionally shifted behind the three misplaced
 * pushes, no byte after offset 3 can match, which is what holds the score at
 * 99/346 despite obj size being exactly right at 346.
 *
 * 2026-09-08 session.  Two measurement facts first, because they invalidate
 * earlier probe numbers: `rebrew diff` and `rebrew test --va` compile this
 * function as its own translation unit and emit 384 bytes, not the 346 the
 * whole file emits, so only `rebrew test <file>` describes the shipped object.
 * Probe scores taken from the standalone build (99 -> 101 -> 105 shapes) do not
 * reproduce in-file.  A reconstructed-candidate disassembler for the in-file
 * bytes is at .scratch/exact-hunt/indis.py.
 *
 * The docs 38 bisect was run in-file (.scratch/exact-hunt/infile_gen.py, one
 * filter check added per step): 0 checks obj 170 with 1 eager push, 1-4 checks
 * obj 216/240/269/291 with 2 eager pushes (ebx, esi), 5 checks obj 322 flips to
 * 3 (ebx, ebp, esi) and 6 checks holds at 3 + edi.  The threshold is real, but
 * the target needs 5 filter checks live and only one entry push, so no legal
 * subset of the function sits below it.
 *
 * Ruled out this session, all measured in-file against 99 with all three
 * file-mates re-checked at full RELOC: making the two late `return 0` paths
 * unfoldable so they cannot merge into the four-pop tail, in both places and
 * each alone (99, the docs/msvc6-allocator.md Finding-6 recipe point 1 does not
 * apply here because the merge is not what pins the pushes); the same through a
 * volatile load (86/99/86); `#pragma optimize` for all of t/s/g/w/p/a/l/y in
 * both directions (91-99, none moves a push, /Ot and /Os only shrink the object
 * to 316); moving the `match`/`end` initialisers below the guards (87/88/101);
 * `const` end (99); merging the two entry guards into one `||` (99); routing
 * them through a shared `goto` label (99); making each filter global volatile
 * individually (91/96/98/100/100) and all five at once (104); reordering the TU
 * so this function compiles first (99); `unsigned short`/`int` match (91/97);
 * `unsigned int` end (99); a `row` local of every width in the extra4 arm, plus
 * the *p*589 folding (99 each: that arm already emits the target's
 * xor/mov/add/lea/shl/add/lea/mov sequence byte for byte).
 *
 * The only shapes that beat 99 are semantically wrong or inert-by-accident and
 * were not kept: returning `g_query_filter_base` from the post-`candidate`
 * bound guard scores 105, but the target returns a literal 0 there
 * (`xor eax,eax` at 0x10016ff5); a dead volatile re-read of extra2 at the end
 * of the extra4 arm scores 104 and moves no push.
 *
 * 2026-09-08 session, 113 -> 130/346 at obj 345 (target 346).  The recovered
 * instruction sequence in git ca8766f was used as the specification; probes
 * ran standalone against a saved target image (.scratch/l6-fnfe/probe.py,
 * wine cl 12.00.8168, /O2 /Gd, relocation-masked scoring that reproduces
 * `rebrew test` exactly).  Two levers moved it:
 *
 * 1. The `g_dynasty_field_49 = 0` store must not be able to reuse `match`'s
 *    zeroed register.  Reading `g_query_filter_base` BEFORE the store, and
 *    initialising `match` at `candidate:` instead of at entry, makes msvc6
 *    emit the target's `mov byte ptr [g_dynasty_field_49], 0` immediate form
 *    (0x10016fb9) instead of `mov [g_dynasty_field_49], cl`.  113 -> 128.
 * 2. The tail must reach the zero-store through a `goto clear` from the
 *    post-loop bound test, with `if (match != 0) return p;` ahead of it and
 *    no `hit` alias.  That reproduces the target's two-exit tail at
 *    0x1001710a/0x1001712a and closes the object from 386 to 345.  128 -> 130.
 *
 * The `a2:` inverted-goto in the no-flag advance loop is load-bearing: the
 * plain `if (p >= end) return 0;` spelling scores 100, the inverted form 130.
 *
 * The entry wall described below was BROKEN in the 2026-09-08 round-7 pass;
 * see the round-7 note at the end of this block.  Ruled out before that,
 * all measured standalone with the file re-tested at 130 and the
 * three file-mates re-checked at full RELOC: inverted entry guards with
 * fall-through returns (109); a single shared `return 0` reached by goto
 * from both guards (inert); distinct `(void*) 0` return expressions to block
 * tail-merging (inert); computing `end` lazily after one or both guards
 * (121/120); dropping each filter global in turn to shorten a callee-saved
 * range (84/93/102, pushes unmoved in all three); block-scope caches of
 * extra1/extra2/extra4 read at the loop top (80); `volatile` end (89);
 * replacing the loop-bottom `p < end` compare with an `int` down-counter so
 * no `end` reference survives past `candidate:` (99, pushes unmoved -- this
 * refutes the earlier note that the loop-bottom bound test is the pin);
 * `int`/`unsigned int` match (93 each); `for(;;)` and while-form advance
 * loops (107/125); reversed advance-loop condition order (129); and the
 * /Ox, /O1, /Oy-, /Ot /Og, /Gs, /Gf, /Gy, /Ob0 and /Og /Oi /Ot /Ob1 flag
 * sweeps (/O2 and /Ox tie at 130, everything else 92-128).
 *
 * The shrink-wrap and the tail shape are coupled: the `hit` alias with the
 * `match != 0 && hit != 0` guard is what triggers the correct one-push
 * prologue, but it forces the 386-byte tail (123 at best, .scratch/l6-fnfe/
 * p1.inc), while the 345-byte tail forces the four-push prologue.  Six
 * attempts to hold both (ja/pa/pb/pc/bA/bC) scored 96-126.
 *
 * 2026-09-08 round 7, 130 -> 168/346, object 345 -> 342 (target 346).
 * The prologue wall above is solved.  Bisected in .scratch/l7-fnfe with a
 * minimal reproducer (m3/mH/v3/x1..x3 probe series, docs section 38's own
 * m3.c as the starting point): msvc6 keeps the shrink-wrapped `push esi`
 * prologue only while the function has ONE return point.  A second reachable
 * return that yields a different value forces all four pushes to entry, and
 * that is what the old `if (match != 0) return p; ... return 0;` tail did.
 * Three coupled changes, each worthless alone:
 *
 * 1. Single return point.  The tail folds both outcomes into `p`
 *    (`if (match == 0) { g_query_filter_base = 0; p = 0; } return p;`).
 *    Re-splitting it into two returns costs the prologue immediately
 *    (probes zq1/zr1, 123 with all four pushes back at entry).
 * 2. The scan loop leaves only by `break`.  An in-loop `return` collapses
 *    the prologue exactly like a second tail return (probes m8/mE vs mD/mH).
 * 3. The scan loop's advance is rotated so the byte test sits at the top of
 *    the body, not the bottom.  Standalone this closes the object from 362
 *    to exactly 346 (probe ze1); the plain do/while spelling stays at 362.
 *
 * The first-arm bound test then folds into `if (p < end) { ... }` instead of
 * an early `return 0`, worth 122 -> 166 standalone (probe af1).
 *
 * Remaining delta, from the sequence diff (.scratch/l7-fnfe/sdiff.py, which
 * masks branch displacements and relocated operands so layout shifts do not
 * hide content): three hunks.  The entry guards still reach one shared
 * epilogue instead of the target's inline `xor eax,eax; pop esi; ret` at
 * 0x10016f97/0x10016fa7; the extra3 arm emits `je` into an inline clear
 * instead of the target's `jne` to the out-of-line block at 0x100170c6; and
 * the loop-back test carries the opposite polarity.  All three are
 * out-of-line block placement, which docs/msvc6-c-shapes.md section 17
 * records as not steerable from C.  Probes that did not move any of them:
 * inverted entry guards (zf1), distinct return expressions per guard (zg1),
 * `p = 0` before the guards (zh1), guards routed through a shared goto
 * (zs1/zt1), guards testing a hoisted table local (zj1), `end` computed
 * after the guards (zk1), if/else arm spellings (aa1/aa2), per-arm inline
 * `match = 0` instead of the shared label (aq1), a named extra3 local
 * (ab1), and `continue`/goto loop-back spellings (zo1/zp1).
 * File at 168/346, obj 342.  Probe harness: .scratch/l7-fnfe/.
 *
 * ROUND 196 -- THE BODY IS CLOSED, by arithmetic rather than exhaustion.
 * Shapes 91 retired this function's tail epilogue ordering (sp5-pp reproduces
 * it verbatim AND reaches obj 346 = the reference, where sp6 emits 342) and
 * said to probe the body 1..314 instead, on the assumption the 4-byte
 * shortfall might be a body defect.  Measured, it is not:
 *     BODY 0..314 : ref 315  ours 315  delta  +0   <-- EXACT
 *     TAIL 315..  : ref  31  ours  27  delta  -4   <-- the whole deficit
 * So no body-local edit can supply the 4 bytes.  Per shapes 88 the slack that
 * would pay for one is real (any body length 342..352 pads to the same span
 * 352, i.e. +10 upward) but it is only reachable by moving the no_match stub,
 * which IS the retired tail-ordering decision.
 * The filter-arm `jne` widths at +168/+184/+225 are NOT a source lever: they
 * are forced by rel8 range against the stub's position, and are correct 7/7 on
 * both sides.  Reference stub at +326 gives disp 152/136 -> NEAR 6B and
 * 121/99 -> short 2B; ours at +223 gives 49/37/22 -> all short 2B.  The -4
 * reconciles exactly: two early jcc 12 vs 4 = -8, extra3 arm 2 vs 6 = +4.
 * So the body and the epilogue are ONE finding seen from two ends, and the
 * SCHEDULER-BOUND classification is confirmed from the body side.
 * Residual split over 1..314 (229 bytes): 89 in real hunks (38.9%), 64
 * aligned-but-displaced (27.9%), 76 reloc slots (33.2%).  Remaining body
 * clusters are all closed: entry-guard epilogue inlining (shapes 17), the
 * `xor cl,cl` placement (shapes 85 -- a constant has no definition site to
 * move), the advance-loop bound tests (levers already spent), and the jcc
 * widths above (a consequence, not a fault).
 * Two measurement traps found here: `probe_function.py` is unusable on this
 * function because it compiles standalone and reports obj 352 / aligned
 * 74/118, which do not reproduce in-file; and `instr_diff.py` UNDER-reports
 * alignment (68/118 against a true 87/118) because it does not mask
 * unresolved `[0]` reloc operands against the reference's resolved
 * addresses. */

// FUNCTION: SERVER 0x10016f80
// gm_FindNextFilteredEntity

void* __cdecl gm_FindNextFilteredEntity(void)
{
	unsigned char* list_head;
	unsigned char* end;
	unsigned char match;

	match = 0;
	if (g_entity_type_table == 0) {
		return 0;
	}
	end = (unsigned char*) g_entity_ptr + 0xa900;
	if (g_dynasty_field_4c > 0x100) {
		return 0;
	}
	if (g_dynasty_field_49 != 0) {
		list_head = g_query_filter_base;
		g_dynasty_field_49 = 0;
		if (list_head < end) {
			while (*list_head == 0) {
				list_head += 0xa9;
				g_query_filter_base = list_head;
				if (list_head >= end) {
					break;
				}
			}
		}
		goto candidate;
	} else {
		list_head = g_query_filter_base;
		do {
			list_head += 0xa9;
			g_query_filter_base = list_head;
			if (list_head < end) {
				goto a2;
			}
			return 0;
		a2:
			;
		} while (*list_head == 0);
	}
candidate:
	match = 0;
	if (list_head >= end) {
		return 0;
	}
	for (;;) {
		if (g_dynasty_field_48 != 0) {
			match = 1;
		}
		if (g_filter_extra5 != 0xff) {
			if (*list_head != g_filter_extra5) {
				goto no_match;
			}
			match = 1;
		}
		if (g_query_filter_extra1 != -1) {
			if (*(int*) (list_head + 1) != g_query_filter_extra1) {
				goto no_match;
			}
			match = 1;
		}
		if (g_query_filter_extra2 != 0x7fff) {
			if (*(short*) (list_head + 0x25) != g_query_filter_extra2) {
				goto no_match;
			}
			match = 1;
		}
		if (g_query_filter_extra3 != 0x7fff) {
			if (*(short*) (list_head + 0x27) != g_query_filter_extra3) {
				goto no_match;
			}
			match = 1;
		}
		if (g_query_filter_extra4 != 0xff) {
			match = (*(unsigned char*) ((char*) g_entity_type_table + *list_head + *list_head * 588) ==
			         g_query_filter_extra4);
		}
		goto counted;
	no_match:
		match = 0;
	counted:
		g_dynasty_field_4c++;
		if (match == 0) {
			while (*list_head == 0 || 1) {
				list_head += 0xa9;
				g_query_filter_base = list_head;
				if (list_head >= end) {
					break;
				}
				if (*list_head != 0) {
					break;
				}
			}
		}
		if (list_head >= end) {
			break;
		}
		if (match != 0) {
			break;
		}
	}
	if (match == 0) {
		g_query_filter_base = 0;
		list_head = 0;
	}
	return list_head;
}
