/* gm_AllocSpieler: allocate and initialize an entity from a
 * father/mother pair with random trait generation.
 *
 * KNOWN REAL BUG (2026-09-13, semantic review): the slot[9] else-branch
 * (`arg8 != 2`) stores slot[0x166] (=0), but the reference stores
 * (char)arg8 — at 0x10018cd4 the reference loads arg8 into eax, the
 * 0x10018cde jne skips the gm_RandomMod call, and 0x10018cec stores al.
 * Observable whenever arg8 is neither 2 nor 0. Correct fix
 * (`slot[9] = (char)arg8`) compiles 10 bytes shorter (obj 3689 -> 3679)
 * and costs +393 linked via tail desync — reverted per the link rule.
 * Revisit only with a length-neutral spelling or a resynced tail.
 * (Second finding from the same review — tail log/sprintf order — is the
 * already-recorded +53 lead below.)
 *
 * Real name in the original sources: gm_AllocSpieler from spiel.c.  This is
 * a full C reconstruction of the 3689-byte target: slot scan, slot/refs
 * zeroing, record header init, the debug sprintf/log, the type-0x10 citizen
 * path (ahm_InitRandomEntity-driven field init + trait iteration), the
 * gender/class checks, the father/mother resolution via
 * gm_LookupEntityRecordById, the stat-range interpolation, the per-type
 * finalization (refs scan, id assignment, trait loops, dynasty init) and the
 * final id assignment with the 0x10030b6c counter.
 *
 * Current state (2026-09-13 probe): object 3696 bytes (span; 3689
 * real) against the target's 3689.  The "3681 (-8)" figure above predated
 * later work; retired.  The
 * normalized instruction comparison (.scratch/ndiff.py) aligns 699 of the
 * target's 1056 instructions, in 192 hunks of 1-2 instructions each.  No
 * region is missing: the call sequences agree 55/55, so every statement has
 * a counterpart and the residue is spelling, order and register choice.
 *
 * Statement order is the dominant lever in this function.  msvc6 schedules
 * the record-header stores and the citizen-path field copies in source
 * order, so relocating single statements by one to three lines moves the
 * score by tens of bytes at a time.  A hill-climb over single-statement
 * relocations took the function from 734 to 858; it has converged, so no
 * remaining single move improves the score.
 *
 * Levers that landed (each measured, score in parentheses):
 *   - the 0x82 trait bump reads through the volatile alias inside the store
 *     expression rather than through a separate `trait` local (734 -> 780).
 *     The extra local defeated msvc6's mov/add/mov and cost a spill slot.
 *   - `slot[2] = type` sinks below the two zero stores at 0x170 and 0x16c,
 *     which is the target's order at 0x100188f9 (780 -> 781).
 *   - `ref = father + 0x68` is computed before the 0x58 increment, matching
 *     the target's `lea ecx,[edx+0x68]` ahead of `inc al` (781 -> 782).
 *   - in the citizen path `slot[9] = ent[0xd5]` precedes
 *     `slot[0x164] = ent[0xd4]` (782 -> 785), and 2026-09-13 (round 110)
 *     groups the three byte-copies (slot[9]/[0x164]/[0xc]) ahead of the
 *     three strcpys: object 736/1310 -> 740/1314, linked 2861 -> 2857
 *     (-4, confirmed after full rebuild).  Kept.
 *   - 2026-09-13 (round 121): father-wins else-branch copies in
 *     0xc/0x1d0/0x217 order (was 0x217/0xc/0x1d0), matching the
 *     reference's store sequence — object 740/1314 -> 741/1315,
 *     linked 2857 -> 2856 (-1).  Kept for the byte.  (The mother
 *     branches were already in that order — no twin change existed.)
 *   - 2026-09-13 (round 128): per-trait selection tests best_mother
 *     first (was best_father-first) — object +7/+7, aligned -2,
 *     linked 2856 -> 2848 (-8, confirmed after full rebuild).
 *     Position beat alignment again.  Kept for the bytes.
 *   - 2026-09-14 (round 174): two statement moves recovered by
 *     comparing the reference's whole top-level block order against
 *     this file (the method of shapes section 84).  Object 748/1322
 *     -> 766/1338, aligned 652 -> 662, rebrew test 985 -> 1004, all
 *     span-neutral; linked 8894 -> 8871 (-23, confirmed after a full
 *     clean rebuild).
 *       (1) `slot[0xd] = 1` hoisted ABOVE the parent-wins chain: the
 *           reference stores it at 0x10018d5d, before the chain.  The
 *           chain reads `mother+0xd`/`father+0xd`, never `slot[0xd]`.
 *       (2) the [0x124]/[0x128] pair sunk BELOW the 14-iteration trait
 *           loop.  This one is not merely cosmetic: [0x124]'s value
 *           comes from `gm_RandomFloat01()`, and the reference draws
 *           the loop's 14 samples first (`mov ebx,0xe` at 0x10018e21,
 *           back-edge `jne 0x10018e26`) and only then draws this one
 *           at 0x10018e77, storing at 0x10018ea7/0x10018eb3.  Our
 *           order drew it first, so the RNG sequence differed from the
 *           original program's.  The move corrects the behaviour as
 *           well as the bytes.
 *     The no-parent twin already had its own [0x124]/[0x128] pair
 *     after its loop (0x1001931b); that asymmetry is what exposed the
 *     difference.  A third divergence — the reference calls
 *     RandomFloat01 inside the 5-iteration selection loop — is a
 *     scheduling artifact, not a source-level per-iteration draw:
 *     sinking `acc` into that loop scores 366/3689.  Do not retry it.
 *   - the idx>=6 selector must be the addition form,
 *     `0x3c + (idx < 6 ? 0x86 : 0)`, which emits the target's
 *     setge / dec / and 0x86 / add 0x3c.  The subtraction spelling
 *     `0xc2 - (idx >= 6 ? 0x86 : 0)` emits setl / sub instead (the earlier
 *     note here had the two forms the wrong way round); switching it takes
 *     the alignment from 616 to 617 of 1056 and the object from 3698 back to
 *     3694.
 *   - the record-header stores are transcribed into the order the target
 *     *emits*, not the order that reads naturally: [0x170] before [0x16c],
 *     [0x215] after [0x210], [0x218]/slot[8] after the 0x2637 log, plus
 *     (CORRECTED round 178 -- the tail claim that stood here was wrong.
 *     The reference's actual sequence, read off 0x100189be-0x100189f4, is
 *     slot[8], [0xa], [0x166], [0x165], [0x1f4], [0x190], [0x194], [0xd],
 *     [0x18c], [0x20c]: [0xa] is SECOND at 0x100189c4 and [0x20c] is LAST
 *     at 0x100189f4, where the old note put [0xa] last and [0x20c] third.
 *     Our source still has those two swapped.  Applying the true order is
 *     size-neutral and splits the rulers -- aligned 662 -> 664 but both
 *     byte rulers -43.  LINK-TESTED round 178: +43 (8871 -> 8914), so the
 *     byte rulers were right and the aligned gain was noise.  Our swapped
 *     order is kept deliberately; do not "fix" it to match the reference.)
 *     Also
 *     `ref = father + 0x68` ahead of the father 0x58 increment.  Measured with
 *     scripts/probe_function.py --va 0x10018850: 697 -> 736 of 3689 honest,
 *     matched-reloc 1277 -> 1310, aligned 646 -> 654 of 1056, object 3696 and
 *     real body 3689 unchanged (size-neutral on both).
 *
 * Next, and the largest single-file delta found but NOT applied here because
 * it is not size-neutral: the target calls
 * LogMessageInternal(file, 0x2888, work, 8) *after* the final
 * sprintf(work, s_fmt_playerid_10031570, ...), not before it -- see the
 * 0x286c / 0x2888 / sprintf sequence at 0x1001962c..0x10019690, where the
 * `jne` from `cmp idx,0xffff` jumps over the 0x286c log straight into the
 * sprintf.  Moving only that call (and leaving the 0x286c guard ahead of the
 * sprintf) measures aligned 646 -> 652 and real body 3689 -> 3687, and
 * combined with the header transcription above aligned 658.  It also changes
 * which string the 0x2888 record contains, so it is a behaviour change
 * *towards* the reference: the current source logs the SpID buffer, the
 * target logs the PlayerID buffer.  Closed 2026-09-13: the reference order
 * is confirmed (0x10019636 `jne` skips the 0x286c log, `sprintf` at
 * 0x10019666, then the 0x2888 log at 0x1001967c), and applying it measures
 * obj 3689 -> 3687, match 973 -> 915, linked +53 (2861 -> 2914).  Reverted:
 * the local alignment gain trades against the link, so this lead is spent.
 *
 * Measured dead ends, all reverted (score from the 859 base unless noted):
 *   - moving `work[0x3fc]` in the declaration list, to chase the scratch area
 *     sitting at esp+0x40 here against the target's esp+0x3c: msvc6 assigns
 *     the slot independently of declaration order.  Two uses stay at 0x40 and
 *     the alignment is unchanged at 617 either way.
 *   - a local copy of `arg8` (`n = arg8`) before `if (n == 2)`, to stop msvc6
 *     folding the `gm_RandomMod` argument to the constant 2 (the target pushes
 *     the register, we push the immediate).  The fold survives and the
 *     alignment falls 617 -> 616.
 *   - every remaining `_ftol` site as a plain `(int)` cast: 473 / 471 / 470
 *     for the three trait-selection sites and 547 for the age loop.  Each
 *     saves the `sub esp,8` / `fstp qword ptr [esp]` pair but costs about
 *     380 matched bytes, so the explicit calls stay.
 *   - merging `colv` and `rowv` into one local, or into any of `i`, `j`,
 *     `rnd`, `n`, `idx`, `best_father`, `best_mother`: 608 to 652.  The
 *     object shrinks toward 3684 but the sympathy loops lose their
 *     single-base addressing.
 *   - `acc` as `double` instead of `float`: 614.
 *   - volatile reads on the four parent-sympathy stores, to force the
 *     target's per-use `xor eax,eax` + `mov ax` reloads: 627.
 *   - the no-parent selector ternaries rewritten in the subtraction form
 *     that worked for idx>=6: 631 to 745.  Those sites already emit the
 *     target's shape.
 *   - `type_entry == 1` inverted into a guard clause in the location block:
 *     measured 770 at the time and reverted, but re-tested 2026-09-12 after the
 *     FPU and clamp fixes and it is the reference's shape after all (715 ->
 *     718, and the emitted branch is now the target's `je` to an out-of-line
 *     0x170 store).  Do not trust the 770 figure; it predates the current
 *     source.  A rejection is only valid for the compilation it was measured on.
 *   - `gm_RandomMod((unsigned short) arg8)` spelled as `gm_RandomMod(2)`:
 *     601.  The constant defeats the target's register reuse.
 *   - the stat-modifier table index rewritten to put `i` first: 591.
 *   - CFLAGS sweep over 20 variants (/G3, /G4, /G5, /Gd, /Oy and
 *     combinations): every one scores identically to the current
 *     /O2 /Gd /Oa; the FPU forms (/Op) and /G6 both regress.
 *
 * `rebrew prove` cannot certify this function.  Both a 600-second and a
 * 2400-second run with loop bounds 10 and 3 report no terminal states for
 * the original binary: the two 0x300-iteration sympathy loops and the
 * 0x300-iteration slot scan explode the path space well before any exit is
 * reached.  Slice proving would need per-block start and end offsets.
 *
 * Remaining delta: 8 bytes short, spread over ~192 one- and two-instruction
 * hunks.  The prologues match exactly (`sub esp, 0x41c` on both sides), so
 * this is not a frame-size difference.
 *
 * `/Ow` is load-bearing in the metadata CFLAGS (`/DREBREW_ALLOW_NAKED
 * /O2 /Gd /Oa /Ow` in `src/rebrew-functions.toml`), which is what both the
 * tools and the CMake build read (`rebrew cmake-flags`; there is no inline
 * `// CFLAGS:` line in this file).  The annotation used to carry
 * `/O2 /Gd /Oa` alone while the metadata carried `/Oa /Ow`, so every
 * measurement recorded above (all made through `rebrew test`/the metadata)
 * described a build the tree was not producing: the linked function was 1047
 * instructions against the target's 1056 and matched 914 of 3689 bytes,
 * against 1054 and 1194 once the two agreed.  Note that CMake bakes
 * `COMPILE_FLAGS` in at configure time, so editing the metadata CFLAGS needs
 * `cmake -S . -B build`, not just a rebuild. */

// FUNCTION: SERVER 0x10018850

#include <stdlib.h>
#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

#pragma intrinsic(memcpy, memset, strlen, strcpy)

extern int g_next_object_id; /* 0x10030b6c */
extern int g_citizen_count; /* 0x10035434 */
extern double g_dbl_const_688; /* 0x10025688 */
extern double g_dbl_const_6d0; /* 0x100256d0 */
extern double g_dbl_const_7d8; /* 0x100257d8 */
extern double g_dbl_const_810; /* 0x10025810 */
extern float g_dbl_const_f88; /* 0x10025f88 - fmul dword, not qword */
extern double g_dbl_const_f90; /* 0x10025f90 */
extern double g_dbl_const_f98; /* 0x10025f98 */
int __cdecl gm_EntityClassCheck(int);
int __cdecl gm_IsInRange(int);
int __cdecl gm_RandomMod(unsigned short);
double __cdecl gm_RandomFloat01(void);
float __cdecl gm_RandomQuadratic(void);
char* __cdecl ahm_InitRandomEntity(void);
char __cdecl gm_RandomStatModifier(char);
int __cdecl gm_MapEntityStatRange(int);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl ahm_ResetEntityState(char*);
void __cdecl InitNewDynastyEntity(int, void*, unsigned short, void*);
int __cdecl _ftol(void);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl LogMessageInternal(char*, int, char*, int);

static char s_fmt_spid_100315e4[] = "----->SpID= %i playermode= %i";
static char s_fmt_playerid_10031570[] =
    "----->PlayerID= %i PlayerName= %s";
static char s_arr_overflow_10031604[] = "gm_AllocSpieler: array overflow...";
static char s_bug_10031594[] = "gm_AllocSpieler: bug";
static char s_family_overflow_100315ac[] =
    "gm_AllocSpieler(): gm_CurrentHumanFamilyCount overflow";
static char s_file_spiel_c_10031004[] =
    "D:\\Develop\\DieGildeAddOn\\game\\spiel.c";

unsigned short __cdecl gm_AllocSpieler(int type, int mother_id, int gender, int arg4, int location, int arg6, int arg7, int arg8)
{
	char* slot;
	char* mother;
	char* father;
	char work[0x3fc];
	int idx;
	int j;
	int i;
	int rnd;
	int n;
	int best_father;
	int best_mother;
	float acc;
	float* src;
	float* dst;
	int colv;
	int rowv;

	/* find a free slot: first by id word == 0xffff, then by state byte == 0xf */
	for (idx = 0; idx < 0x300; idx++) {
		if (*(unsigned short*) (0x100358a0 + idx * 0x21c) == 0xffff) {
			break;
		}
	}
	if (idx == 0x300) {
		for (idx = 0; idx < 0x300; idx++) {
			if (*(unsigned char*) (0x100358a2 + idx * 0x21c) == 0xf) {
				break;
			}
		}
	}
	if (*(unsigned char*) (0x100358a2 + idx * 0x21c) == 0xf) {
		g_citizen_count--;
	}
	if (idx == 0x300) {
		LogMessageInternal(s_file_spiel_c_10031004, 0x2614,
		                   s_arr_overflow_10031604, 1);
		return 0xffff;
	}
	slot = (char*) 0x100358a0 + idx * 0x21c;
	memset(slot, 0, 0x21c);
	/* The reference stores 0xffff here before the -1 fills.  msvc6
	 * dead-store-eliminates it against the id store further down unless the
	 * id store is addressed so the two are not provably the same location:
	 * with `*(unsigned short*) (0x100358a0 + idx * 0x21c) = idx` below, both
	 * stores survive (spelling that store through `slot` removes this one).
	 * The reference's own disassembly keeps both, so the scaled-index form is
	 * the reconstruction, not a trick.
	 *
	 * Measured with both stores: object 3698 against the target's 3689 and
	 * scripts/seqdiff.py aligning 616 of 1056 instructions, against 3694 /
	 * 614 with this store dropped.  The object is further from the target's
	 * size than the version without it (which is 5 B over rather than 9),
	 * because the remaining ~11 B of the target's code is still missing; the
	 * positional score falls 924 -> 583 for the offset-shift reason, so
	 * `rebrew test`'s score cannot judge this function.
	 *
	 * The -1 fills are addressed off the scaled index, not off slot: the
	 * reference keeps idx * 0x21c live in edx and reuses it as the base for
	 * both. */
	*(unsigned short*) slot = 0xffff;
	*(int*) (0x100358a4 + idx * 0x21c) = -1;
	/* record header init + debug sprintf/log */
	*(unsigned short*) (0x100358a0 + idx * 0x21c) = (unsigned short) idx;
	*(int*) (slot + 0x170) = 0;
	*(int*) (slot + 0x16c) = 0;
	memset((void*) (0x100358fc + idx * 0x21c), 0xff, 0x20);
	slot[2] = (char) type;
	*(int*) (slot + 0x1f0) = 0;
	g_citizen_count++;
	*(int*) (slot + 0x210) = -1;
	slot[0x215] = 0;
	sprintf(work, s_fmt_spid_100315e4, g_next_object_id, type);
	slot[0x216] = 0;
	slot[0x217] = 0;
	*(int*) (slot + 4) = g_next_object_id;
	g_next_object_id++;
	*(int*) (slot + 0x1e4) = 0x3f800000; /* 1.0f */
	slot[0x164] = (char) arg6;
	LogMessageInternal(s_file_spiel_c_10031004, 0x2637, work, 8);
	slot[0x218] = 1;
	slot[8] = 0x64;
	*(int*) (slot + 0x20c) = -1;
	slot[0x166] = 0;
	slot[0x165] = (char) arg7;
	slot[0x1f4] = 0;
	*(int*) (slot + 0x190) = 4;
	*(int*) (slot + 0x194) = 0;
	slot[0xd] = 1;
	*(int*) (slot + 0x18c) = -1;
	*(unsigned short*) (slot + 0xa) = (unsigned short) arg4;
	if (slot[2] == 3 || slot[2] == 0x10 || slot[2] == 0x13) {
		*(int*) (slot + 0x1e8) = 1;
		slot[0xd] = 2;
	}
	if (slot[2] == 0x10) {
		/* entity type 0x10: citizen with randomized traits from ahm */
		char* ent;

		ent = ahm_InitRandomEntity();
		slot[2] = 3;
		if (ent != (char*) 0) {
			*(int*) (slot + 0x1f0) = *(int*) ent;
			rnd = gm_RandomMod(8) & 0xffff;
			slot[9] = ent[0xd5];
			slot[0x164] = ent[0xd4];
			slot[0xc] = ent[0xd6];
			strcpy(slot + 0x30, ent + 4);
			strcpy(slot + 0x40, ent + 0x14);
			strcpy(slot + 0x1f4, ent + 0xd7);
			*(int*) (slot + 0x80) = *(int*) (ent + 0x24);
			*(char*) (slot + 0x84) = ent[0x28];
			memcpy(slot + 0x88, ent + 0x2c, 0xa8);
			*(unsigned short*) (slot + 0x50) =
			    (unsigned short) (*(int*) 0x1003542c);
			(*(int*) 0x1003542c)++;
			*(int*) (slot + 0x1c) = 0x447a0000; /* 1000.0f */
			*(float*) (slot + 0x1d0) =
			    (float) (gm_RandomFloat01() * *(float*) 0x100256b0) +
			    *(float*) 0x10025714;
			*(float*) (slot + 0x14) =
			    (float) (gm_RandomQuadratic() *
			             *(float*) 0x100256c8) +
			    *(float*) 0x100256c4;
			*(int*) (slot + 0x20) = 0x41400000; /* 12.0f */
			n = (int) (*(float*) (slot + 0x1c) *
			           g_dbl_const_810);
			rnd = gm_RandomMod((unsigned short) n) & 0xffff;
			*(float*) (slot + 0x18) = *(float*) (slot + 0x1c);
			*(float*) (slot + 0x10) =
			    (float) (*(float*) (slot + 0x1c) *
			                 *(float*) 0x100256b8 +
			             (double) (unsigned short) rnd -
			             *(float*) (slot + 0x1c) *
			                 *(float*) 0x100256b4);
			if (arg4 < 2) {
				slot[0x217] = 0x58;
			} else if (idx < 4) {
				slot[0x217] = 0x5c;
			}
			slot[0x217] = (char) (0x3c + (idx < 6 ? 0x86 : 0));
			if ((double) *(unsigned short*) (slot + 0xa) >
			    *(float*) (slot + 0x20)) {
				acc = *(float*) (slot + 0x1c);
				for (n = (int) ((double) *(unsigned short*) (slot + 0xa) -
				               *(float*) (slot + 0x20));
				     n > 0; n--) {
					acc = acc - *(float*) (slot + 0x14) +
					      *(float*) (slot + 0x14) / acc;
				}
				if (acc <= *(float*) 0x100256a0) {
					acc = *(float*) 0x100256a0;
				}
				*(float*) (slot + 0x1c) = acc;
				return *(unsigned short*) slot;
			}
			return *(unsigned short*) slot;
		}
		/* ahm_InitRandomEntity returned NULL: fall through */
	}
	if (slot[2] == 0x15 || slot[2] == 0x16) {
		InitNewDynastyEntity(slot[2] & 0xff, (void*) mother_id, (unsigned short) arg4,
		                     slot);
		return *(unsigned short*) slot;
	}

	/* building-type location field */
	if (location != 0) {
		unsigned char type_byte;
		unsigned char type_entry;

		type_byte = *(unsigned char*) location;
		type_entry = *(*(unsigned char**) 0x100a8c30 + type_byte * 0x24d);
		if (type_entry != 1) {
			if (type_entry > 3 && type_entry < 0x17 && type_entry != 0xa && type_entry != 0xf && type_entry != 0x11) {
				*(int*) (slot + 0x16c) = location;
			}
		} else {
			*(int*) (slot + 0x170) = location;
		}
	}
	slot[0xd] = (char) ((slot[0x166] != 0) + 1);
	if (type != 6 && type != 7 && type < 0xa) {
		slot[0x1b0] = (char) gm_RandomMod(8);
	}
	if (arg8 == 2) {
		slot[9] = (char) gm_RandomMod((unsigned short) arg8);
	} else {
		slot[9] = slot[0x166];
	}
	if (type < 4 || type == 0xb) {
		if (arg7 != 0) {
			n = gm_EntityClassCheck(arg7);
			if (n != 2) {
				slot[9] = (char) n;
			}
		} else if (arg6 != 0) {
			n = gm_IsInRange(arg6);
			if (n != 2) {
				slot[9] = (char) n;
			}
		}
	}
	mother = (char*) gm_LookupEntityRecordById(mother_id);
	father = (char*) gm_LookupEntityRecordById(arg4);
	if (mother == (char*) 0 || father == (char*) 0) {
		/* no usable parent pair: generate the traits from the type tables */
		slot[0x164] = (char) arg6;
		slot[0x166] = 0;
		slot[0x165] = (char) arg7;
		n = gm_MapEntityStatRange(arg6 & 0xff);
		rnd = gm_RandomMod(8) & 0xffff;
		/* four-way class/rank pick (reference 0x10019228..0x100192b3).
		 * The outer test is slot[2] == 3; each arm then splits on the
		 * stat range being 0xb/0xc.  Each leaf is spelled "base +
		 * (rnd < K ? V : 0)", which is what emits the reference's
		 * setge / dec / and V / add base; the equivalent ">= K ? 0 : V"
		 * compiles to setl / and ~V instead. */
		if (slot[2] != 3) {
			if (n == 0xb || n == 0xc) {
				slot[0x217] = (char) (0x56 + (rnd < 4 ? 0xf8 : 0));
			} else {
				if (rnd < 3) {
					slot[0x217] = 0x3e;
				} else {
					slot[0x217] = (char) (0x4e + (rnd < 6 ? 8 : 0));
				}
			}
		} else {
			if (n == 0xb || n == 0xc) {
				if (rnd < 3) {
					slot[0x217] = 0x58;
				} else {
					slot[0x217] =
					    (char) (0xc2 + (rnd < 6 ? -0x66 : 0));
				}
			} else {
				if (rnd < 3) {
					slot[0x217] = 0x3c;
				} else {
					slot[0x217] = (char) (0x58 + (rnd < 6 ? 4 : 0));
				}
			}
		}
		/* 14-iteration trait interpolation from the trait table */
		dst = (float*) (slot + 0x88);
		src = (float*) (0x10025818 + n * 0x70);
		for (i = 0xe; i != 0; i--) {
			dst[0] = (float) (gm_RandomFloat01() * (double) (src[1] - src[0]) +
			                  src[0]);
			src += 2;
			dst += 3;
			dst[-1] = (float) ((double) (gm_RandomMod(0xa) & 0xffff) +
			                   g_dbl_const_f98);
		}
		*(float*) (slot + 0x124) =
		    (float) ((gm_RandomFloat01() + g_dbl_const_688) *
		             g_dbl_const_f90);
			/* KNOWN BUG, deliberately left in place (round 178).
			 * This line belongs INSIDE the loop above: the reference
			 * emits fld [esi-0xc] / fmul [0x100256d0] / fstp [esi-8]
			 * at 0x1001930d-0x10019316, before the back-edge jne at
			 * 0x10019319.  It is indented as if it were in the body
			 * but closes outside it (introduced malformed in
			 * 63fe71e5), so it runs once instead of fourteen times.
			 * Moving it inside is CORRECT and makes the instruction
			 * count exact (1054 -> 1056 against the reference's
			 * 1056) -- and costs +420 linked bytes (8871 -> 9291),
			 * because our surrounding schedule then diverges.
			 * Third instance of correctness and byte-matching
			 * pulling apart; see the slot[9] note above and
			 * docs/behavioral-verdicts.md.  Fix it when the
			 * function's schedule is close enough to absorb it. */
			dst[-2] = (float) ((double) dst[-3] * g_dbl_const_6d0);
		*(float*) (slot + 0x128) =
		    (float) ((double) *(float*) (slot + 0x124) *
		             g_dbl_const_6d0);
		/* symmetric sympathy-matrix init: both [j][id] and [id][j] */
		for (j = 0; j < 0x300; j++) {
			colv = *(volatile unsigned short*) slot + j * 0x300;
			*(char*) (0x1014d8e0 + colv) = 0;
			*(char*) (0x100a9820 + colv) =
			    (char) (gm_RandomMod(0x40) - 0x20);
			rowv = ((*(volatile unsigned short*) slot * 3) << 8) + j;
			*(char*) (0x100a9820 + rowv) =
			    (char) (gm_RandomMod(0x40) - 0x20);
			*(char*) (0x1014d8e0 + rowv) = 0;
		}
		slot[0xc] = (char) gm_RandomMod(2);
		*(float*) (slot + 0x1d0) =
		    (float) (gm_RandomFloat01() * *(float*) 0x100256b0) +
		    *(float*) 0x10025714;
		goto stat_modifiers;
	}
	slot[0xd] = 1;
	if (mother[2] == 6 || mother[2] == 7 || mother[2] == 5) {
		slot[0xc] = mother[0xc];
		*(int*) (slot + 0x1d0) = *(int*) (mother + 0x1d0);
		slot[0x217] = mother[0x217];
	} else if (father[2] == 6 || father[2] == 7 || father[2] == 5) {
		slot[0xc] = father[0xc];
		*(int*) (slot + 0x1d0) = *(int*) (father + 0x1d0);
		slot[0x217] = father[0x217];
	} else if (*(unsigned char*) (mother + 0xd) >=
	           *(unsigned char*) (father + 0xd)) {
		slot[0xc] = mother[0xc];
		*(int*) (slot + 0x1d0) = *(int*) (mother + 0x1d0);
		slot[0x217] = mother[0x217];
	} else {
		slot[0xc] = father[0xc];
		*(int*) (slot + 0x1d0) = *(int*) (father + 0x1d0);
		slot[0x217] = father[0x217];
	}
	/* 14-iteration parent trait interpolation; the 0x88/0x84/0x80 triple is
	 * float, not byte: the reference stores them with fstp dword */
	for (i = 0; i < 0xe; i++) {
		double rnd01;

		rnd01 = gm_RandomFloat01();
		*(float*) (slot + 0x88 + i * 0xc) =
		    (float) ((g_dbl_const_7d8 - rnd01) *
		                 (double) *(float*) (father + 0x88 + i * 0xc) +
		             rnd01 * (double) *(float*) (mother + 0x88 + i * 0xc));
		*(float*) (slot + 0x90 + i * 0xc) =
		    (float) ((double) (gm_RandomMod(0xa) & 0xffff) +
		             g_dbl_const_f98);
		*(float*) (slot + 0x8c + i * 0xc) =
		    (float) ((double) *(float*) (slot + 0x88 + i * 0xc) *
		             g_dbl_const_6d0);
	}
	/* The reference draws this pair at 0x10018e77, AFTER the 14-iteration
	 * trait loop -- the no-parent twin at 0x1001931b already sits after
	 * its own loop, and that asymmetry is what exposed the difference.
	 * Defined above the loop, [0x124] pins its schedule across it. */
	*(float*) (slot + 0x124) =
	    (float) ((gm_RandomFloat01() + g_dbl_const_688) *
	             g_dbl_const_f90);
	*(float*) (slot + 0x128) =
	    (float) ((double) *(float*) (slot + 0x124) *
	             g_dbl_const_6d0);
	/* find the best trait index of each parent (quirky +1 indexing) */
	best_mother = 0;
	best_father = 0;
	for (i = 0; i < 4; i++) {
		if (*(unsigned char*) (father + 0x81 + i) >
		    *(unsigned char*) (father + 0x80 + best_father)) {
			best_father = i + 1;
		}
		if (*(unsigned char*) (mother + 0x81 + i) >
		    *(unsigned char*) (mother + 0x80 + best_mother)) {
			best_mother = i + 1;
		}
	}
	/* per-trait selection: father best / mother best / interpolation */
	acc = (float) gm_RandomFloat01();
	for (i = 0; i < 5; i++) {
		if (i == best_mother) {
			slot[0x80 + i] = (char) (
			    (double) *(unsigned char*) (mother + 0x80 + i) *
			    *(float*) 0x100256b0);
		} else if (i == best_father) {
			slot[0x80 + i] = (char) (
			    (double) *(unsigned char*) (father + 0x80 + i) *
			    *(float*) 0x100256b0);
		} else {
			slot[0x80 + i] = (char) (
			    ((g_dbl_const_7d8 - (double) acc) *
			         (double) *(unsigned char*) (father + 0x80 + i) +
			     (double) acc *
			         (double) *(unsigned char*) (mother + 0x80 + i)) *
			    *(float*) 0x100256b0);
		}
	}
	/* no gm_RandomMod(2) / gm_RandomFloat01 pair here: on the two-parent
	 * path 0xc and 0x1d0 were already copied from whichever parent won the
	 * checks above (reference 0x10018d96..0x10018df9).  The randomized pair
	 * belongs only to the no-parent path at 0x1001939a. */
	/* record both parents and hook the child into their ref arrays */
	*(int*) (slot + 0x64) = gender;
	*(int*) (slot + 0x60) = mother_id;
	*(int*) (slot + 0x68) = -1;
	*(int*) (slot + 0x6c) = -1;
	*(int*) (slot + 0x70) = -1;
	*(int*) (slot + 0x74) = -1;
	*(int*) (slot + 0x78) = -1;
	for (i = 3; i < 8; i++) {
		int ref;

		ref = *(int*) (father + i * 4 + 0x5c);
		if (ref == -1) {
			*(int*) (father + i * 4 + 0x5c) = *(int*) (slot + 4);
			break;
		}
		if (((char*) gm_LookupEntityRecordById(ref))[2] == 0xf) {
			*(int*) (father + i * 4 + 0x5c) = *(int*) (slot + 4);
			break;
		}
	}
	for (i = 3; i < 8; i++) {
		int ref;

		ref = *(int*) (mother + i * 4 + 0x5c);
		if (ref == -1) {
			*(int*) (mother + i * 4 + 0x5c) = *(int*) (slot + 4);
			break;
		}
		if (((char*) gm_LookupEntityRecordById(ref))[2] == 0xf) {
			*(int*) (mother + i * 4 + 0x5c) = *(int*) (slot + 4);
			break;
		}
	}
	*(int*) (slot + 0x7c) = 0;
	if (mother[2] == 6 || mother[2] == 7 || mother[2] == 5) {
		*(unsigned short*) (slot + 0x50) = *(unsigned short*) (mother + 0x50);
		slot[0x58] = (char) (mother[0x58] + 1);
		*(int*) (slot + 0x54) = *(int*) (mother + 0x54);
	} else {
		*(unsigned short*) (slot + 0x50) = *(unsigned short*) (father + 0x50);
		slot[0x58] = (char) (father[0x58] + 1);
		*(int*) (slot + 0x54) = *(int*) (father + 0x54);
	}
	*(int*) (slot + 0x1c) = 0x447a0000; /* 1000.0f */
	*(float*) (slot + 0x14) =
	    (float) ((gm_RandomQuadratic() * *(float*) 0x100256c8 +
	              *(float*) 0x100256c4) *
	                 g_dbl_const_f88 +
	             (*(float*) (father + 0x14) + *(float*) (mother + 0x14)) *
	                 g_dbl_const_810);
	rnd = gm_RandomMod((unsigned short) (int) (*(float*) (slot + 0x1c) *
	                                           g_dbl_const_810)) &
	      0xffff;
	*(int*) (slot + 0x20) = 0x41400000; /* 12.0f */
	*(float*) (slot + 0x18) = *(float*) (slot + 0x1c);
	*(float*) (slot + 0x10) =
	    (float) (*(float*) (slot + 0x1c) * *(float*) 0x100256b8 +
	             (double) (unsigned short) rnd - *(float*) (slot + 0x1c) *
	                                *(float*) 0x100256b4);
	/* Symmetric sympathy-matrix init: both [j][id] and [id][j].  Each pair of
	 * stores shares one index local, which is what makes msvc6 emit the
	 * reference's single-base "mov byte ptr [edi + <table>]" form instead of
	 * recomputing the address for every store.  Both reads must stay
	 * volatile; the reference reloads `*(unsigned short*) slot` once per
	 * iteration (two `xor eax,eax; mov ax,[ebp]` pairs at 0x10019342) and
	 * only a volatile read prevents msvc6 from keeping it in a register.
	 * The sibling loop in the no-parent path above takes the same shape: the
	 * reference reloads there too (0x10018f12..0x10018f41), which an earlier
	 * note here denied.  Its four writes were inline, so they had to be given
	 * the two index locals first. */
	for (j = 0; j < 0x300; j++) {
		colv = *(volatile unsigned short*) slot + j * 0x300;
		*(char*) (0x1014d8e0 + colv) = 0;
		*(char*) (0x100a9820 + colv) =
		    (char) (gm_RandomMod(0x40) - 0x20);
		rowv = ((*(volatile unsigned short*) slot * 3) << 8) + j;
		*(char*) (0x100a9820 + rowv) =
		    (char) (gm_RandomMod(0x40) - 0x20);
		*(char*) (0x1014d8e0 + rowv) = 0;
	}
	/* mutual sympathy between the new entity and each parent.  Unlike the two
	 * loops above, these reads are plain: the unit compiles with /Oa, and
	 * under a no-alias assumption the volatile only cost msvc6 the reloads
	 * the reference actually takes. */
	*(char*) (0x100a9820 + ((*(unsigned short*) slot * 3) << 8) +
	          *(unsigned short*) mother) =
	    (char) (0x7f - gm_RandomMod(0x20));
	*(char*) (0x100a9820 + ((*(unsigned short*) mother * 3) << 8) +
	          *(unsigned short*) slot) =
	    (char) (0x7f - gm_RandomMod(0x20));
	*(char*) (0x100a9820 + ((*(unsigned short*) slot * 3) << 8) +
	          *(unsigned short*) father) =
	    (char) (0x7f - gm_RandomMod(0x20));
	*(char*) (0x100a9820 + ((*(unsigned short*) father * 3) << 8) +
	          *(unsigned short*) slot) =
	    (char) (0x7f - gm_RandomMod(0x20));
	/* stat modifier loop from the type tables; shared with the no-parent
	 * path, which reaches it via the goto above */
stat_modifiers:
	if (arg7 != 0 && arg6 == 0) {
		for (i = 0; i < 5; i++) {
			slot[0x80 + i] = (char) gm_RandomStatModifier(
			    *(unsigned char*) (0x10030dda +
			                       *(unsigned char*) (slot + 0x165) * 6 +
			                       i));
		}
	} else {
		for (i = 0; i < 5; i++) {
			slot[0x80 + i] = (char) gm_RandomStatModifier(
			    *(unsigned char*) (0x10030ba0 +
			                       *(unsigned char*) (slot + 0x164) * 6 +
			                       i));
		}
	}

	*(int*) (slot + 0x64) = gender;
	if (type != 6 && type != 7) {
		slot[0xd] = *(char*) (0x10030ba5 +
		                      *(unsigned char*) (slot + 0x164) * 6);
	}
	memset(slot + 0x5c, 0xff, 0x20);
	if (father != (char*) 0) {
		int* ref;

		ref = (int*) (father + 0x68);

		slot[0x58] = (char) (father[0x58] + 1);
		for (i = 3; i < 8; i++) {
			if (*ref == -1) {
				*(int*) (father + i * 4 + 0x5c) = *(int*) (slot + 4);
				break;
			}
			ref++;
		}
	}
	if (type == 6 || type == 7 || type == 5) {
		/* The reference loads the family counter once and reuses it for the
		 * bound test and the update: `mov eax,[0x10035430]; cmp eax,0x10;
		 * jl ...; mov edx,eax; or dh,0x80; inc eax; mov [ebp+0x50],dx;
		 * mov [0x10035430],eax` at 0x100194c5.  Reading the global twice
		 * emitted a 16-bit load for the store and a second 32-bit load for
		 * the increment. */
		n = *(int*) 0x10035430;
		if (n >= 0x10) {
			LogMessageInternal(s_file_spiel_c_10031004, 0x27f0,
			                   s_family_overflow_100315ac, 1);
			return 0xffff;
		}
		*(unsigned short*) (slot + 0x50) = (unsigned short) (n | 0x8000);
		*(int*) 0x10035430 = n + 1;
	} else if (type >= 0xa) {
		*(unsigned short*) (slot + 0x50) = 0x7fff;
	} else {
		/* Same single-load shape on the other counter (0x100194d8). */
		n = *(int*) 0x1003542c;
		*(unsigned short*) (slot + 0x50) = (unsigned short) n;
		*(int*) 0x1003542c = n + 1;
	}
	slot[0x58] = 1;
	*(int*) (slot + 0x20) = 0x41400000; /* 12.0f */
	*(int*) (slot + 0x1c) = 0x447a0000; /* 1000.0f */
	*(int*) (slot + 0x18) = *(int*) (slot + 0x1c);
	*(float*) (slot + 0x14) =
	    (float) (gm_RandomQuadratic() * *(float*) 0x100256c8) +
	    *(float*) 0x100256c4;
	rnd = gm_RandomMod((unsigned short) (int) (*(float*) (slot + 0x1c) *
	                                           g_dbl_const_810)) &
	      0xffff;
	*(float*) (slot + 0x10) =
	    (float) (*(float*) (slot + 0x1c) * *(float*) 0x100256b8 +
	             (double) (unsigned short) rnd - *(float*) (slot + 0x1c) *
	                                *(float*) 0x100256b4);
	/* The reference draws gm_RandomMod(0x10) twice here, back to back and
	 * both ahead of the stat guard (0x1001956a and 0x10019574).  Neither
	 * result is read: the call at 0x10019574 has no `and eax,0xffff` after
	 * it, so its value is discarded, and reading the two globals in two
	 * expressions for one draw put one after the guard instead. */
	gm_RandomMod(0x10);
	gm_RandomMod(0x10);
	if ((float) *(unsigned short*) (slot + 0xa) > *(float*) (slot + 0x20)) {
		acc = *(float*) (slot + 0x1c);
		for (n = (int) ((float) *(unsigned short*) (slot + 0xa) -
		               *(float*) (slot + 0x20));
		     n > 0; n--) {
			acc = acc - *(float*) (slot + 0x14) +
			      *(float*) (slot + 0x14) / acc;
		}
		if (acc <= *(float*) 0x100256a0) {
			acc = *(float*) 0x100256a0;
		}
		*(float*) (slot + 0x1c) = acc;
	}
	memset(slot + 0x1b4, 0, 0x10);
	ahm_ResetEntityState(slot);
	if (slot[2] == 3 || slot[2] == 4 || slot[2] == 2 || slot[2] == 0x13) {
		rnd = gm_RandomMod(3) & 0xffff;
		/* volatile read to stop msvc6 folding load and store into a
		 * single "add byte ptr [..],0x2a"; the reference keeps the
		 * separate mov/add/mov (0x10019627..0x10019634) */
		slot[0x82 + rnd] =
		    (char) (*(volatile char*) (slot + 0x82 + rnd) + 0x2a);
	}
	LogMessageInternal(s_file_spiel_c_10031004, 0x2888, work, 8);
	if (idx == 0xffff) {
		LogMessageInternal(s_file_spiel_c_10031004, 0x286c, s_bug_10031594,
		                   1);
	}
	sprintf(work, s_fmt_playerid_10031570, g_next_object_id, slot + 0x30);
	return idx;
}
