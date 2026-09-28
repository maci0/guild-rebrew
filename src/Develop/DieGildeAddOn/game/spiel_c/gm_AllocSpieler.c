/* gm_AllocSpieler: allocate and initialize an entity from a
 * father/mother pair with random trait generation.
 *
 * Semantic fixes (2026-09-24), each read off the reference disassembly:
 *   1. the 14-iteration trait loop stores dst[-2] inside the body
 *      (0x1001930d-0x10019316, before the back-edge);
 *   2. the arg8 != 2 arm stores (char) arg8, not slot[0x166]
 *      (0x10018cd4-0x10018cec, eax = arg8 on the skip path);
 *   3. the tail formats the PlayerID line before the 0x2888 log
 *      (0x10019636-0x1001967c);
 *   4. the citizen gm_RandomMod(8) roll goes into idx and all three
 *      slot[0x217] tests read it (0x10018a3b, 0x10018b5b..0x10018b9e);
 *   5. the blend weight is drawn once per trait (back edge 0x10018f75 ->
 *      the gm_RandomFloat01 call at 0x10018f01);
 *   6. the father's best trait is tested first, so a tie takes the father's
 *      value (0x10018f0e);
 *   7. slot[0x58] = 1 is the default BEFORE `if (father != 0)`
 *      (0x1001946b); after the if/else chain it overwrote father[0x58] + 1.
 *   8. father_id goes to slot+0x64 AFTER the 0xff fill of +0x5c..+0x7b
 *      (0x10019462); before it, the fill overwrote it with -1.
 *   9. the stat modifiers, 0xd/0x5c/0x64/0x58 fields, father ref hook,
 *      counters and 1000.0f block run on the no-parent path only; the
 *      two-parent path jumps from its mutual block to the second
 *      gm_RandomMod(0x10) (0x100191e9 jmp 0x10019572).  Falling into
 *      them re-ran gm_RandomQuadratic and bumped a counter twice.
 *  10. the father is looked up by parameter 2, father_id (0x10018d35
 *      reads [esp+0x43c] with the mother's id still pushed), the same
 *      value both paths store at slot+0x64 beside mother_id at +0x60;
 *      it had been looked up by arg4, the value stored at slot+0xa.
 * Flags: this file compiles with plain /O2 /Gd (the project default).  The
 * /Oa /Ow metadata setting needed volatile reads to reproduce the reference's
 * load/store pairing; without /Ow msvc6 assumes aliasing and pairs them
 * itself (linked 12,182 -> 12,062 on the same source).
 * Addressing: the record array, both relationship tables and the entity-type
 * table go through their symbols (g_slot_table, g_relationship_matrix_*,
 * g_entity_type_table), not raw integer addresses.  msvc6 treats memory
 * reached from a raw integer address as unchanged by calls once a branch
 * has made the load a global CSE candidate, so it kept the entity id in a
 * register across the mutual block's four gm_RandomMod calls; through the
 * symbol it reloads, as the reference does (docs/msvc6-c-shapes.md 187).
 * The same change let the sympathy loops drop their volatile reads and
 * emit the reference's xor/mov zero-extend.  Linked 12,044 -> 11,917.
 * Shape facts established from the reference and kept:
 *   - work is char[0x400]: the frame is 0x41c with the same seven small
 *     slots as ours, and nothing addresses the top dword (slots2.py);
 *   - the per-trait selection keeps separate per-arm stores (the counter
 *     stays in a register: cmp esi,5 / [esi+ebp+0x80]) and reads the
 *     father byte of the blend through an int with a memory home, which is
 *     what makes msvc6 emit the reference's fimul (shapes 82);
 *   - the best-trait scan runs for (i = 1; i < 5; i++) (cmp ecx,5);
 *   - the byte-field selects are ternaries (an arithmetic select stored to a
 *     byte narrows to add r8; a ternary keeps add r32); the 0x217 target is
 *     unsigned char (and eax,0x86 imm32 at 0x10018bad);
 *   - the header init's stores sit on the reference's side of the sprintf
 *     and LogMessageInternal calls (stores cannot cross a call);
 *   - both aging blocks convert the age to float once and keep acc on the
 *     FPU stack.
 *   - the citizen block follows the reference's statement order around its
 *     calls (roll, +0x1f0, 0x164, 9, 0xc; +0x1d0 before the counter; +0x20
 *     after gm_RandomQuadratic; +0x18 after gm_RandomMod), reads the
 *     0x1003542c counter once, and copies the five trait bytes as a struct;
 *   - the mutual-sympathy stores compute their value before indexing (the
 *     reference calls gm_RandomMod first, then loads both ids).
 * Spellings the reference's code pins down:
 *   - the float constants are symbols (g_float_const_*): through raw
 *     addresses the per-trait arm 2 and the 14-trait blend load the
 *     constant first and lose the shared tail fmul;
 *   - the three +0x10 draws go through an unsigned short local (one
 *     `and eax,0xffff`, then fild) and read slot+0x1c as
 *     `(double) *(float*) (slot + 0x1c)`, which loads it before the
 *     constant as the reference does;
 *   - in the aging loops decay is assigned before acc; the other order
 *     evaluates acc - decay first and needs fld st(0) / fstp st(1);
 *   - the 14-trait blend weight is a float local and the mother term has
 *     no (double) cast (fld st(0); fsubr; fxch; fmul mem);
 *   - the father term is `(float) (K - w) * father`: with the float
 *     rounding the first fmul consumes the op-0x162 node that c2 puts
 *     after fsubr (scheduler latency 3), so `push 0xa` issues right after
 *     fsubr.  With a double product the fmul takes fsubr's result directly,
 *     is ready the next cycle and the push lands after the second fmul;
 *   - the no-parent trait loop stores dst[0..2] and steps both pointers
 *     at the end of the body.
 * Linked: byte-exact.  Constructs the reference pins down beyond
 * the list above (each measured against the positional probe):
 *   - the header -1 fill, the no-parent -1 fill and the parent path's five
 *     -1 ref slots are store loops, not memset or separate stores
 *     (shapes 197); the 0x1b4 clear is a real memset;
 *   - the citizen path's +0x10 draw is written inline in the blend, and
 *     its quadratic term goes through the double `blend`; the 0x124/0x128
 *     pair goes through a second double, `scale` (a re-read of +0x124
 *     keeps msvc6 from moving the best_* stores above the fst);
 *   - on the no-parent and parent paths +0x18 = +0x1c is written after the
 *     +0x10 blend (msvc6 hands out eax/ecx/edx in rotation, so the copy's
 *     order decides every later scratch register);
 *   - the mutual-sympathy values are computed inside each store (no char
 *     local), the no-parent hook loop indexes father+0x5c directly, and
 *     g_citizen_count++ comes before slot[0x216];
 *   - the per-trait blend weight is its own block-local float; the tail's
 *     aging loop keeps its decay in `acc` (the per-trait slot 0x10) and its
 *     running value in `decay`, while the citizen path's aging has its own
 *     `decay_citizen` and shares `age` (both ages sit at 0x24);
 *   - no-parent trait loop: dst[2] is the gm_RandomMod(0xa) value and
 *     dst[1] = dst[0] * 0.x, as in the parent loop (0x90 / 0x8c); the
 *     earlier source had them swapped.
 *   - `location` is dead after the building-type block and doubles as the
 *     scratch int for the class check, the range check and the no-parent
 *     dynasty counter.  Each reuse is a separate web of the parameter, and
 *     c2 numbers a parameter's webs from the free list the constant
 *     candidates were just released to, so three extra webs move `type`
 *     from id 61 to 30 and `arg6` stays at 49.  That reverses which of the
 *     two is split first, and with it the reload order in the two edge
 *     blocks at 0x10018c28/0x10018c38 (esi/ebx against ebx/esi).  One or
 *     two reuses, in any of the dead parameters, leave the order as it
 *     was; the local `n` in those three places gives our old order.
 * The per-trait fimul needs the father byte in memory; the trait_home
 * alias gives it, a plain int local is enregistered and gets fild/fmulp.
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
 * THE "192 HUNKS" FIGURE ABOVE MISREAD THE SHAPE -- round 1082 replaced it.
 * That helper is no longer in the tree.  Re-measured with capstone, aligning
 * the reference against the raw-linked split_poc and matching on mnemonic plus
 * register-normalised operands (resync window 6): 1056 reference instructions,
 * 1054 ours, **48 differing runs, largest 159**.  Two of every three differing
 * instructions sit in ONE contiguous block at 0x1001910e.  The function is not
 * uniformly rough; it has one large wall and a scatter of small ones.  Hunk
 * count depends on where the aligner resyncs, so it cannot answer "one wall or
 * many" -- run-size distribution can, and that is what to quote.
 *
 * The wall is a two-register role swap (edi/esi) whose single upstream cause is
 * the third instruction of the block: the reference zero-extends the
 * `unsigned short` load with `xor eax,eax` + `mov ax,[ebp]`, we emit
 * `and eax,0xffff`.  That is the colv/rowv sympathy loop below.  Three probes,
 * all measured at the link and all negative -- do not re-probe:
 *   drop `volatile` from both loads          -> +426 (volatile is load-bearing)
 *   explicit `(int)` cast on the first load  -> +0 (inert)
 *   hoist `rowv` above the first gm_RandomMod call (the reference's order)
 *                                            -> composition collapses,
 *                                               .text +658, 0/319 at ref VA
 * See codegen-walls section 34.
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

#include <stdlib.h>
#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

#pragma intrinsic(memcpy, memset, strlen, strcpy)

extern int g_next_object_id; /* 0x10030b6c */
extern int g_citizen_count; /* 0x10035434 */
extern double g_const_2; /* 0x10025688 */
extern double g_const_0_001; /* 0x100256d0 */
extern double g_const_one_d; /* 0x100257d8 */
extern double g_const_0_2; /* 0x10025810 */
extern float g_const_0_6; /* 0x10025f88 - fmul dword, not qword */
extern double g_const_8; /* 0x10025f90 */
extern double g_const_900; /* 0x10025f98 */
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
int __cdecl sprintf(char*, const char*, ...);
int __cdecl LogMessageInternal(char*, int, char*, int);

/* Named, in the reference's order: as a literal, the SpID format swaps two
 * stack loads in this function (3681/3689).  The spiel.c path stays a raw
 * address; gm_InitObjektHersteller emits it. */
// DATA: SERVER 0x10031570
static char s_fmt_player_id[] =
    "----->PlayerID= %i PlayerName= %s";
// DATA: SERVER 0x10031594
static char s_alloc_spieler_bug[] = "gm_AllocSpieler: bug";
// DATA: SERVER 0x100315ac
static char s_family_count_overflow[] =
    "gm_AllocSpieler(): gm_CurrentHumanFamilyCount overflow";
// DATA: SERVER 0x100315e4
static char s_fmt_sp_id[] = "----->SpID= %i playermode= %i";
// DATA: SERVER 0x10031604
static char s_alloc_spieler_array_overflow[] = "gm_AllocSpieler: array overflow...";

/* The five trait bytes at record +0x80 (ahm entity +0x24). */
// SIZE 0x5
struct traits5 {
	unsigned char b[5];
};

extern unsigned char g_slot_table[2]; /* 0x100358a0: 0x300 records of 0x21c */

extern char g_relationship_matrix_primary[];
extern char g_relationship_matrix_secondary[];

extern float g_const_1_0f;  /* 0x100256a0: 1.0 */
extern float g_const_0_5;  /* 0x100256b0: 0.5 */
extern float g_const_0_1;  /* 0x100256b4: 0.1 */
extern float g_const_0_33;  /* 0x100256b8: 0.33 */
extern float g_const_30;  /* 0x100256c4: 30.0 */
extern float g_const_7;  /* 0x100256c8: 7.0 */
extern float g_const_0_25; /* 0x10025714: 0.25 */

extern unsigned char g_stat_table[780]; /* 0x10030ba0: 6-byte records, 5 stats + slot[0xd] default */
#define g_stat_table_30dda (g_stat_table + 95 * 6)

extern int g_next_family_index; /* 0x1003542c */
extern int gm_CurrentHumanFamilyCount; /* 0x10035430 */

// FUNCTION: SERVER 0x10018850
unsigned short __cdecl gm_AllocSpieler(int type, int mother_id, int father_id, int arg4, int location, int arg6, int arg7, int arg8)
{
	char* slot;
	char* mother;
	char* father;
	char work[0x400];
	int idx;
	int j;
	int i;
	int rnd;
	int n;
	double blend;
	double scale;
	int trait_byte;
	int* trait_home;
	int best_father;
	int best_mother;
	float acc;
	float age;
	float decay;
	float* src;
	float* dst;
	char* stat;
	char cv;
	float decay_citizen;

	/* find a free slot: first by id word == 0xffff, then by state byte == 0xf */
	for (idx = 0; idx < 0x300; idx++) {
		if (*(unsigned short*) (g_slot_table + idx * 0x21c) == 0xffff) {
			break;
		}
	}
	if (idx == 0x300) {
		for (idx = 0; idx < 0x300; idx++) {
			if (*(unsigned char*) (g_slot_table + 0x2 + idx * 0x21c) == 0xf) {
				break;
			}
		}
	}
	if (*(unsigned char*) (g_slot_table + 0x2 + idx * 0x21c) == 0xf) {
		g_citizen_count--;
	}
	if (idx == 0x300) {
		LogMessageInternal((char*) 0x10031004, 0x2614,
		                   s_alloc_spieler_array_overflow, 1);
		return 0xffff;
	}
	slot = (char*) g_slot_table + idx * 0x21c;
	memset(slot, 0, 0x21c);
	/* The reference stores 0xffff here before the -1 fills.  msvc6
	 * dead-store-eliminates it against the id store further down unless the
	 * id store is addressed so the two are not provably the same location:
	 * with `*(unsigned short*) (g_slot_table + idx * 0x21c) = idx` below, both
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
	*(unsigned short*) (g_slot_table + idx * 0x21c) = 0xffff;
	*(int*) (g_slot_table + 0x4 + idx * 0x21c) = -1;
	/* The -1 fills here, on the no-parent path and on the parent path, and
	 * the 0x1b4 clear near the end are loops in the source: msvc6 turns
	 * each into rep stosd or a run of stores, but the destination stays its
	 * own register candidate, which is what the reference shows
	 * (`lea edx,[edx+0x100358fc]; ...; mov edi,edx` at 0x100188fa, `lea
	 * edi` before `mov ecx,8` at 0x10019455).  The same fills written as
	 * memset() compile the destination straight into edi and shift the
	 * allocation of the whole function (shapes 197). */
	for (i = 0; i < 8; i++) {
		*(int*) (g_slot_table + 0x5c + idx * 0x21c + i * 4) = -1;
	}
	*(unsigned short*) slot = (unsigned short) idx;
	slot[2] = (char) type;
	*(int*) (slot + 0x170) = 0;
	*(int*) (slot + 0x16c) = 0;
	*(int*) (slot + 0x1f0) = 0;
	*(int*) (slot + 0x210) = -1;
	slot[0x215] = 0;
	g_citizen_count++;
	slot[0x216] = 0;
	slot[0x217] = 0;
	slot[0x218] = 1;
	sprintf(work, s_fmt_sp_id, g_next_object_id, type);
	LogMessageInternal((char*) 0x10031004, 0x2637, work, 8);
	*(int*) (slot + 4) = g_next_object_id;
	g_next_object_id++;
	*(int*) (slot + 0x1e4) = 0x3f800000; /* 1.0f */
	slot[0x164] = (char) arg6;
	slot[8] = 0x64;
	*(unsigned short*) (slot + 0xa) = (unsigned short) arg4;
	slot[0x166] = 0;
	slot[0x165] = (char) arg7;
	slot[0x1f4] = 0;
	*(int*) (slot + 0x190) = 4;
	*(int*) (slot + 0x194) = 0;
	slot[0xd] = 1;
	*(int*) (slot + 0x18c) = -1;
	*(int*) (slot + 0x20c) = -1;
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
			idx = gm_RandomMod(8) & 0xffff;
			*(int*) (slot + 0x1f0) = *(int*) ent;
			slot[0x164] = ent[0xd4];
			slot[9] = ent[0xd5];
			slot[0xc] = ent[0xd6];
			strcpy(slot + 0x30, ent + 4);
			strcpy(slot + 0x40, ent + 0x14);
			strcpy(slot + 0x1f4, ent + 0xd7);
			*(struct traits5*) (slot + 0x80) = *(struct traits5*) (ent + 0x24);
			memcpy(slot + 0x88, ent + 0x2c, 0xa8);
			*(float*) (slot + 0x1d0) =
			    (float) (gm_RandomFloat01() * g_const_0_5) +
			    g_const_0_25;
			n = g_next_family_index;
			*(int*) (slot + 0x1c) = 0x447a0000; /* 1000.0f */
			*(unsigned short*) (slot + 0x50) = (unsigned short) n;
			g_next_family_index = n + 1;
			blend = gm_RandomQuadratic() * g_const_7;
			*(int*) (slot + 0x20) = 0x41400000; /* 12.0f */
			*(float*) (slot + 0x14) = (float) blend + g_const_30;
			*(float*) (slot + 0x10) =
			    (float) ((double) *(float*) (slot + 0x1c) * g_const_0_33 +
			             (double) (unsigned short) gm_RandomMod((unsigned short) (int) (*(float*) (slot + 0x1c) *
			                                            g_const_0_2)) -
			             (double) *(float*) (slot + 0x1c) * g_const_0_1);
			*(float*) (slot + 0x18) = *(float*) (slot + 0x1c);
			if (idx < 2) {
				slot[0x217] = 0x58;
			} else if (idx < 4) {
				slot[0x217] = 0x5c;
			}
			*(unsigned char*) (slot + 0x217) = idx < 6 ? 0xc2 : 0x3c;
			age = (float) *(unsigned short*) (slot + 0xa);
			if (age > *(float*) (slot + 0x20)) {
				decay_citizen = *(float*) (slot + 0x14);
				acc = *(float*) (slot + 0x1c);
				for (n = (int) (age - *(float*) (slot + 0x20)); n > 0; n--) {
					acc = acc - decay_citizen + decay_citizen / acc;
				}
				if (acc <= g_const_1_0f) {
					acc = g_const_1_0f;
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

	/* building-type location field.  The entry is a pointer local, as in
	 * gm_CheckEntityType (spiel6.c, RELOC): the reference forms its address
	 * with lea and loads the byte separately (0x10018c7b), where a byte
	 * local folds the address into the load. */
	if (location != 0) {
		unsigned char* type_entry;

		type_entry = (unsigned char*) g_entity_type_table + (unsigned int) *(unsigned char*) location * 0x24d;
		if (*type_entry != 1) {
			if (*type_entry > 3 && *type_entry < 0x17 && *type_entry != 0xa && *type_entry != 0xf && *type_entry != 0x11) {
				*(int*) (slot + 0x16c) = location;
			}
		} else {
			*(int*) (slot + 0x170) = location;
		}
	}
	slot[0xd] = slot[0x166] != 0 ? 2 : 1;
	if (type != 6 && type != 7 && type < 0xa) {
		slot[0x1b0] = (char) gm_RandomMod(8);
	}
	if (arg8 == 2) {
		slot[9] = (char) gm_RandomMod((unsigned short) arg8);
	} else {
		slot[9] = (char) arg8;
	}
	if (type < 4 || type == 0xb) {
		if (arg7 != 0) {
			location = gm_EntityClassCheck(arg7);
			if (location != 2) {
				slot[9] = (char) location;
			}
		} else if (arg6 != 0) {
			location = gm_IsInRange(arg6);
			if (location != 2) {
				slot[9] = (char) location;
			}
		}
	}
	mother = (char*) gm_LookupEntityRecordById(mother_id);
	father = (char*) gm_LookupEntityRecordById(father_id);
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
				*(unsigned char*) (slot + 0x217) = rnd < 4 ? 0x4e : 0x56;
			} else {
				if (rnd < 3) {
					slot[0x217] = 0x3e;
				} else {
					*(unsigned char*) (slot + 0x217) = rnd < 6 ? 0x56 : 0x4e;
				}
			}
		} else {
			if (n == 0xb || n == 0xc) {
				if (rnd < 3) {
					slot[0x217] = 0x58;
				} else {
					*(unsigned char*) (slot + 0x217) = rnd < 6 ? 0x5c : 0xc2;
				}
			} else {
				if (rnd < 3) {
					slot[0x217] = 0x3c;
				} else {
					*(unsigned char*) (slot + 0x217) = rnd < 6 ? 0x5c : 0x58;
				}
			}
		}
		/* 14-iteration trait interpolation from the trait table */
		dst = (float*) (slot + 0x88);
		src = (float*) (0x10025818 + n * 0x70);
		for (i = 0xe; i != 0; i--) {
			dst[0] = (float) (gm_RandomFloat01() * (double) (src[1] - src[0]) +
			                  src[0]);
			dst[2] = (float) ((double) (gm_RandomMod(0xa) & 0xffff) +
			                  g_const_900);
			dst[1] = (float) ((double) dst[0] * g_const_0_001);
			src += 2;
			dst += 3;
		}
		*(float*) (slot + 0x124) =
		    (float) ((gm_RandomFloat01() + g_const_2) *
		             g_const_8);
		*(float*) (slot + 0x128) =
		    (float) ((double) *(float*) (slot + 0x124) *
		             g_const_0_001);
		/* symmetric sympathy-matrix init: both [j][id] and [id][j] */
		for (j = 0; j < 0x300; j++) {
			*(char*) (g_relationship_matrix_primary + *(unsigned short*) slot + j * 0x300) =
			    (char) (gm_RandomMod(0x40) - 0x20);
			*(char*) (g_relationship_matrix_secondary + *(unsigned short*) slot + j * 0x300) = 0;
			*(char*) (g_relationship_matrix_primary + ((*(unsigned short*) slot * 3) << 8) + j) =
			    (char) (gm_RandomMod(0x40) - 0x20);
			*(char*) (g_relationship_matrix_secondary + ((*(unsigned short*) slot * 3) << 8) + j) = 0;
		}
		slot[0xc] = (char) gm_RandomMod(2);
		*(float*) (slot + 0x1d0) =
		    (float) (gm_RandomFloat01() * g_const_0_5) +
		    g_const_0_25;
		/* Stat modifiers through the second draw belong to this path only:
		 * the two-parent path's mutual block jumps past them to the shared
		 * draw (reference jmp 0x10019572 at 0x100191e9), having set its own
		 * counters, parent ids and 1000.0f fields already. */
		if (arg7 != 0 && arg6 == 0) {
			for (i = 0; i < 5; i++) {
				slot[0x80 + i] = (char) gm_RandomStatModifier(
				    g_stat_table_30dda[*(unsigned char*) (slot + 0x165) * 6 + i]);
			}
		} else {
			for (i = 0; i < 5; i++) {
				slot[0x80 + i] = (char) gm_RandomStatModifier(
				    g_stat_table[*(unsigned char*) (slot + 0x164) * 6 + i]);
			}
		}

		if (type != 6 && type != 7) {
			slot[0xd] = g_stat_table[*(unsigned char*) (slot + 0x164) * 6 + 5];
		}
		for (i = 0; i < 8; i++) {
			*(int*) (slot + 0x5c + i * 4) = -1;
		}
		*(int*) (slot + 0x64) = father_id;
		slot[0x58] = 1;
		if (father != (char*) 0) {
			slot[0x58] = (char) (father[0x58] + 1);
			for (i = 3; i < 8; i++) {
				if (*(int*) (father + i * 4 + 0x5c) == -1) {
					*(int*) (father + i * 4 + 0x5c) = *(int*) (slot + 4);
					break;
				}
			}
		}
		if (type == 6 || type == 7 || type == 5) {
			/* The reference loads the family counter once and reuses it for the
			 * bound test and the update: `mov eax,[0x10035430]; cmp eax,0x10;
			 * jl ...; mov edx,eax; or dh,0x80; inc eax; mov [ebp+0x50],dx;
			 * mov [0x10035430],eax` at 0x100194c5.  Reading the global twice
			 * emitted a 16-bit load for the store and a second 32-bit load for
			 * the increment. */
			n = gm_CurrentHumanFamilyCount;
			if (n >= 0x10) {
				LogMessageInternal((char*) 0x10031004, 0x27f0,
				                   s_family_count_overflow, 1);
				return 0xffff;
			}
			*(unsigned short*) (slot + 0x50) = (unsigned short) (n | 0x8000);
			gm_CurrentHumanFamilyCount = n + 1;
		} else if (type >= 0xa) {
			*(unsigned short*) (slot + 0x50) = 0x7fff;
		} else {
			/* Same single-load shape on the other counter (0x100194d8). */
			location = g_next_family_index;
			*(unsigned short*) (slot + 0x50) = (unsigned short) location;
			g_next_family_index = location + 1;
		}
		*(int*) (slot + 0x1c) = 0x447a0000; /* 1000.0f */
		*(float*) (slot + 0x14) =
		    (float) (gm_RandomQuadratic() * g_const_7) +
		    g_const_30;
		*(int*) (slot + 0x20) = 0x41400000; /* 12.0f */
		*(float*) (slot + 0x10) =
		    (float) ((double) *(float*) (slot + 0x1c) * g_const_0_33 +
		             (double) (unsigned short) gm_RandomMod((unsigned short) (int) (*(float*) (slot + 0x1c) *
		                                            g_const_0_2)) -
		             (double) *(float*) (slot + 0x1c) * g_const_0_1);
		*(float*) (slot + 0x18) = *(float*) (slot + 0x1c);
		/* first of two discarded gm_RandomMod(0x10) draws (0x1001956a); the
		 * second, at draw_tail, is the one both paths reach */
		gm_RandomMod(0x10);
		goto draw_tail;
	}
	/* Round 194: the parent-wins chain is ONE fault, not the five the
	 * round-429 census implied, and not 344 bytes -- the chain proper is
	 * ref 0x10018d5d-0x10018e0b, 45 instructions / 174 bytes, and OURS IS
	 * ALSO 174 bytes with an EQUAL byte multiset and an EQUAL kind
	 * multiset.  Zero instruction-length difference: it is a pure
	 * load-hoist repeated in all four arms.  The reference pairs each
	 * LOAD with its own STORE (verified 0x10018d93: `mov dl,[esi+0xc]` /
	 * `mov [ebp+0xc],dl` / `mov eax,[esi+0x1d0]` / `mov [ebp+0x1d0],eax` /
	 * `mov cl,[esi+0x217]` / `mov [ebp+0x217],cl`); msvc6 hoists all three
	 * loads above all three stores because `slot` and `mother`/`father`
	 * are independent heap pointers it cannot prove non-aliasing for --
	 * shapes 86b's mechanism seen from the LOAD side.  The STORES were
	 * already in reference order on both sides; only the loads moved, so
	 * do not re-diagnose this by reading store order.
	 * Volatile-qualifying the six parent reads pins them: aligned
	 * 662 -> 670, hunks 178 -> 166, insert/delete 117 -> 106, the chain
	 * going 17/45 -> 33/45 text-identical with the reference's exact
	 * LOAD,STORE pairing in all four arms, at real body 3689 both ways
	 * (byte-neutral).  It costs **+2 linked**, so it is NOT applied.
	 * Residue after it was 10 branch displacements all off by a constant
	 * -3, inherited from upstream rather than from this chain.
	 * ALSO CORRECTED: this file's header claimed a 20-variant CFLAGS sweep
	 * where "every one scores identically".  False -- `/Ow` is heavily
	 * load-bearing (766 -> 317 without it) while `/Oa` is entirely inert. */
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
		float rnd01;

		rnd01 = gm_RandomFloat01();
		*(float*) (slot + 0x88 + i * 0xc) =
		    (float) ((float) (g_const_one_d - rnd01) *
		                 *(float*) (father + 0x88 + i * 0xc) +
		             rnd01 * *(float*) (mother + 0x88 + i * 0xc));
		*(float*) (slot + 0x90 + i * 0xc) =
		    (float) ((double) (gm_RandomMod(0xa) & 0xffff) +
		             g_const_900);
		*(float*) (slot + 0x8c + i * 0xc) =
		    (float) ((double) *(float*) (slot + 0x88 + i * 0xc) *
		             g_const_0_001);
	}
	/* The reference draws this pair at 0x10018e77, AFTER the 14-iteration
	 * trait loop -- the no-parent twin at 0x1001931b already sits after
	 * its own loop, and that asymmetry is what exposed the difference.
	 * Defined above the loop, [0x124] pins its schedule across it. */
	scale = (gm_RandomFloat01() + g_const_2) * g_const_8;
	*(float*) (slot + 0x124) = (float) scale;
	*(float*) (slot + 0x128) = (float) (scale * g_const_0_001);
	/* find the best trait index of each parent (quirky +1 indexing) */
	best_mother = 0;
	best_father = 0;
	/* mother first: the reference compares through the mother pointer and
	 * keeps the father byte pointer as the induction (0x10018eb9) */
	for (i = 1; i < 5; i++) {
		if (*(unsigned char*) (mother + 0x80 + i) >
		    *(unsigned char*) (mother + 0x80 + best_mother)) {
			best_mother = i;
		}
		if (*(unsigned char*) (father + 0x80 + i) >
		    *(unsigned char*) (father + 0x80 + best_father)) {
			best_father = i;
		}
	}
	/* per-trait selection: father best / mother best / interpolation */
	trait_home = &trait_byte;
	for (i = 0; i < 5; i++) {
		float weight;

		weight = (float) gm_RandomFloat01();
		if (i == best_father) {
			slot[0x80 + i] = (char) (
			    (double) *(unsigned char*) (father + 0x80 + i) *
			    g_const_0_5);
		} else if (i == best_mother) {
			slot[0x80 + i] = (char) (
			    (double) *(unsigned char*) (mother + 0x80 + i) *
			    g_const_0_5);
		} else {
			/* The father byte goes through an int with a memory home, which
			 * is what makes msvc6 emit fimul (shapes 82); without the
			 * (double) casts the mother term compiles to fild + fmul [weight]
			 * and all three arms share the reference's tail fmul (0x10018f5e). */
			*trait_home = *(unsigned char*) (father + 0x80 + i);
			slot[0x80 + i] = (char) (((g_const_one_d - weight) * trait_byte +
			                          *(unsigned char*) (mother + 0x80 + i) * weight) *
			                         g_const_0_5);
		}
	}
	/* no gm_RandomMod(2) / gm_RandomFloat01 pair here: on the two-parent
	 * path 0xc and 0x1d0 were already copied from whichever parent won the
	 * checks above (reference 0x10018d96..0x10018df9).  The randomized pair
	 * belongs only to the no-parent path at 0x1001939a. */
	/* record both parents and hook the child into their ref arrays */
	*(int*) (slot + 0x60) = mother_id;
	*(int*) (slot + 0x64) = father_id;
	for (i = 3; i < 8; i++) {
		*(int*) (slot + 0x5c + i * 4) = -1;
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
	*(int*) (slot + 0x7c) = 0;
	if (father[2] == 6 || father[2] == 7 || father[2] == 5) {
		*(unsigned short*) (slot + 0x50) = *(unsigned short*) (father + 0x50);
		slot[0x58] = (char) (father[0x58] + 1);
		*(int*) (slot + 0x54) = *(int*) (father + 0x54);
	} else {
		*(unsigned short*) (slot + 0x50) = *(unsigned short*) (mother + 0x50);
		slot[0x58] = (char) (mother[0x58] + 1);
		*(int*) (slot + 0x54) = *(int*) (mother + 0x54);
	}
	*(int*) (slot + 0x1c) = 0x447a0000; /* 1000.0f */
	*(float*) (slot + 0x14) =
	    (float) ((gm_RandomQuadratic() * g_const_7 +
	              g_const_30) *
	                 g_const_0_6 +
	             (*(float*) (father + 0x14) + *(float*) (mother + 0x14)) *
	                 g_const_0_2);
	*(int*) (slot + 0x20) = 0x41400000; /* 12.0f */
	*(float*) (slot + 0x10) =
	    (float) ((double) *(float*) (slot + 0x1c) * g_const_0_33 +
	             (double) (unsigned short) gm_RandomMod((unsigned short) (int) (*(float*) (slot + 0x1c) *
	                                            g_const_0_2)) -
	             (double) *(float*) (slot + 0x1c) * g_const_0_1);
	*(float*) (slot + 0x18) = *(float*) (slot + 0x1c);
	/* Symmetric sympathy-matrix init: both [j][id] and [id][j].  The index
	 * is written into each store rather than held in a local: msvc6 then
	 * shares the sum as its own CSE, loads the id into a scratch register and
	 * forms the index with lea into a callee-saved one, as the reference does
	 * (0x100190fc).  A named index local takes the id load directly and adds,
	 * 2 bytes shorter per loop. */
	for (j = 0; j < 0x300; j++) {
		*(char*) (g_relationship_matrix_primary + *(unsigned short*) slot + j * 0x300) =
		    (char) (gm_RandomMod(0x40) - 0x20);
		*(char*) (g_relationship_matrix_secondary + *(unsigned short*) slot + j * 0x300) = 0;
		*(char*) (g_relationship_matrix_primary + ((*(unsigned short*) slot * 3) << 8) + j) =
		    (char) (gm_RandomMod(0x40) - 0x20);
		*(char*) (g_relationship_matrix_secondary + ((*(unsigned short*) slot * 3) << 8) + j) = 0;
	}
	/* mutual sympathy between the new entity and each parent.  The value is a
	 * char: the reference computes it with `mov cl,0x7f; sub cl,al` and
	 * stores cl, where an int temporary adds a movsx per store. */
	*(char*) (g_relationship_matrix_primary + ((*(unsigned short*) slot * 3) << 8) +
	          *(unsigned short*) mother) =
	    (char) (0x7f - gm_RandomMod(0x20));
	*(char*) (g_relationship_matrix_primary + ((*(unsigned short*) mother * 3) << 8) +
	          *(unsigned short*) slot) =
	    (char) (0x7f - gm_RandomMod(0x20));
	*(char*) (g_relationship_matrix_primary + ((*(unsigned short*) slot * 3) << 8) +
	          *(unsigned short*) father) =
	    (char) (0x7f - gm_RandomMod(0x20));
	*(char*) (g_relationship_matrix_primary + ((*(unsigned short*) father * 3) << 8) +
	          *(unsigned short*) slot) =
	    (char) (0x7f - gm_RandomMod(0x20));
draw_tail:
	gm_RandomMod(0x10);
	age = (float) *(unsigned short*) (slot + 0xa);
	if (age > *(float*) (slot + 0x20)) {
		acc = *(float*) (slot + 0x14);
		decay = *(float*) (slot + 0x1c);
		for (n = (int) (age - *(float*) (slot + 0x20)); n > 0; n--) {
			decay = decay - acc + acc / decay;
		}
		if (decay <= g_const_1_0f) {
			decay = g_const_1_0f;
		}
		*(float*) (slot + 0x1c) = decay;
	}
	memset(slot + 0x1b4, 0, 0x10);
	ahm_ResetEntityState(slot);
	if (slot[2] == 3 || slot[2] == 4 || slot[2] == 2 || slot[2] == 0x13) {
		rnd = gm_RandomMod(3) & 0xffff;
		/* through a pointer local: the reference loads, forms the address
		 * with lea and stores separately (0x10019619..0x1001962a); an
		 * indexed `+= 0x2a` folds into one add byte ptr, 10 bytes shorter */
		stat = slot + 0x82 + rnd;
		*stat = (char) (*stat + 0x2a);
	}
	if (idx == 0xffff) {
		LogMessageInternal((char*) 0x10031004, 0x286c, s_alloc_spieler_bug,
		                   1);
	}
	sprintf(work, s_fmt_player_id, g_next_object_id, slot + 0x30);
	LogMessageInternal((char*) 0x10031004, 0x2888, work, 8);
	return idx;
}
