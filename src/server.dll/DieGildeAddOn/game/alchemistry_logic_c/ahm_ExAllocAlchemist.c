// FUNCTION: SERVER 0x1000bdf0
#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
int __cdecl _ftol(void);

typedef int(__cdecl* dispatch_fn)(unsigned char*);

int __cdecl gm_ResolveEntityById(void** dynamic, int zero1, int zero2, int id);
int __cdecl gm_RandomMod(int range);
float __cdecl gm_RandomQuadratic(void);
void __cdecl gm_AddOrAccumulateObject(int p1, int p2, int p3);
int __cdecl gm_RefreshMarketAvailability(int season);
extern float g_color_scale;
extern int g_next_object_id;
extern unsigned char g_current_season;
extern double g_dbl_const_6d0; /* 0x100256d0 */
extern dispatch_fn g_chain_handler_table[];

extern int g_citizen_count;
extern unsigned char g_slot_table[];
extern char g_relationship_matrix_primary[];
extern char g_relationship_matrix_secondary[];
extern unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
extern void __cdecl gm_RemoveObjectByType(int*, int);
void* __cdecl m_AllocTracked(unsigned int size, const char* source);

// SIZE 0x8
typedef struct {
	int key;
	int val;
} PAIR;

// SIZE 0x14
// SIZE 0x3c
typedef struct {
	char hdr[0xc];
	PAIR entries[6];
} TGT;

/* Allocates a new alchemy entity: resolves the parent building record,
 * finds a free slot in the static entity table (0x100358a0, stride 0x21c),
 * initializes the slot from the command payload, fills the alchemy grid
 * (0x100a9820 / 0x1014d8e0) with random values, and allocates/refreshes the
 * building's alchemy data block (record->0x65). Returns the slot index or
 * 0xffff on failure.
 *
 * SIZE_MISMATCH at byte level (obj 989 vs target 1002), 452/1002 matched,
 * up from 418. Three levers moved it, all about pinning a load or a store
 * to its use site instead of letting MSVC6 hoist it:
 *
 *   - `payload` as an explicit `unsigned char*` local established just
 *     before the slot init block, read at slot+0xa. Without it the
 *     cmd_payload load floats ~12 instructions early (target keeps it in
 *     ecx at 0x1000bf38, one instruction before the movzx). 441 -> 443.
 *   - `volatile` on the slot-index store at slot[0], matching the target's
 *     `mov word ptr [esi], bp` inside the g_citizen_count RMW. 439 -> 441.
 *   - a `volatile int` read of cmd_payload at the same site before the
 *     `payload` local replaced it. 418 -> 439.
 *
 * Residual gap starts at instruction 66: the target chains the stride lea
 * through edx (`lea edx,[eax+eax*8]; lea edx,[edx+edx*4]`) where ours
 * reuses eax, and the x87 block at 0x1000bfd0 loads slot+0x1c first
 * (`fld [esi+0x1c]; fmul [const]`) where ours loads the constant first.
 *
 * Dead ends, with the score each produced: hoisting the slot+0x18 store
 * above the float math 443 -> 325; a `base` temp for the three slot+0x1c
 * reads in that block 443 -> 368; `volatile` reads of `dynamic` for the
 * 0x170/0x16c stores 443 -> 300; writing slot[0] through the `slot`
 * pointer instead of the folded 0x100358a0 + index expression 439 -> 118;
 * swapping the 0xffff and -1 stores to match 0x1000bee6 433; a shared
 * `one` constant local and a volatile g_citizen_count read, both inert;
 * routing both memsets and the two -1 stores through a single `slot` local
 * established before them, to get the target's `lea edx,[edx+g_entity_ref_table];
 * mov edi,edx` at 0x1000bef4 instead of our folded `lea edi,[...]`, 443 -> 95.
 * That fold and the `lea edx,[eax+eax*8]` vs `lea eax,[eax+eax*8]` split at
 * index 66 are both register-pressure consequences: in isolation a named
 * offset local, a base-pointer local and a regrouped `i*0x87*4` all emit the
 * candidate's form, so neither is steerable from the expression alone.
 *
 * Further dead ends: a `slot_off = slot_index * 0x21c` local shared by the
 * guard, both memsets and the two -1 stores, to force the target's single
 * edx stride at 0x1000bebb, 109; a do-while 5-iteration fill matching the
 * target's `jl` back edge at 0x1000c04b, 317; the slot+0x1c -> slot+0x18
 * copy through an int temp, matching the `mov edx`/`mov [esi+0x18],edx`
 * pair at 0x1000c014, 328 both before and after the float math; the
 * slot-index store split into the middle of the g_citizen_count RMW as at
 * 0x1000bf0c, 416; `volatile` on the grid-loop slot-word reads to defeat
 * the CSE the target does not do (0x1000c048 / 0x1000c061), 179; a
 * `ref_table` local for the second memset destination, inert (443);
 * reversing the first fmul so the field is the fld operand, 435;
 * `volatile rand_iter` 401 at obj 1011 and `volatile rand_value` 385 at
 * obj 1040, both overshooting the target's 1002.
 *
 * Also measured and reverted: dropping the `volatile` from the slot[4] = -1
 * store (keeping it on slot[0] = 0xffff) to let msvc6 materialise -1 into
 * eax first and share it with the second memset, as the target does at
 * 0x1000bee6, 443 -> 437.  Both volatiles are load-bearing; the pair is what
 * holds the two stores in the target's order at all.
 *
 * Now at 452/1002 with the slot+0xa source byte read as
 * `*(volatile unsigned char*) (payload + 0x10)`.  The `payload` local alone
 * (443) already keeps the pointer load late, but msvc6 still folded the byte
 * read into the earlier edx; qualifying the read pins the `movzx` at the
 * target's 0x1000bf3b instead of eight instructions above it, and the whole
 * slot-init store block (diff instructions 100-118) then emits the target's
 * order.  The `payload` local and the volatile read are independent: the
 * volatile read alone also scores 452, so the local is kept only because it
 * names the value.
 *
 * The residue is one instruction: the target reloads cmd_payload with a
 * separate `mov ecx,[esp+0x1c]` at diff index 99, which our code folds into
 * the register already holding it.  Everything from index 100 on is the
 * target's instruction stream shifted by that one slot.  Measured against it
 * and reverted: `*(volatile int*) &cmd_payload` as the source of the
 * `payload` local, which does force a reload but at the wrong point (417);
 * the same through a `*(unsigned char**)(volatile int*)&cmd_payload` cast,
 * inert at 452; moving the `payload` establishment above the slot-init block
 * instead of to its use, inert at 452.
 *
 * Also measured and reverted on the 443/452 bodies: `char one` instead of
 * `int one`, chasing the target's `mov dl,1` byte form, 444; a `refbase`
 * pointer local for the second memset destination, inert; the grid loop's
 * bound moved onto rand_value (`while (rand_value < 0x300)`), inert; the
 * first grid index respelled as a row multiply `btype + rand_value * 0x300`,
 * 441; operand order swapped on the second grid index, inert; a volatile
 * read of btype inside the grid loop, to force the target's per-iteration
 * reload at 0x1000c048/0x1000c061, 179; `*(volatile int*) &rand_value` and
 * `rand_value = *(volatile int*) &rand_value + 1` on the counter, both 220
 * at obj 1012; a plain `for (i = 0; i < 5; i++)` in place of the while-form
 * 5-iteration fill, 317 (the while form's note above still holds); the
 * `minus_one = -1` assignment moved below the 0xffff store, inert.
 *
 * Measured again on the 452 body and reverted, all inert: hoisting
 * `minus_one = -1` above the 0xffff store, chasing the target's `or
 * eax,0xffffffff` before `mov word ptr [esi],0xffff` at diff 79/80; routing
 * the second memset destination through a `refbase` local, chasing the
 * target's `lea edx,[edx+g_entity_ref_table]; mov edi,edx` split at diff
 * 82-84; spelling the citizen-count bump as `+ 1` rather than `+ one`.  The
 * unused `refbase` declaration was deleted (inert, 452).
 *
 * Measured this pass on the 452 body, all reverted:
 *   - splitting the citizen-count RMW so the slot-index store lands between
 *     the read and the write, chasing the target's `mov ecx,[cc]; mov dl,1;
 *     inc ecx; mov [esi],bp; mov [cc],ecx` at diff 86-90.  426 both as a
 *     function-scope local and as one scoped into its own block.
 *   - the same split on g_next_object_id, 318 at obj 994.
 *   - the slot+0x18 copy spelled as an int rather than a float, chasing the
 *     target's `mov edx,[esi+0x1c]` ahead of the `add esp,4` at diff 143.
 *     338 at obj 987, whether or not the `v` assignment moved with it.
 *   - the 5-iteration fill as `for` or as a scope-narrowed `do/while`.  An
 *     isolated probe confirms both emit the reference's exact loop, bound at
 *     the bottom with `cmp edi,5; jl` AND the reference's `[edi+esi+0x80]`
 *     SIB order, where the kept while(1) form costs a `cmp/jge/jmp` guard.
 *     In the whole function both still cascade to 318 at obj 987, so the
 *     while(1) form's 2 extra instructions buy back more downstream than
 *     they cost.  The scope-narrowing lever does not change that.
 *   - `one` declared `char` to get the target's `mov dl,1`, 444.
 *   - the grid loop's btype reads routed through `slot` (995/331) or through
 *     a volatile `slot` (997/232); `rand_iter`'s bound as `!=` rather than
 *     `<`, inert; the second grid index respelled `btype * 0x300 +
 *     rand_value`, inert; `*(volatile int*) &rand_value` on the second grid
 *     index to pin the counter to the reference's [esp+0x14] spill slot,
 *     233 at obj 1022.
 *   - a `payload` pointer local for the cmd_payload+0x10 read, inert.  The
 *     dead `payload` declaration left by an earlier pass was deleted.
 *
 * The stride lea chain at diff 66-67 (target `lea edx,[eax+eax*8]; lea
 * edx,[edx+edx*4]`, ours `lea eax,[eax+eax*8]; lea edx,[eax+eax*4]`) is not
 * steerable from the expression: five groupings of the 0x21c multiply were
 * probed against the real scan-loop context and all five emit the candidate's
 * order, so msvc6's strength reducer fixes it.
 *
 * 2026-09-06 pass (452/1002, obj 989, no change kept): hoisting the slot+0x18
 * int-copy above the float block to chase the reference's `mov edx,[esi+0x1c]`
 * ahead of the rand-result spill, 323 at obj 987; loop-scoped `int btype`
 * instead of `unsigned short`, inert; grid loop without the `base_off` local
 * (address recomputed per store), worse in isolation (`and,0xffff` widening,
 * so not transplanted); isolated grid-loop probe confirms `int` vs
 * `unsigned short` btype does not change the 16-bit read, the width comes
 * from the `*(unsigned short*)` source read, not the local.
 *
 * 2026-09-06 pass 2 (452/1002, obj 989, no change kept): the grid-loop
 * counter aliases R's spill slot across esp depths (pre-add [esp+0x18] =
 * post-add [esp+0x14] = loop-top [esp+0x18]@E-4 = [esp+0x1c]@E-8: one home,
 * verified from raw bytes, so no dead counter and no constant-R theory).
 * The float tail needs `mov edx,[esi+0x1c]` + R spill BEFORE `add esp,4`
 * with the slot+0x18 int-copy stored AFTER the float math; `rand_iter` as
 * the copy temp puts rand_iter in edi (338), a fresh `c1c` local also 338.
 * Restructuring the grid loop (btype via slot) collapses to 331 (`mov
 * bx,[esi]`), int-btype + direct second-index addresses to 210 (countdown
 * `dec eax; jne`). In isolation the loop is close (probe_bdf0q.c Z1: sub
 * al, single add esp,8, count-up) but the `= 0` stores emit `movb $0`
 * instead of the reference's `mov [ebp],bl`, and the first-index store
 * order needs the second btype read before the second zero store. The tail
 * cluster 233-285 (+13B) is cascade from the float/Grid region, not a
 * separate gap: the query call already interleaves pushes around the alch
 * store in J1 order (probe_bdf0i.c). Next: land the float tail (copy temp
 * that survives in edx without renumbering the frame) before touching the
 * grid loop. Probes: probe_bdf0*.c, probe_slot18*.c, probe_grid*.c,
 * probe_mm*.c, probe_f2.c, probe_idxmix*.c.
 *
 * 2026-09-08 pass (452 -> 493, obj 989 -> 1000): the slot and grid addresses
 * were spelled as raw literals for tables that have declared symbols.  A
 * literal makes msvc6 materialize the address in a register; the symbol form
 * lets it fold the base into the displacement, which is what the reference
 * does.  Every substitution is the same address, so behaviour is unchanged.
 *   - all five slot addresses through `g_slot_table` (0x100358a0) with the
 *     old literal's delta as a displacement: 0x100358a2 -> `+ 2`,
 *     0x100358a4 -> `+ 4`, 0x100358fc -> `+ 0x5c`.  452 -> 485, and the
 *     object grows 989 -> 1000 against a 1002 target.
 *   - the two grid tables as `g_relationship_matrix_primary` (0x100a9820)
 *     and `g_relationship_matrix_secondary` (0x1014d8e0), indexed by
 *     `base_off`.  485 -> 493.
 *
 * Both must be symbolic together; the second memset left as the literal
 * `0x100358fc + slot_index * 0x21c` scores 489, and the slot+4 store is
 * inert either way.  The store-order block around it is unchanged: on the
 * 452 body, `minus_one` established before the 0xffff store was inert, a
 * volatile `minus_one` 301, `slot` established before the 0xffff store 444,
 * a shared `slot_off` local inert, and a `refbase` local for the second
 * memset destination inert.
 *
 * 2026-09-08 pass 2 (493, nothing kept): the reference's two slot scans are
 * pointer walks (`mov eax,0x100358a0; cmp word ptr [eax],0xffff; add
 * eax,0x21c` at 0x1000be51), not the index form used here, but converting
 * them costs far more than it buys: through the existing `alch_data_ptr`
 * local 146-177, through a fresh dedicated `char*` also 146.  The index form
 * folds `slot_index * 0x21c` into the later slot addressing that the walk
 * would have to recompute, so it stays.  The residual delta is a two-register
 * role pair in the field-init block: the reference holds `one` in dl and
 * reloads cmd_payload into ecx, this compiles cl and edx.  Probed and inert:
 * `one = 1` moved down to just above the 0x1f0 store, `minus_one` established
 * before the 0xffff store, the object-id bump through a temp, the payload
 * byte hoisted into a local (479), the second memset as the raw literal
 * `0x100358fc + slot_index * 0x21c` (489).  Hoisting the citizen-count bump
 * below the slot-index store regresses to 467.
 *
 * 2026-09-08 pass 3 (493 -> 495, obj 1000 against a 1002 target): the
 * object-id and citizen-count bumps read into `seq` and `live` locals before
 * the two dynamic stores, with the writebacks after, matching the reference's
 * ecx traffic at 0x1000bf03-0x1000bf32.  The same lever moved
 * gv_ExAllocGraveyardWorker 538 -> 541; the two functions share this block
 * shape.  The pass-2 note above records the object-id bump through a temp as
 * inert - that was the bump alone, without the citizen-count read moving with
 * it.
 *
 * Unlike the graveyard sibling, the 0xffff store here does NOT need a fresh
 * volatile: it already carries one from an earlier pass and the reference's
 * `mov word ptr [esi],0xffff` at 0x1000bee9 is present.
 *
 * Residual: the register-role pair recorded above, plus a store-order window
 * at 0x1000bf3c.  Re-probed on the 495 body and reverted: the citizen-count
 * writeback moved before the slot-index store (493), `slot` established ahead
 * of both memsets so the reference's esi is live earlier (486), the 5-byte
 * fill as a do/while (351) or with the subscript operands reversed (inert),
 * the neighbour-loop stores as array subscripts (inert) or through a volatile
 * slot read like the graveyard's (422 at obj 1007), the neighbour loop in
 * for-shape (492), the first slot scan as a do/while (178), the 0x20 float
 * immediate hoisted above the quotient (inert).
 *
 * 2026-09-08 pass 4 (495, nothing kept).  The CFLAGS sweep is a no-op: /O2
 * and /Ox produce the identical 1000-byte object, /O1 and /Og are far worse
 * (146-155).  The whole field-init block is one instruction out of phase,
 * not missing anything: every store from slot+0x1f0 to slot+0x50 is present
 * and in the reference's order, shifted by one slot because the reference
 * emits `mov dl,1` early (between the citizen-count load and its `inc`, at
 * 0x1000bf05) and reloads cmd_payload into ecx afterwards, where this
 * compile emits `mov cl,1` late, after the g_next_object_id writeback.
 * `one`'s placement is inert in every position tried: at the top of the
 * counter block, above the block entirely, and after the object-id
 * writeback, all 495.
 *
 * The `slot_off` lever that moved gv_ExAllocGraveyardWorker 484 -> 526 does
 * NOT transfer: holding `slot_index * 0x21c` in a local shared by the first
 * memset, both volatile stores, the second memset and the `slot` base
 * collapses this function to 136 at obj 1017.  Unlike the graveyard sibling,
 * the repeated `g_slot_table + slot_index * 0x21c` expression is what lets
 * msvc6 fold the base into each store's displacement here.  Also re-probed
 * on the 495 body and reverted: the second memset destination through a
 * block-scoped `off` or a `refbase` pointer local, both inert; the
 * citizen-count bump split into a load then a separate `+ 1`, chasing the
 * reference's `mov ecx,[cc]; mov dl,1; inc ecx` at 0x1000bf00, inert.
 *
 * 2026-09-08 pass 5 (495 -> 787, obj 1000 -> exactly 1002).  Four levers,
 * measured one at a time:
 *   - the alch-data slot-id store moved ABOVE the alch_props byte read
 *     (495 -> 741, obj to exactly 1002).  The reference stores
 *     `mov [ecx],edx` at 0x1000c0eb before `mov al,[edi+0xf]` at
 *     0x1000c0ed; with the byte read first msvc6 kept the whole tail one
 *     slot out of phase, so the entire alch-data block from 0x1000c0c1 to
 *     the 0x1cc or-store never resolved.  This is the sibling lever from
 *     cm_ExProdObjekt: a reload that looks redundant in C is what fixes the
 *     reference's register roles.  The `alch_props` hoist comment above it
 *     described the OLD order and was wrong.
 *   - the slot+0x20 float constant store moved INSIDE the fv block, between
 *     the gm_RandomQuadratic call and the multiply chain (741 -> 747),
 *     matching the reference's `mov [esi+0x20],0x41400000` at 0x1000bfe5
 *     sitting between the `fmul` at 0x1000bfdf and the `fadd` at 0x1000bfec.
 *   - cmd_payload read into a `slot_ptr` local through `*(volatile int*)&cmd_payload`
 *     at the end of the counter block, with the slot+0xa source byte read
 *     from `slot_ptr` non-volatile (747 -> 781).  The volatile qualifier on the
 *     POINTER read (not on the byte read as before) is what forces the
 *     reference's separate `mov ecx,[esp+0x1c]` at 0x1000bf38; qualifying the
 *     byte read instead pins the movzx but leaves the pointer folded.
 *   - the object-id read as `*(volatile int*)&g_next_object_id` (781 -> 783)
 *     and then moved above the two dynamic stores (783 -> 787), matching the
 *     reference's `mov ecx,[0x10030b6c]` ahead of its slot+2 store.
 *   - the slot+0x1e4 float constant store moved above the slot+0x218 store
 *     (787 -> 789).  Every field store from slot+0x218 to slot+0x50 then
 *     matches the reference byte for byte.
 *
 * Residual 215 bytes, three separate faults, each probed to a fixed point:
 *   - field-init block one instruction out of phase.  The reference emits
 *     `mov dl,1` in the citizen-count slack at 0x1000bf09 and the slot-index
 *     store at 0x1000bf0c; this compile emits the index store first and the
 *     `mov dl,1` after the object-id writeback.  Inert on this body: `one` as
 *     char/uchar/short or dropped for a literal, `one = 1` at five positions
 *     including above both memsets, `one` sourced by both bumps, the index
 *     store between the cc read and its writeback, the cc bump as a plain RMW
 *     or `++`, `one = 1` at five further positions down the flat store list.
 *     Regressions: a volatile `one` store 338, `one` read from a const global
 *     313, the index store after the cc writeback 719, the object-id read
 *     before the cc bump 718, the `slot_ptr` read hoisted into the cc slack 179.
 *   - grid loop holds the store address in edi (also its counter) where the
 *     reference uses ebp, so all four `mov byte ptr [reg+TABLE]` stores and
 *     the `add`/`cmp` pair differ by one register field.  Inert: subscripts on
 *     both matrices, `btype` as int/uint, two separate btype locals, btype
 *     read through `slot`, `base_off` at function scope, two separate offset
 *     locals, `(btype + btype*2) * 0x100` for the second index, the rnd temps
 *     inlined or typed char, declaration order of rand_value/rand_iter/i.
 *     Regressions: a `char*` address local 365, fully inlined index
 *     expressions 365, secondary store before primary 460, `base_off`
 *     computed after the call 254.
 *   - the 5-iteration fill's `xor edi,edi` sits 75 bytes early, in the middle
 *     of the field-init stores.  The while(1) form is load-bearing: do-while,
 *     for and `while (i < 5)` each emit the reference's exact loop body
 *     (`cmp edi,5; jl` back edge, no guard) but cascade the object to 1000 and
 *     the score to 387-393.  The init cannot be sunk: `volatile int i` 329,
 *     `i` from a volatile zero load 311, counting from 0x80 328; `i = one -
 *     one` and `i = minus_one + 1` are inert.
 *
 * Also measured on the 787 body and reverted: the fv-block expression in five
 * groupings (`(v+a)-b`, `a+v-b`, `v+(a-b)` 734, a sum temp, v as double, all
 * inert or worse), the slot+0x18 copy through an int temp read before the
 * gm_RandomMod call (439) or after it (446), `alch_props` read through `slot_ptr`
 * (314), and dropping the alch-data reload between the slot-id store and the
 * float (554).
 *
 * 2026-09-08 pass 6 (789 -> 823, obj stays exactly 1002).  Three levers, each
 * measured alone:
 *   - the fv multiply folded into the local's initializer
 *     (`float fv = gm_RandomQuadratic() * *(float*) 0x100256c8`) instead of
 *     staying in the store expression (789 -> 802).  The reference emits
 *     `fmul [0x100256c8]` at 0x1000bfdf BEFORE the slot+0x20 constant store at
 *     0x1000bfe5; with the multiply left in the store expression msvc6
 *     scheduled the store first.  Moving the store between the call and the
 *     multiply (the pass-5 lever) only got the store into the block; the
 *     multiply had to move into the initializer to land ahead of it.
 *   - a `p1` local for the first slot+0x1c multiply of the slot+0x10
 *     expression (802 -> 817), which pins `fld [esi+0x1c]; fmul [const]` at
 *     the reference's 0x1000c022 instead of hoisting the constant.
 *   - the `slot_ptr` read (cmd_payload through a volatile int) moved OUT of the
 *     counter block down to its use at the slot+0xa store (817 -> 823).  The
 *     pass-5 note that placed it at the end of the counter block was the best
 *     position for the 747 body; on the 817 body the use site is better,
 *     because the reference's `mov ecx,[esp+0x1c]` at 0x1000bf48 now sits
 *     after the object-id writeback rather than before it.
 *
 * Residual 179 bytes, still the same three faults, each re-probed to a fixed
 * point on the 823 body:
 *   - field-init block one instruction out of phase (0xf6-0x17d, 90B).  The
 *     reference emits `mov dl,1` in the citizen-count slack at 0x1000bf19 and
 *     splits the second memset destination as `lea edx,[edx+table]; mov
 *     edi,edx` where this folds to one `lea edi,[edx+0x5c]`.  Inert: `one`
 *     established before either memset, sourced from `-minus_one` or
 *     `minus_one + 2`, typed unsigned char; the memset destination through a
 *     named base, an offset local, a subscript or a reordered sum; the 0xffff
 *     store sourced from `minus_one`; `minus_one` as `~0` or hoisted to the
 *     top of the function.  A 24-cell grid crossing the citizen-count slack
 *     form, three `dynamic` spellings, both object-id read forms and both
 *     dyn/seq orders is flat at 823 except for known regressions (plain
 *     object-id read 754-756).  Declaration order is fully inert across four
 *     permutations.
 *   - float tail leaks `fstp st(0)` at 0x254 (0x243-0x284, 51B).  The
 *     reference's `faddp st(1)` needs the sum's left operand dead at the add;
 *     every spelling tried keeps it live.  Inert: `p1 + v`, `p1 += v`,
 *     accumulating into `v`, a `p2` local for the second multiply, both
 *     operand orders on both multiplies, `(v + p1)` parenthesised, `v` as
 *     double.  Regressions: separate p1/p2 locals evaluated before the
 *     slot+0x18 store (469 at obj 1006), a `c1c` float local shared by the
 *     store and both multiplies (461), volatile on either multiply operand
 *     (798/800), the sibling gm_CreateEntityFromParents spelling
 *     (`field * k + (double) rand_value - field * k`, 451 at obj 998).
 *     Everything from 0x2b2 to the epilogue is this 2-byte phase shift, not a
 *     separate gap.
 *   - the 5-iteration fill's `xor edi,edi` still sits 75 bytes early
 *     (0x1c5-0x1df, 26B).  Re-confirmed on this body: for, do-while and
 *     `while (i < 5)` all cascade to 393 at obj 1000; walking 0x80..0x85 342,
 *     a down-counter 331, the test moved to the bottom 399.  `i = minus_one +
 *     1` and an `i == 5` bound are inert.
 *
 * CFLAGS re-swept on the 823 body: /O2, /Ox, /O2 /Gy and /O2 /Ob2 all produce
 * the identical 1002-byte object; /Oxs (112) and /O2 /Oy- (141) are far worse.
 * The 0x21c stride lea chain at 0xcb (reference `lea edx,[eax+eax*8]; lea
 * edx,[edx+edx*4]`, ours `lea eax,...; lea edx,[eax+eax*4]`) is unchanged by
 * five regroupings of the multiply, confirming the earlier finding that
 * msvc6's strength reducer fixes it. */

unsigned int __cdecl ahm_ExAllocAlchemist(int cmd_payload)
{
	void* dynamic;
	int building_type;
	char* slot;
	int slot_index;
	int rand_value;
	int rand_iter;
	int* query_result;
	int found_record;
	short item_type;
	int building_id;
	int alch_data_ptr;
	int alch_props;
	int one;
	int minus_one;
	int i;
	int slot_ptr;

	building_id = *(int*) (cmd_payload + 8);
	gm_ResolveEntityById(&dynamic, 0, 0, building_id);
	if (dynamic == 0) {
		LogMessageInternal((char*) 0x1002a10c, 0x449, (char*) 0x1002a19c, 1);
		return 0xffff;
	}

	building_type = (unsigned char) *(char*) dynamic;
	if (*((char*) (g_entity_type_table + building_type + building_type * 0x24c)) != 0x1e) {
		LogMessageInternal((char*) 0x1002a10c, 0x451, (char*) 0x1002a168, 1);
		goto ret_false;
	}

	for (slot_index = 0; slot_index < 0x300; slot_index++) {
		if (*(unsigned short*) (g_slot_table + slot_index * 0x21c) == 0xffff)
			break;
	}
	if (slot_index == 0x300) {
		for (slot_index = 0; slot_index < 0x300; slot_index++) {
			if (*(char*) (g_slot_table + slot_index * 0x21c + 2) == 0xf)
				break;
		}
		if (slot_index == 0x300) {
			LogMessageInternal((char*) 0x1002a10c, 0x45d, (char*) 0x1002a140, 1);
			ret_false:
			return 0xffff;
		}
	}

	if (*(char*) (g_slot_table + slot_index * 0x21c + 2) == 0xf) {
		g_citizen_count = g_citizen_count - 1;
	}

	memset((void*) (g_slot_table + slot_index * 0x21c), 0, 0x21c);
	/* volatile: keeps both stores alive past the slot[0] = slot_index
	 * write below (the reference keeps them: slot[0]=0xffff, then
	 * slot[4]=-1 with the -1 in eax reused by the second memset). The
	 * reference order is slot[0]=0xffff before slot[4]=-1; both must be
	 * volatile or MSVC6 dead-store-eliminates slot[0]=0xffff. */
	minus_one = -1;
	*(volatile unsigned short*) (g_slot_table + slot_index * 0x21c) = 0xffff;
	*(volatile int*) (g_slot_table + slot_index * 0x21c + 4) = minus_one;
	memset((void*) (g_slot_table + slot_index * 0x21c + 0x5c), minus_one, 0x20);

	slot = (char*) (g_slot_table + slot_index * 0x21c);

	/* Order follows the target from 0x1000bf03: the citizen-count bump and
	 * the slot-index store come first, then the object-id read, both dynamic
	 * stores, slot[2] and the object-id writeback.  Both counters are read
	 * into a local ahead of their stores and written back after, which is what
	 * emits the reference's ecx traffic instead of a load-inc-store pair.  The
	 * object-id read is volatile so it lands above the dynamic stores rather
	 * than being sunk to its use. */
	{
		int live = g_citizen_count + 1;
		int seq;
		one = 1;
		*(volatile unsigned short*) (g_slot_table + slot_index * 0x21c) =
		    (unsigned short) slot_index;
		g_citizen_count = live;
		seq = *(volatile int*) &g_next_object_id;
		*(int*) (slot + 0x170) = (int) dynamic;
		*(int*) (slot + 0x16c) = (int) dynamic;
		*(char*) (slot + 2) = 0;
		*(int*) (slot + 4) = seq;
		g_next_object_id = seq + 1;
	}

	*(int*) (slot + 0x1f0) = 0;
	*(int*) (slot + 0x210) = -1;
	*(char*) (slot + 0x215) = 0;
	*(char*) (slot + 0x216) = 0;
	*(char*) (slot + 0x217) = 0;
	*(int*) (slot + 0x1e4) = 0x3f800000;
	*(char*) (slot + 0x218) = (char) one;
	*(char*) (slot + 8) = 0x64;
	/* The volatile read forces the reference's separate `mov ecx,[esp+0x1c]`
	 * at 0x1000bf48 instead of reusing a register that already holds the
	 * pointer.  It belongs here at the use site, not in the counter block:
	 * the reference reloads after the object-id writeback, not before. */
	slot_ptr = *(volatile int*) &cmd_payload;
	*(unsigned short*) (slot + 0xa) = *(unsigned char*) (slot_ptr + 0x10);
	*(char*) (slot + 0x164) = 0x52;
	*(char*) (slot + 0x166) = 0;
	*(char*) (slot + 0x165) = 0;
	*(char*) (slot + 0x1f4) = 0;
	*(int*) (slot + 0x190) = 4;
	*(int*) (slot + 0x194) = 0;
	*(char*) (slot + 0xd) = (char) one;
	*(int*) (slot + 0x18c) = -1;
	*(int*) (slot + 0x20c) = -1;
	*(unsigned short*) (slot + 0x50) = 0x7fff;

	/* While-form of the 5-iteration fill: the top-tested loop shape
	 * (rather than a for or do-while) is what keeps the reference's
	 * register allocation downstream (the reference's fill is
	 * bottom-tested, but a do-while here cascades: 998 obj / 285 match). */
	i = 0;
	while (1) {
		if (!(i < 5)) break;
		*(char*) (slot + 0x80 + i) = (char) (gm_RandomMod(0x40) + 0x54);
		i += 1;
	}
	*(char*) (slot + 9) = 0;

	*(int*) (slot + 0x1c) = 0x447a0000;
	{
		/* The multiply is in the initializer and the slot+0x20 store follows
		 * it, matching the reference's `fmul [0x100256c8]` at 0x1000bfdf
		 * ahead of `mov [esi+0x20],0x41400000` at 0x1000bfe5.  Leaving the
		 * multiply in the store expression below lets msvc6 schedule the
		 * constant store first. */
		float fv = gm_RandomQuadratic() * *(float*) 0x100256c8;
		*(int*) (slot + 0x20) = 0x41400000;
		*(float*) (slot + 0x14) =
			(fv + *(float*) 0x100256c4) - *(float*) 0x100256c0;
	}

	{
		float f_tmp = *(float*) (slot + 0x1c);
		rand_value = (int) (*(float*) 0x100256bc * f_tmp);
	}
	rand_value = (unsigned short) gm_RandomMod(rand_value);

	/* `p1` names the first slot+0x1c multiply so it emits the reference's
	 * `fld [esi+0x1c]; fmul [0x100256b8]` at 0x1000c022 rather than loading
	 * the constant and multiplying by the field. */
	{
		float v = (float) rand_value;
		float p1 = *(float*) (slot + 0x1c) * *(float*) 0x100256b8;
		*(float*) (slot + 0x18) = *(float*) (slot + 0x1c);
		*(float*) (slot + 0x10) =
			v + p1 - *(float*) (slot + 0x1c) * *(float*) 0x100256b4;
	}

	/* The grid loop reuses rand_value as the +1 index counter, matching the
	 * reference: rand_value is zeroed (mov [esp+0x14], ebx) after the
	 * slot[0x10] float math, then lives in that same stack slot for the
	 * second grid index (loaded before the second gm_RandomMod call, reloaded
	 * and incremented after it; the counter is never read after the loop).
	 * NOTE (verified 2026-08-27): this formulation still strength-reduces
	 * under msvc6 /O2 (989 obj, 417 match) — reusing the spilled slot does
	 * NOT pin the allocator to the reference's per-iteration lea chains. The
	 * fixed point is documented in the metadata blocker. */
	rand_value = 0;
	rand_iter = 0;
	do {
		unsigned short btype;
		int rnd1;
		int rnd2;
		int base_off;

		btype = *(unsigned short*) (g_slot_table + slot_index * 0x21c);
		base_off = btype + rand_iter;
		rnd1 = gm_RandomMod(0x40) - 0x20;
		*(char*) (g_relationship_matrix_primary + base_off) = (char) rnd1;
		*(char*) (g_relationship_matrix_secondary + base_off) = 0;

		btype = *(unsigned short*) (g_slot_table + slot_index * 0x21c);
		base_off = rand_value + btype * 0x300;
		rnd2 = gm_RandomMod(0x40) - 0x20;
		*(char*) (g_relationship_matrix_primary + base_off) = (char) rnd2;
		*(char*) (g_relationship_matrix_secondary + base_off) = 0;
		rand_value = rand_value + 1;
		rand_iter = rand_iter + 0x300;
	} while (rand_iter < 0x90000);

	if (*(int*) ((char*) dynamic + 0x65) == 0) {
		*(int*) ((char*) dynamic + 0x65) = (int) m_AllocTracked(0x3c, (char*) 0x1002a0f8);
	}

	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	memset((void*) alch_data_ptr, 0, 0x3c);

	/* The slot-id store goes ahead of the alch_props byte read, matching the
	 * reference's `mov [ecx],edx` at 0x1000c0eb before `mov al,[edi+0xf]`.
	 * Reversing the two puts the whole alch-data block one slot out of phase.
	 * The reload of dynamic+0x65 between the store and the float is what the
	 * reference does; dropping it costs 233 bytes. */
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(int*) alch_data_ptr = *(int*) (slot + 4);
	alch_props = (unsigned char) *(char*) (cmd_payload + 0xf);
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(float*) (alch_data_ptr + 4) =
		((float) alch_props * *(float*) 0x100256ac + *(float*) 0x100256a0) * *(float*) 0x100256b0;

	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(char*) (alch_data_ptr + 8) = *(char*) (cmd_payload + 0xc);
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(char*) (alch_data_ptr + 9) = *(char*) (cmd_payload + 0xd);
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(char*) (alch_data_ptr + 0xa) = *(char*) (cmd_payload + 0xe);
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(char*) (alch_data_ptr + 0xb) = *(char*) (cmd_payload + 0xf);
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(int*) (alch_data_ptr + 0xc) = *(int*) (cmd_payload + 0x14);

	query_result = (int*) gm_StartEntityQuery(
		*(int*) ((char*) dynamic + 0x5d),
		2,
		6,
		0,
		0xff
	);
	found_record = (int) query_result;

	if (found_record != 0) {
		while (*(int*) (found_record + 0x14) != 0) {
			item_type = *(short*) *(int*) (found_record + 0x14);
			gm_RemoveObjectByType((int*) (found_record + 0x14), (int) (unsigned short) item_type);
		}
	}

	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(int*) (alch_data_ptr + 0x10) = *(int*) (cmd_payload + 0x20);

	if (found_record != 0) {
		gm_AddOrAccumulateObject(
			*(int*) (found_record + 2),
			*(int*) (cmd_payload + 0x14),
			2
		);
	}

	gm_RefreshMarketAvailability((int) (unsigned char) g_current_season);
	*(int*) (slot + 0x1cc) = *(int*) (slot + 0x1cc) | 4;

	return *(unsigned short*) slot;
}