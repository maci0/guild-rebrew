#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
int __cdecl _ftol(void);

typedef int(__cdecl* ALLOCFN)(int, int, int);

#pragma intrinsic(memcpy, memset)

// SIZE 0x2c
typedef struct {
	char pad[0x24];
	int(__cdecl* func)(int, int);
	int field_28;
} DISPATCH_OBJ;

#pragma pack(push, 1)
// SIZE 0x43
typedef struct {
	short active;
	int id;
	char pad[0x3d];
} Record;
#pragma pack(pop)

extern char* g_item_def_table; /* 0x101de450 */
void __cdecl gm_InitEntitySlots(void);
extern unsigned short* g_query_base;
extern int g_query_limit;
void __cdecl m_FreeTracked(void*);
extern char* g_entity_type_table;
extern unsigned char* g_entity_ptr;
void* __cdecl FindNextFilteredEntity(void);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern char* g_array_base;
extern unsigned char g_slot_table[];
void __cdecl free_node(char*);
int __cdecl gm_FreeObjectListRecursive(char**);
void __cdecl gm_NoopRet2(void);
char* __cdecl gm_AllocateObjectSlot(void);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
short* __cdecl gm_ResolveParentEntity(short*);
extern int g_next_object_id; /* defined in spiel.c */
int g_current_year;
extern char s_D__Develop_DieGildeAddOn_game_sp_10031004[]; /* defined in spiel.c */
extern char s_gm_AddObjekt____obj____ob_NULL_10031390[];
extern char s_gm_AddObjekt____Parent_not_found_10031358[];
extern unsigned char* g_EntityListStart;
extern unsigned char* g_EntitySearchPtr;
extern int g_SearchCount;
extern unsigned char g_SearchFlag;
extern void* g_SomeGlobal;
extern unsigned char g_FilterActive;
extern unsigned char g_FilterType;
extern int g_FilterId;
extern unsigned short g_FilterVal25;
extern unsigned short g_FilterVal27;
extern unsigned char g_FilterVal30;
void __cdecl gv_Free3Fields(void* param);
extern int g_query_state_a0c[];
extern unsigned char g_byte_table_30861;
char* __cdecl gm_SearchStruct(void);
int __cdecl gm_AllocBuildingContents(char* geb, int obj_id);
unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
int __cdecl gm_CheckEntityType(unsigned char* geb);
int __cdecl AllocGraveyardField(char* geb);
void __cdecl SpawnGraveyardEntities(char* geb, int param);
void __cdecl gm_SetBuildingWorkerLimits(unsigned char* geb);
int __cdecl gm_GetBuildingTypeCategory(int);
void __cdecl gm_AllocBuildingDefaults(unsigned char* geb);
int __cdecl gm_EntityAccumulate(void*);
int __cdecl gm_RemoveLinkedNodeById(int*, int);
void __cdecl amt_ClearEntityLinks(short*);
void __cdecl gm_InitEntityIfValid(void* arg1);
void __cdecl gm_DeallocEntity(unsigned int idx, int param);
extern int g_citizen_count;
extern int g_dynasty_field_2c;
extern int g_dynasty_generation_counter;
extern unsigned char g_entity_base[];
extern char g_entity_end[];
int __cdecl gm_GetBuildingTypeCategory(int btype);
int __cdecl gm_MapEntityStatRange(int);
short* __cdecl gm_GetEntityTableEntry(char*);
extern float g_const_42_0;
int __cdecl gm_RandomMod(unsigned short range);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_AssignBuildingOwner(unsigned char*, unsigned short, unsigned int);
int __cdecl gm_WalkEntityChain(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_GetOppositeStatIndex(int);
void* __cdecl gm_AddOrAccumulateObject(int, int, int);
/* 189 4-byte entries per object type; only the low word of each entry is read. */
extern unsigned int g_entity_slot_table[];
extern float g_const_0_01; /* 0x10025fb8 */
extern float g_const_1_5; /* 0x10025fb4 */
extern float g_const_2_2; /* 0x10025fb0 */
extern float g_const_0_06875; /* 0x10025fac */
extern float g_const_896_0; /* 0x10025fa8 */
extern double g_const_1_over_720; /* 0x10025fa0 */
extern float g_const_0_0; /* 0x100256cc */
extern float g_gv_const_57c8; /* 0x100257c8 */
extern double g_const_half; /* 0x100257d0 */
double __cdecl gm_CalculateProductionValue(int, unsigned char);
extern unsigned char g_current_season;
int __cdecl gm_SumBuildingProductionValues(char*, int);
int __cdecl gm_EntityQuerySum(int);
int __cdecl compute_size(char*); /* 0x10019d00 */
char* __cdecl gm_FindEntityByOwner(int); /* 0x10019c60 */
int __cdecl gm_GetMsgField(char*, char*); /* 0x10019cd0 */
int __cdecl ahm_LookupEntityInTable(int); /* 0x1000c670 */
extern float g_const_1_over_32767;
double __cdecl gm_RandomFloat01(void);
extern float g_const_1_0;
extern float g_const_neg_1_0;

/* Allocates and initializes a game entity structure. Allocates
 * memory via m_AllocTracked and zeroes the initial fields. */

// FUNCTION: SERVER 0x100196c0
// gm_QueryEntitySum

int __cdecl gm_QueryEntitySum(int entity, unsigned int obj_type)
{
	short* ent;
	int total;

	total = 0;
	ent = gm_StartEntityQuery(entity, 1, 4, 9);
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
//   NEAR_MATCHING 386/396 matched, 4 differing instructions out of 123.
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
//   - `acc = quot; acc = acc * mod_value; value = (float)(acc * g_const_half)`
//     yields `fxch st(1)` / `fmulp st(1)` and drops the dead `fstp st(0)`,
//     disproving the earlier note that no source form pops there.
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
//   and "p"/"s"/"w" off all hold 386; "p" on, "s" on, "t" off, "y" off and
//   "g" off collapse the body). CFLAGS remain inert at both 378 and 386:
//   /G3 /G4 /G5 /Ox /Gy /Oi- /Ob0 all score identically, /G6 /Op /O1 /Ot
//   collapse.
//
//   Residual 4 instructions (386/396, two transpositions):
//   - [67..68] the target emits `fxch st(1)` BEFORE `cmp byte ptr [esi],0x17`;
//     the candidate emits the compare first. Same instructions, same bytes.
//   - [115..116] the target emits `pop ebp` before `fmul [esp+0x14]`; the
//     candidate emits `fmul [esp+0x18]` before `pop ebp`. The displacement
//     difference is the pending `pop`, not a frame-size difference.
//
//   Residual at 391/396: ONE adjacent transposition, offsets 228..232.
//   Target `d9c9 803e17` (fxch; cmp byte ptr [esi],0x17) against the
//   candidate's `803e17 d9c9`. Every other instruction matches.
//
//   The fxch slot and the folded compare are mutually exclusive across every
//   shape measured (2026-09-08, ~330 compiles, scripts in .scratch/pv-x87/):
//   - Scaling by g_const_half through a FLOAT local (`mod_value` or `value`)
//     folds the compare to `cmp byte ptr [esi],0x17` but schedules it one slot
//     ahead of the fxch. This is the 391 shape.
//   - Scaling through a DOUBLE local (`p2_wide`, `acc`, a block-scoped temp)
//     puts the [esi] access after the fxch, matching the target's order, but
//     msvc6 then splits it into `mov al,[esi]` plus a later `cmp al,0x17`,
//     which is one byte longer: obj 397, SIZE_MISMATCH at 255.
//     A volatile `value` store lands the fxch correctly too but sinks the
//     compare two slots, past `fmulp`/`fstp` (387/396, 3 structural diffs).
//   Ruled out against the 391 base, each holding 391 or worse:
//   - CFLAGS: /G3 /G4 /G5 /GB /Ox /Ot /Oa /Ow /Gy /Oi- /Ob1 /QIfdiv- emit
//     BYTE-IDENTICAL objects (compared hex, not just the score), so no flag
//     reaches this scheduling decision. /G6 /Op /Oy- /O1 /Od collapse.
//   - `#pragma optimize`: 20 combinations. "a" plus any of g/t/w/y hold 391;
//     "s" on, "t" off, "y" off, "g" off, "p" on each collapse the body.
//   - All four msvc6 service-pack images (sp1..sp4) produce the identical
//     391/396 object, verified on an isolated probe (.scratch/pv-x87/probe.c)
//     that reproduces this function without windows.h.
//   - Local declaration order: 14 permutations, all inert.
//   - Compare spelling: unsigned/signed char, `entity[0]`, `0x17 ==` reversed,
//     `!(x != 0x17)`, `(int)` cast, via a `dp`/`cp`/`slot_p` alias, via a
//     hoisted int local placed before, between or after the FP statements.
//     `- 0x17 == 0`, `^ 0x17 == 0` and `& 1` add bytes.
//   - Branch shape: switch, goto, if/else, duplicated arms, nested block,
//     `do {} while (0)`, block-scoped temp, empty statement separator.
//   - Reaching definitions of `mod_value` (doc section 42): preset before the
//     if, inverted polarity, while-loop form, 57d0 duplicated into both arms.
//     All regress (319..391).
//   - Loop body reassociation and the else-arm constant form: inert.
//   - Filler integer work in the pre-fxch slot (param2 reload, mask, min_val,
//     the +0x38 read, the cp lea) placed before or between the FP statements:
//     inert. A volatile param2 read there collapses the whole function.
//   - 312 generated tail permutations (.scratch/pv-x87/gen2.py, gen3.py) over
//     scaled-local x numerator-local x product form x compare form x return
//     form x filler: none exceeds 391.
//
//   Second pass, 2026-09-08 (.scratch/spiel622-x87/), 700+ further compiles,
//   still 391. What it adds to the picture:
//   - The `fxch` is a removable stack fixup, not a fixed instruction. Making
//     the scaled double the destination of the merge multiply
//     (`acc = (double) mod_value * g_const_half; mod_value = (float)(acc * quot)`)
//     drops it entirely for a 394-byte object, and `value = (float)(acc * quot)`
//     replaces `fmulp st(1)` with the non-popping `fmul st,st(1)` at 385/396.
//     So the question is not how to move the fxch but why msvc6 ranks the
//     folded compare ahead of it, and no measured shape reverses that ranking.
//   - The compare and the fxch trade places together, never separately: every
//     variant lands in one of four classes, `cmp; fxch` (391), `fxch; mov al`
//     (obj 397), `fxch; fmulp` with the compare sunk past `fstp` (387), or no
//     fxch at all (394/385). The target's `fxch; cmp` is in none of them.
//   - `#pragma optimize("a")` does not decide the slot: dropping it holds the
//     same `cmp; fxch` order at 383, so the epilogue lever and this one are
//     independent.
//   - Additionally ruled out here: `/GX /GR /Gs /GF /Gf /Zp1 /Ob2 /Oi /Og /Gi`
//     (byte-identical objects, mismatch sets compared by hash, not score);
//     duplicating the 57d0 multiply into both arms (msvc6 duplicates the
//     `fmul` rather than cross-jumping, so the merge block boundary does not
//     move); a double accumulator in the arms (241 or worse, the float
//     round-trip is load-bearing); eight nested association trees with no
//     temp; the compare's pointer provenance via `cp`/`dp`/`slot_p` and via a
//     late-defined pointer; reading the 0x17 byte at the top of the function
//     into a char/uchar/int local; the loop's own eager-fxch accumulate shape
//     mirrored onto the merge; 630 further generated permutations over
//     scale x numerator x product x compare x return x filler x filler
//     position (.scratch/spiel622-x87/gen.py, gen2.py).
//   - Toolchain re-check on this exact shape: sp1 and sp4 give the identical
//     391 object, sp2 gives 380. No service pack reorders the pair.
//   The obstacle is msvc6's FP-stack allocator deciding the fxch position from
//   the scaled operand's type, and the same type choice decides whether the
//   compare folds. No C89 spelling separates the two.
//
//   2026-09-10: search closed. `rebrew match` ran 100 generations without
//   beating the residual and `rebrew prove` established the two forms
//   equivalent (EAX, 1 original state vs 1 compiled state), so the function is
//   recorded PROVEN rather than byte-identical. The 5-byte delta stays in the
//   linked artifact.
//
//   Notes below predate the pragma; scores quoted in them are against 378.
//   Re-measured against the 386 base, all still inert or worse: the return
//   expression reassociated five ways (357..386), `value` copied to a separate
//   float for the tail multiply (358), `p2_wide` read through a volatile alias
//   (374), a volatile `[esi+0x38]` store (372), a volatile home store (378),
//   the mask before the store (369), the `dp` alias for the store (89), the
//   compare widened/unsigned/via a hoisted local (inert), the loop as a `for`
//   (382), and every reassociation of the g_const_half multiply (380..386,
//   the 372-shape now reaches 380 but reintroduces a dead `fstp st(0)`).
//   Hoisting integer work (`i = 0`, the `p2_home` alias, a dead `weight`
//   assignment) above the compare to give the scheduler something to place
//   there is inert.
//
//   Superseded residual notes (7 instructions, 378/396):
//   - [67..70] 378 shape: mod_value scaled by g_const_half as a float store,
//     then acc = quot; value = (float)(acc * mod_value). Emits qword fmul
//     before fxch/fmulp and keeps fstp/jne. Leftover: cmp [esi],0x17 one
//     instruction early (fmul qword; cmp; fxch; fmulp). kind=*entity after
//     the multiply is inert; hoisting cp=entity+0x2e there is 91. Reading the
//     byte into an int local ahead of the multiply is 255 at SIZE_MISMATCH;
//     `unsigned char` instead of `char` at the compare is inert.
//   - [111..116] the epilogue emits the same instructions in a different
//     order: candidate `mov [esi+0x38]` / `mov [esp+0x20],ebp` / `pop edi` /
//     `fmul [esp+0x18]` / `pop ebp` against the target's `pop edi` /
//     `mov [esp+0x1c],ebp` / `mov [esi+0x38]` / `pop ebp` / `fmul [esp+0x14]`.
//
//     The frame sizes are EQUAL, contrary to an earlier note here. Both
//     versions address the same two bytes; the displacements differ only
//     because the target has already popped edi when it forms them.
//     Homed ebp: candidate [esp+0x20] pre-pop == target [esp+0x1c] post-pop.
//     Value slot: candidate [esp+0x18] pre-pop == target [esp+0x14] post-pop.
//     The `fild [esp+0x1c]` in the middle of the block is byte-identical in
//     both, which pins the alignment. There is no extra local to remove, so
//     do not chase frame size here: the delta is purely the scheduler
//     interleaving the two pops with the two stores.
//
//     Measured this pass against 378, none kept: `[esi+0x38]` stored from an
//     int temp after the mask (369); the mask before the `[esi+0x38]` store
//     (369, hoists `and ebp` ahead of the ftol call); a volatile `[esi+0x38]`
//     store after the mask (374, 8 structural diffs against 7); `value` used
//     directly instead of the `mod_value` float temp (373); splitting the
//     mask into `param2 &= 0xff` plus the home store (inert); an `int*` alias
//     for the +0x38 store (inert); moving the `p2_home = &param2` alias
//     declaration (inert); a dead `cp` store to shorten edi's live range
//     (inert, eliminated). Reusing `divisor` as the loop slot scores 364.
//
//   The `unsigned char` second parameter in the forward declaration above is
//   load-bearing for gm_SumBuildingProductionValues (0x100198b0, 218/355) and
//   gm_EntityQuerySum (0x10019a70, RELOC); widening it to `int` regresses both.
//
//   Residual re-audit 2026-09-09 (391/396, one transposition at 228-232:
//   target `fxch st(1); cmp byte ptr [esi],0x17`, candidate the reverse).
//   22 new probes across five categories, all 391 or worse; the order is a
//   pure msvc6 scheduler choice with no C89 spelling:
//   - per-statement #pragma is impossible inside a function (C2156); the only
//     scope is the whole function, and dropping "a" regresses the epilogue
//     (383) while leaving the transposition intact.
//   - every statement/sequence split around the merge is inert at 391.
//   - scaling through the p2_wide double moves the [esi] access into the
//     target slot but splits it into mov al/cmp al (obj 397, 255).
//   - a volatile value store (387) puts the fxch first but sinks the folded
//     cmp past fmulp+fstp: plain store lets the load hoist fully to slot 1,
//     volatile blocks it entirely, the target needs the partial hoist.
//   - duplicating the 57d0 scale into both arms grows obj to 403.
//   Cross-binary: only 5 fxch in the whole .text; no other function shows the
//   folded-cmp-after-fxch order, so there is no C precedent to copy.
#pragma optimize("a", on)
double __cdecl gm_CalculateProductionValue(int entity_index, int param2)
{
	char* entity;
	char* record;
	float value;
	double quot;
	float mod_value;
	int i;
	int min_val;
	int divisor;
	int weight;
	int* dp;
	unsigned short comp;
	unsigned short* cp;
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
	dp = &divisor;
	quot = quot / *dp;
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
	/* Copying quot into a separate accumulator makes that accumulator the
	   destination of the multiply, so msvc6 emits `fxch st(1)` / `fmulp st(1)`
	   and consumes quot. Written as one expression it keeps quot live and
	   emits the non-popping `fmul st,st(1)` plus a trailing `fstp st(0)`.
	   The g_const_half multiply has to stay last: applying it before the
	   exchange makes msvc6 unfold the 0x17 compare below into
	   `mov al,[esi]` / `cmp al,0x17`, which is 3 bytes longer.
	   Re-tested 2026-09-04 against the target's [67..70] order (the qword
	   multiply BEFORE the fxch).  Four formulations, all worse than the 374
	   below, so reassociating this site is a dead end:
	     acc = mod_value * g_const_half; value = (float)(acc * quot);    372
	     acc = mod_value; acc = acc * g_const_half; ...                  254
	     acc = quot; value = (float)(mod_value * g_const_half * acc);    254
	     acc = mod_value * g_const_half; acc = acc * quot;               372
	     acc = 57d0*mod_value; kind=*entity; acc*=quot; if(kind==0x17)  372
	     (qword fmul matches, cmp [esi],0x17 too early, fmulp becomes
	     fmul st(1)/fstp).  acc *= 57d0 then *mod_value: 248 SIZE 398.
	     fused acc*57d0*mod_value: 255 SIZE 397.
	     372 muls + volatile entity[0] compare: 258 SIZE 397 (unfolds to mov al).
	     acc=quot; acc*=(mod_value*57d0); value=(float)acc: 259 SIZE 397
	     (qword fmul/fxch/fmulp match, unfolds 0x17 to mov al).
	     same with delayed fstp after the if: 273 SIZE 392 (cmp/fmulp
	     match, fstp vs jne, CFG 88.4).  volatile fstp before cmp
	     restores 374 but moves fstp before cmp.
	   The 372 pair reaches the target's operand order but loses two matches
	   in the epilogue, so the multiply order and the epilogue instruction
	   order are coupled; they cannot be fixed independently.
	   Folding the two assignments into `value = (float)(acc * mod_value)`
	   holds 378 with the same 7 structural diffs and one less live local. */
	acc = quot;
	mod_value = (float) ((double) mod_value * g_const_half);
	value = (float) (acc * mod_value);
	if (*(char*) entity == 0x17) {
		mod_value = value;
		return (float) ((double) mod_value * g_const_2_2);
	}
	cp = (unsigned short*) (entity + 0x2e);
	/* A `while` with the counter incremented ahead of the pointer gives the
	   target's `inc ebx` / `add edi,2` order; a `for` header emits them the
	   other way round. */
	i = 0;
	while (i < 4) {
		comp = *cp;
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
			*slot_p = (int) cp[-4];
			*sub = *sub * *slot_p;
			*slot_v = (int) *(unsigned short*) (entity + 0x36);
			*sub = *sub / *slot_v;
			*sub = *sub + value;
			value = (float) *sub;
		}
		i++;
		cp++;
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
//   instead of overwriting `q`, because the original keeps the outer query in
//   esi across the branch; the epilogue multiply order is
//   `(param2 * g_const_0_01) * total`, which emits fild/fmul/fimul, where the
//   `(double)` casts emitted fld/fimul/fimul; and the inner call's `q+0x14`
//   load stays inside the argument list, which is what emits the original's
//   `push eax` / `mov eax,[esi+0x14]` / ... / `push eax` schedule. Hoisting
//   that load into a local (`qbase`) materialises it into ecx before the
//   pushes and costs 5 bytes.
//   The last fix was the whole-function esi/edi role swap that made the hoist
//   look necessary. It is decided by the OUTER call's first argument: reading
//   `*q` into an `int` local and passing that, instead of passing `*q`
//   directly, puts the query in esi and the cursor in edi as the original has
//   them, and it also reproduces the original's
//   `mov dl,[esi+0x12]` / `xor eax,eax` / `mov ax,[esi]` order. The local's
//   width matters: `unsigned short` emits an `and eax,0xffff` widen and
//   reorders the two field reads (SIZE_MISMATCH, 167); `int` is exact.
//   Dead ends measured on the hoisted shape (all 350, register swap right but
//   schedule wrong): dead-hoist beside the inline load, `register int`,
//   comma/assignment folded into the argument, address-only and `int*`/`char*`
//   alias hoists, `((int*) q)[5]`, `*(int*)(q + 0xa)` in short units, hoisting
//   the masked id instead, and hoisting the outer call's `obj+0x5d`.
//   Dead ends on the inline shape (all 343, schedule right but registers
//   swapped): declaration order (all 10 positions for comp_ptr), `register`
//   qualifiers on either pointer, swapping the init order of `q` and
//   `comp_ptr` (336), a `volatile int*` inline load (337), `q`/`sub`/
//   `have_query` retyped, a `!=` loop bound, an end-pointer loop bound, and
//   hoisting `next_comp` above the branch. A redundant `if (q != 0)` guard
//   around the inner call flips the registers but reverts the schedule, and
//   `q == comp_ptr` style dead compares flip them at the cost of a
//   `sub esp,8` frame and a `have_query` spill.
int __cdecl gm_SumBuildingProductionValues(char* obj, int param2)
{
	char* record;
	unsigned short* q;
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
	q = NULL;
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
				q = gm_StartEntityQuery(*(int*) (obj + 0x5d), 1, 0, comp & 0x7fff);
				if (q != NULL) {
					q_slot = *q;
					total = (int) (gm_CalculateProductionValue(q_slot, *(unsigned char*) ((char*) q + 0x12)) + (double) total);
					if (i < 0x3f) {
						next_comp = *comp_ptr;
						if (((char*) g_item_def_table)[(next_comp & 0x7fff) * 0x41] != 2 && ((char*) g_item_def_table)[(next_comp & 0x7fff) * 0x41] != 6) {
							have_query = 1;
						}
					}
				}
			}
		} else if (q != NULL) {
			sub = gm_StartEntityQuery(*(int*) ((char*) q + 0x14), 1, 0, comp & 0x7fff);
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

// FUNCTION: SERVER 0x10019A20
// gm_AccumulateTyped2

int __cdecl gm_AccumulateTyped2(char* entity)
{
	int sum;
	int result;
	unsigned int idx;
	sum = 0;
	idx = (unsigned int) (unsigned char) g_current_season * 189;
	result = (int) gm_StartEntityQuery(
	    *(int*) (entity + 0x178), 1, 0, (int) (unsigned short) g_entity_slot_table[idx]);
	if (result) {
		do {
			sum += *(int*) (result + 0xe);
			result = (int) gm_NextEntityQueryMatch();
		} while (result);
	}
	return sum;
}

/* Runs an entity query and sums a field across all results.
 * Combines query iteration with field accumulation. */

// FUNCTION: SERVER 0x10019a70
// gm_EntityQuerySum

int __cdecl gm_EntityQuerySum(int arg1)
{
	int sum;
	void* head;
	unsigned short* q;

	sum = 0;
	head = gm_StartEntityQuery(*(int*) (arg1 + 0x5d), 2, 6, sum, 0x2a);
	if (head != NULL) {
		q = gm_StartEntityQuery(*(int*) ((char*) head + 0x14), 1, 5);
		if (q != NULL) {
			do {
				sum = (int) (gm_CalculateProductionValue(*(unsigned short*) q, *(unsigned char*) ((char*) q + 0x12)) + (double) sum);
				q = gm_NextEntityQueryMatch();
			} while (q != NULL);
		}
	}
	return sum;
}

/* Resolves a parent entity reference. Follows entity chain
 * links to find the parent. Returns parent pointer. */

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

/* Accumulates values along an entity chain. Walks linked
 * entities and sums a specified field. */

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
			ent = (int) FindNextFilteredEntity();
		} while (ent);
	}
	return total;
}

// DATA: SERVER 0x100358a2
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

/* Finds an entity by its owner. Searches for an entity
 * whose owner field matches the given ID. */

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
	int p;
	char* r;

	r = NULL;
	if (arg1 == 0) {
		return r;
	}
	i = 0;
	p = 0x100358a2;
	while (p < 0x1009aca2) {
		if (*(char*) (p + 0x162) != 0 && *(int*) (p + 0x16a) == arg1) {
			if (*(char*) p == 6 || *(char*) p == 7 || *(char*) p == 1 ||
			    *(char*) p == 2) {
				r = (char*) (0x100358a0 + i * 0x21c);
				break;
			}
		}
		p += 0x21c;
		i++;
	}
	return r;
}

/* Gets a message field from a command packet. Reads a
 * specific field from the packet's payload section. */

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

char s_gm_KannObjektHergestellt___pCObj_10031628[] = "gm_eval_SlotVoll(): Lager ist in keinem Geb\344ude";

// FUNCTION: SERVER 0x10019d30
// gm_KannObjektHergestellt
//   RELOC 407/407. The earlier note blaming register allocation was wrong; the
//   source had three separate bugs, each costing the rest of the function:
//   the second and third arguments were transposed (the item id is arg2, not
//   arg3, so the query and item-table index used the wrong value), the
//   gm_GetMsgField arguments were in the wrong order, and the three
//   "cap reached" exits were spelled as separate returns. Merging them into
//   one shared tail (the goto below) gives the single `xor eax,eax` epilogue
//   and the single min() block the original emits, closing 146/407 to 407/407.

int __cdecl compute_size(char* pkt, int param2);

int __cdecl gm_KannObjektHergestellt(char* obj, int item_id, int requested)
{
	char* pkt;
	char* ent;
	char* record;
	int is_cat2;
	int is_producer;
	int size;
	int count;
	int msg_field;
	void* q;
	int q_id;

	pkt = obj;
	ent = (char*) gm_EntityAccumulate((void*) pkt);
	if (ent == NULL) {
		LogMessageInternal((char*) 0x10031004, 0x31de, (char*) 0x10031628, 1);
		return 0;
	}
	is_cat2 = (gm_GetBuildingTypeCategory((unsigned char) *ent) == 2);
	size = compute_size(pkt, item_id);
	q = gm_StartEntityQuery(*(int*) (pkt + 0x14), 1, 0, item_id);
	if (q != NULL) {
		msg_field = gm_GetMsgField(pkt, (char*) q);
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
		q = gm_StartEntityQuery(*(int*) (pkt + 0x14), 1, 5);
		if (q != NULL) {
			do {
				q_id = *(unsigned short*) q;
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
				q = gm_NextEntityQueryMatch();
			} while (q != NULL);
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
	q = gm_StartEntityQuery(*(int*) (pkt + 0x14), 1, 5);
	if (q != NULL) {
		do {
			count++;
			q = gm_NextEntityQueryMatch();
		} while (q != NULL);
	}
	if (count >= *(unsigned char*) (pkt + 0x1c)) {
		return 0;
	}
limited:
	return size < requested ? size : requested;
}

// FUNCTION: SERVER 0x10019ed0
// gm_CheckInventoryCapacity
//   NEAR_MATCHING 291/395, obj 395 == target size (was SIZE_MISMATCH 134/395).
//   Everything from offset 0x8f to the end is byte-identical; the only
//   remaining differences are the seven relocation slots and the 0x1a-0x8e
//   block described at the bottom.
//
//   Two statement-level fixes took 278 -> 291, each measured on its own:
//     - `in_list = 0;` before `cap = 0;` instead of after. The zero-fill of
//       list[7] then comes from ebp as the target has it (`mov [esp+0x2c],ebp`
//       at 0x10019f2c) rather than esi, and the first 26 bytes match rather
//       than the first 20. 278 -> 279.
//     - seeding the scan through an escaped pointer (`pl = list; ppl = &pl;
//       elem = **ppl;`) instead of `elem = list[0]`. Taking pl's address stops
//       msvc6 constant-propagating list[0] == 8, so it no longer peels the
//       first compare into `cmp edx,8` with the loop entered at &list[1];
//       the target holds 8 in a register (`mov eax,8` at 0x10019f40), enters
//       at &list[0] via `lea ecx,[esp+0x10]` and tests at the loop top.
//       279 -> 291, still at exactly 395 bytes.
//
//   The previous body had two paths that disagreed with the binary. Both were
//   read directly out of original/server.exe, not inferred from a score:
//
//     - `count >= 6` returned 3. The target's 0x1001a02d `jge` jumps PAST the
//       `mov ebp,3` at 0x1001a033 (raw bytes at 0x1001a02a:
//       83 fe 06 7d 10 8b 44 24 3c bd 03 00 00 00), so that path reaches the
//       epilogue with ebp still 0 from the prologue's `xor ebp,ebp` and
//       returns 0. An older note here flagged this as an unresolved question
//       for the prover; the raw encoding settles it.
//
//     - the clamp was applied on some shared paths and not others. The target
//       has exactly one clamp epilogue at 0x1001a03f
//       (33 c0 5f 85 ed 0f 9c c0 48 5e 23 c5), reached by the query path, the
//       used+requested path and the count path alike. Only the `type_byte==9`
//       return (0x10019f32) and the three early exits (0x1001a051, which
//       returns a literal 0) bypass it. Routing the shared paths through one
//       `return ((cap < 0) - 1) & cap;` is what the binary does. An older note
//       rejected this shape as "WRONG"; that note was comparing against the
//       then-current C body rather than against the binary.
//
//   Structure that had to change with it, each measured:
//     - the used+requested branch spelled as if/else assigning `cap` and
//       falling into the shared clamp, not as an early clamped return (the
//       early-return form compiles 394 bytes and scores 220 raw).
//     - the count<6 branch spelled `if (requested > 3) cap = 3; else cap =
//       requested;` rather than `cap = 3; if (requested <= 3) cap = requested;`.
//       The `cap=3`-first form emits `cmp eax,ebp` where the target has
//       `cmp eax,3` and costs a byte: 209 raw against 250 raw.
//
//   Residual, the 0x13-0x8e block. The target computes the entity address into
//   eax (`mov eax,edi; add eax,ecx`) and reads `mov al,[eax]`, keeping the byte
//   in al across the list stores; we emit the SIB form `mov al,[edi+ecx]` and
//   then spill it with `mov [esp+0x38],al`, reloading it as `mov edx,[esp+0x38]`
//   at the scan. That spill also makes the scan compare against an immediate
//   (`cmp edx,8`) where the target holds 8 in eax (`mov eax,8; cmp eax,edx`),
//   and puts our zero-fill of list[7] in esi where the target uses ebp.
//
//   2026-09-08 (291 -> 293): the list is written as eight element stores with
//   the entity-byte read placed between list[2] and list[3] instead of before
//   the whole block. The target interleaves the read into the stores
//   (`mov [esp+0x14],0xc` / `mov al,[eax]` / `mov [esp+0x18],0x12` at
//   0x10019ef8-0x10019f02), and that position is the only one that reproduces
//   its `xor ebp,ebp` placement ahead of the stores. Read position measured at
//   every one of the nine slots: slot 3 gives 293, slot 4 gives 292, the
//   initialized-array form and slots 0/1/2/5/6/7/8 all give 291 or less.
//   Everything from 0x8f to the end stays byte-identical.
//
//   2026-09-08 grid results, all inert at 293 (measured, none kept): twelve
//   address spellings (`entity_index * 0x41` as one multiply, `<<6`, an int
//   address local, base+index split into two statements, indexing base by
//   entity_index, an escaped `char**`); ten 9-test and mask spellings; eight
//   scan spellings (while-rotation, sentinel held in a variable, sentinel
//   compared against `cap`, type on the left, pre-increment, the walk done
//   through `*ppl`); ten declaration orders. Five type widths for the byte
//   local crossed with three read positions: only `unsigned char` and `char`
//   hold 395 bytes, `int`/`unsigned int`/`unsigned short` all compile 388-390
//   and collapse to about 55 raw. The spill survives all of them, so it is not
//   reachable by reordering or retyping at this statement granularity.
//
//   2026-09-06 pass (no score change, kept 291): the mov/add form IS reachable
//   (split list stores + adjacent `type_byte = entity[0]; raw = entity[0];`
//   CSEs to one `mov al,[eax]` with `mov eax,edi; add eax,ecx`, no spill), but
//   it trades against two invariants that grid search proved mutually exclusive:
//   in_list=0 at stmt1 gives the target's xor-ebp-first order and list[7]=ebp
//   yet flips idx/in_list to esi/edi; in_list=0 post-guard keeps edi roles yet
//   emits xor-esi-first with list[7]=esi. 27 combos of in_list/cap positions,
//   declaration order, base removal, cap-late, in_list=cap all measured, none
//   gives ebp-first + edi + ebp-list7 together.
//   The scan entry `mov eax,8; cmp eax,edx` was never reproduced: an `elem = 8`
//   loop entry folds to `cmp $0x8` under every spelling tried (for/while/
//   do-while/goto/index/deref/load-entry/int-pun/`(raw & 0xff)` compare,
//   /O1 /Ot /Og- /Od /Ox, `#pragma optimize("g"/"t", off)`), including a
//   20-line minimal scan that still peels. An if/else `type = 9 / raw & 0xff`
//   yields the `mov edx,eax` copy yet still folds elem. Probes in
//   .scratchwork/pv_{M1,R1,H1,E2,E5,K1,K2,L1,M1,N0-N4,Q1-Q2,TS1-TS2}.c,
//   pv_BL{...}.c, mini2/mini_B*/mini_scan/pun.c, flag_{G5,G6,g_off,...}.c.
//
//   Measured this pass against the 250-raw body, none kept: a volatile read of
//   the entity byte (25 raw, 398 bytes); splitting the address into two
//   statements or into base+index locals (250, inert); `entity_index * 0x41`
//   as one multiply (250); `elem = 8` as a literal instead of `list[0]` (250);
//   a `while (elem != 0)` loop rotation (31 raw, 397 bytes - it does emit the
//   target's `mov eax,8` / `lea ecx,[esp+0x10]` / `cmp eax,edx` scan head
//   exactly, but loses the prologue); reading `*pl` instead of `pl[1]` (41 raw,
//   396); the sentinel compared against `in_list` or `cap` to share a zero
//   register (250, inert); the list written as eight element stores with
//   list[7] sourced from `cap` (250); moving `cap = 0` after `in_list = 0`
//   (251 raw, 1 byte better on the zero-fill register but no status change);
//   re-reading `entity[0]` for the mask (111 raw, 389 bytes); the 9-test
//   spelled on a plain `int` (50 raw, 389); an `(type & ~0xff) | type_byte`
//   merge (84 raw, 398).
//
//   2026-09-06 pass 2 (no score change, kept 291): a `do/while (elem != type)`
//   scan with the sentinel as a top break, the bump as `pl++; elem = *pl;`
//   and a post-loop hit test scores 292 at the same size, but every
//   post-loop spelling tried (`if (elem == type)`, `if (elem != 0)`, entry
//   `if/else` guard, hit-break-inside, compound bottom conditions) either
//   skips the list[0] entry compare or misclassifies the zero sentinel, so
//   none is semantics-preserving and all were reverted. The bottom-compare
//   form is structurally closer (one byte), but the entry compare is
//   load-bearing for correctness. Probes in .scratch/pv19{q2,r2,u2,v2,w2,
//   x2,y2,z2,a3,b3,c3,m2,n2,p2,a4b,b4,c4,d4,e4,f4,g4,h4,i4,j4,k4,l4,m4,n4,
//   o4,w3,x3,y3,z3,a2,b,c2,d2,e2,f2,g3,h3,i3,j3,k3,l3,m3,n3,o3,p3,q3,r3,
//   s3,t3,u3}.c plus .scratch/cmp.py (positional compare against
//   original/Server/server.dll at file offset 0x19ed0, no reloc masking).
//
//   The scan-above-the-early-return hoist from the previous pass is NOT kept:
//   with the corrected exits msvc6 saves all four callee-saves in the prologue
//   on its own, so the hoist is no longer needed to avoid the shrink-wrapped
//   `push ebx`, and the target reads the byte and tests it before the scan.
int __cdecl gm_CheckInventoryCapacity(char* obj, int entity_index, int requested)
{
	int list[8];
	char* base;
	char* entity;
	unsigned char type_byte;
	int type;
	int* pl;
	int** ppl;
	int elem;
	int in_list;
	int used;
	void* q;
	int count;
	int cap;

	in_list = 0;
	base = (char*) g_item_def_table + entity_index * 0x40;
	entity = base + entity_index;
	list[0] = 8;
	list[1] = 0xc;
	list[2] = 0x12;
	type_byte = entity[0];
	list[3] = 0x19;
	list[4] = 0x22;
	list[5] = 0x20;
	list[6] = 0x27;
	list[7] = 0;
	cap = 0;
	if (type_byte == 9) {
		return requested;
	}
	type = type_byte & 0xff;
	pl = list;
	ppl = &pl;
	elem = **ppl;
	for (;;) {
		if (elem == type) {
			in_list = 1;
			break;
		}
		elem = pl[1];
		pl++;
		if (elem == 0) {
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
	q = gm_StartEntityQuery(*(int*) (obj + 0x178), 1, 0, entity_index);
	if (q != NULL) {
		ahm_LookupEntityInTable(entity_index);
		used = *(int*) ((char*) q + 0xe);
		if (used + requested > 3) {
			cap = 3 - used;
		} else {
			cap = requested;
		}
	} else {
		count = 0;
		q = gm_StartEntityQuery(*(int*) (obj + 0x178), 1, 5);
		if (q != NULL) {
			do {
				if (*(char*) ((char*) g_item_def_table + *(unsigned short*) q * 0x41) != 9) {
					count++;
				}
				q = gm_NextEntityQueryMatch();
			} while (q != NULL);
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
		sub = (int) gm_StartEntityQuery(*(int*) (entity + 0x5d), 1, 0, 0xff);
		if (sub) {
			sub = (int) gm_StartEntityQuery(*(int*) (sub + 0x14), 1, 5);
			if (sub) {
				do {
					if (*(int*) (sub + 0xe) != 2) {
						*(int*) (sub + 0xe) = 2;
					}
				} while ((sub = (int) gm_NextEntityQueryMatch()) != 0);
			}
		}
		entity = (int) FindNextFilteredEntity();
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

// FUNCTION: SERVER 0x1001a110
// gm_RandomQuadratic

float __cdecl gm_RandomQuadratic(void)
{
	float rand_val;

	rand_val = (float) gm_RandomFloat01();
	rand_val = (rand_val + rand_val) - g_const_1_0;
	if (rand_val < g_const_0_0) {
		return g_const_neg_1_0 * rand_val * rand_val;
	}
	return g_const_1_0 * rand_val * rand_val;
}
int g_some_limit;
unsigned int g_1009b764;
char* g_slot_array;
unsigned int g_100a8cf8;
