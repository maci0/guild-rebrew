#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <windows.h>
#include <stddef.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

#pragma intrinsic(memcpy, memset)

typedef int(__cdecl* ALLOCFN)(int, int, int);

void __cdecl gm_InitObjektHersteller(void);
void __cdecl gm_KillAllSpieler(void);
extern unsigned int g_player_record_src;
extern unsigned int g_player_record_dst;
extern void __cdecl srv_SeedRandomWithTime(void);

extern int g_citizen_count;
extern unsigned char g_current_season;
extern int g_dynasty_name;
extern char g_dynasty_name_ready;
extern char g_dynasty_scan_flag;
extern int g_dynasty_scan_count;
extern char g_query_flag2;
extern unsigned char* g_query_filter_base;
extern unsigned short* g_query_cursor;
extern unsigned short* g_entity_table_end;
extern unsigned char g_slot_table[2];
extern char g_entity_state_base[2];
extern unsigned char g_entity_type_bytes[1];
#include "../../game_structs.h"

#include "entity.h"
#include "game_data.h"

#include "game_structs.h"
#define Record LinkedNode

void __cdecl m_FreeTracked(void*);
void* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);


extern int g_entity_id_counter;



int __cdecl amt_ClearEntityLinks(char* entity);
int __cdecl compute_size(char* pkt);
char* __cdecl gm_AllocObjekt(int parent_id, int type, int param3);
char* __cdecl gm_AllocRaum(char* geb, int obj_id);
int __cdecl gm_CheckEntityType(unsigned char* entity_ptr);
int __cdecl gm_FreeObjectListRecursive(LinkedNode** head);
/* Keep the original declaration position in the shared implementation. */
int __cdecl gm_GetBuildingTypeCategory(int arg1);
short* __cdecl gm_GetEntityTableEntry(char* param);

int __cdecl gm_RandomMod(unsigned short n);
int __cdecl gm_RemoveObjectByType(int a, int b);
char* __cdecl gm_SearchStruct(void);
#define SPIEL_EARLY_STAT_DECLARATIONS /* Preserve the original VC6 declaration order. */
unsigned short* __cdecl gm_ff_Objekt(int container_id, int arg_count, int first_arg, ...);


extern int g_active_player_count; 
extern unsigned char g_current_season; 

void* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

extern int g_query_filter_max_id; 
extern int g_query_filter_owner; 
extern unsigned short g_query_filter_type; 

unsigned short __cdecl gm_GetEntityType(short* entity);

extern unsigned char g_query_filter_state;

void* __cdecl gm_NextEntityQueryMatch(void);

extern int g_query_limit; 




extern int g_query_limit;      
extern int g_next_object_id;   


char* __cdecl gm_AllocateObjectSlot(void);
short* __cdecl gm_ResolveParentEntity(short*);
int __cdecl sprintf(char* buffer, const char* format, ...); 



extern unsigned char* g_query_filter_base; 

extern unsigned char g_filter_extra5; 

extern int g_query_filter_extra1; 

extern short g_query_filter_extra2; 

extern short g_query_filter_extra3; 

extern unsigned char g_query_filter_extra4; 
extern char g_dynasty_name_ready; 
extern char g_dynasty_scan_flag; 
extern int g_dynasty_scan_count; 

extern int g_dynasty_name; 


void* __cdecl gm_FindNextFilteredEntity(void);

void __cdecl m_FreeTracked(void*);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl gv_Free3Fields(void* param);
unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
int __cdecl gv_AllocGraveyardField(char* geb);
void __cdecl gv_SpawnEntities(char* geb, int param);
void __cdecl gm_SetBuildingWorkerLimits(unsigned char* geb);
void __cdecl gm_AllocBuildingDefaults(unsigned char* geb);

void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
void* __cdecl memset(void* dest, int c, unsigned int size);
void* __cdecl m_alloc(unsigned int size, const char* tag);
int __cdecl gv_AllocGraveyardField(char* geb);
void __cdecl gv_SpawnEntities(char* geb, int param);
void __cdecl gm_SetBuildingWorkerLimits(unsigned char* geb);
void __cdecl gm_AllocBuildingDefaults(unsigned char* geb);
extern int g_next_object_id; 

#pragma pack(push, 1)
struct blk14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack(pop)


void* __cdecl gm_NextEntityQueryMatch(void);

unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);

char* __cdecl gm_FindEntityByOwner(int); 

#define PTR_10035A10(idx) (*(unsigned char***) (((idx) * 0x21c) + ((int) g_slot_table + 0x170)))
#define BYTE_100358A2(idx) (*(unsigned char*) (((idx) * 0x21c) + ((int) g_slot_table + 2)))
#define DWORD_100358A4(idx) (*(unsigned int*) (((idx) * 0x21c) + ((int) g_slot_table + 4)))

extern int g_query_limit;              


int __cdecl gm_EntityAccumulate(void*);
int __cdecl gm_RemoveLinkedNodeById(int*, int);

void __cdecl gm_KillAllSpieler(void);

int __cdecl gm_MapEntityStatRange(int);
int __cdecl gm_LookupEntityRecordById(int);

int __cdecl sprintf(char* buffer, const char* format, ...); 

extern unsigned short* g_entity_table_end; 

int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_AssignBuildingOwner(char*, int, int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_GetOppositeStatIndex(int);
int __cdecl gm_MapEntityStatRange(int);
int __cdecl gm_AddObjekt(int, int, int);
void __cdecl gm_KillSpieler(int, int);


extern int g_citizen_count; 
extern double g_const_2; 
extern double g_const_0_001; 
extern double g_const_0_2; 
extern float g_const_0_6; 
extern double g_const_8; 
extern double g_const_900; 
int __cdecl gm_EntityClassCheck(int);
int __cdecl gm_IsInRange(int);
double __cdecl gm_RandomFloat01(void);
float __cdecl gm_RandomQuadratic(void);
char* __cdecl ahm_InitRandomEntity(void);
char __cdecl gm_RandomStatModifier(char);
int __cdecl gm_MapEntityStatRange(int);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl ahm_ResetEntityState(char*);
void __cdecl InitNewDynastyEntity(int, void*, unsigned short, void*);
int __cdecl sprintf(char*, const char*, ...);

struct traits5 {
	unsigned char b[5];
};

extern char g_relationship_matrix_primary[];
extern char g_relationship_matrix_secondary[];

extern const float g_const_0_25; 

extern unsigned char g_stat_table[780]; 
#define g_stat_table_30dda (g_stat_table + 95 * 6)

extern int g_next_family_index; 
extern int gm_CurrentHumanFamilyCount; 

double __cdecl eval_ObjektPreis2Credits(int, unsigned char);
int __cdecl gm_SumBuildingProductionValues(char*, int);
int __cdecl gm_EntityQuerySum(int);
char* __cdecl gm_FindEntityByOwner(int); 
int __cdecl gm_GetMsgField(char*, char*); 
int __cdecl ahm_LookupEntityInTable(int); 


extern int __cdecl rand(void);

double __cdecl gm_RandomFloat01(void);
extern const float g_const_0_0; 

extern char g_query_active;

extern char g_query_flag1;

extern char g_query_flag3;

extern int g_array_count;

/* Canonical definitions live in Units/m_alloc/m_alloc2.c. */
extern int g_alloc_report_groups;

extern void* g_array_ptr;

extern char g_stream_pool[];

extern int g_stream_count;

/* 0x10034678 */
extern int g_connection_counter;

extern int g_query_count;

extern int g_query_match_count;

extern int g_query_limit;

/* 0x10030b9c */
extern int g_dispatch_table_b[1];

/* 0x101398a0 */
extern int g_dispatch_table_a[1];

extern unsigned short* g_query_cursor;

extern char g_query_flag2;

extern int g_citizen_count;

extern unsigned char g_current_season;

extern int g_dynasty_name;

extern char g_dynasty_name_ready;

extern char g_dynasty_scan_flag;

extern int g_dynasty_scan_count;

extern unsigned char* g_query_filter_base;

/* Round-558: same-size majority types that still emit BSS commons.
 * Incomplete [] does not emit; sized arrays broke .text layout. */
extern unsigned short* g_entity_table_end;

extern int g_current_year;

extern unsigned short g_current_hour;

extern int g_clock_copy_mid;

extern short g_clock_copy_tail;

/* Indexed as `char g_entity_state_base[]` by cm_ExAllocCharacter.c and
   gm_Open.c; metadata records a 2-byte object at 0x100358a2 (round 925). */
extern char g_entity_state_base[2];

extern int g_entity_ref_table;

/* Indexed as `unsigned char g_entity_type_bytes[]` by sim.c, spiel62.c and
   gm_Open.c; metadata: 1-byte object at 0x10035a04 (round 925). */
extern unsigned char g_entity_type_bytes[1];

extern int g_next_family_index;

/* 0x1003542c */

extern int gm_CurrentHumanFamilyCount;

/* Named, in the reference's order: as a literal, the SpID format swaps two
 * stack loads in this function (3681/3689).  The spiel.c path stays a raw
 * address; gm_InitObjektHersteller emits it. */
/* 0x100256cc */

/* Allocates and initializes a game entity structure. Allocates
 * memory via m_AllocTracked and zeroes the initial fields. */

extern int g_some_limit;


extern char* g_slot_array;

/* Client-only game-clock helpers (the Gold T&L client's spiel order).  No
 * server function calls them, so /OPT:REF discards them; their absolute
 * fixups, where they have any, still count toward LINK's .reloc reservation. */

int __cdecl gm_CompareGameTime(char* a, char* b)
{
	int ta;
	int tb;

	if (*(int*) a < *(int*) b) {
		return -1;
	}
	if (*(int*) a > *(int*) b) {
		return 1;
	}
	ta = (*(unsigned short*) (a + 4) * 60 + *(int*) (a + 6)) * 60 + *(int*) (a + 0xa);
	tb = (*(unsigned short*) (b + 4) * 60 + *(int*) (b + 6)) * 60 + *(int*) (b + 0xa);
	if (ta < tb) {
		return -1;
	}
	return ta > tb;
}

int __cdecl gm_GameTimeMinutesBetween(char* a, char* b)
{
	return ((*(int*) b - *(int*) a) * 24 - *(unsigned short*) (a + 4) + *(unsigned short*) (b + 4)) * 60 -
	       *(int*) (a + 6) + *(int*) (b + 6);
}

void __cdecl gm_PackGameTime(int* src, char* dst)
{
	*(short*) (dst + 2) = (short) *src + 0x578;
	dst[1] = (char) (*src % 4) * 3 + 1;
	dst[0] = 1;
	dst[4] = ((char*) src)[4];
	dst[5] = ((char*) src)[6];
	*(int*) (dst + 6) = *(int*) ((char*) src + 0xa);
}

void __cdecl gm_UnpackGameTime(char* src, char* dst)
{
	*(int*) dst = *(short*) (src + 2) - 0x578;
	*(unsigned short*) (dst + 4) = (unsigned short) *(char*) (src + 4);
	*(int*) (dst + 6) = *(signed char*) (src + 5);
	*(int*) (dst + 0xa) = *(int*) (src + 6);
}

void __cdecl gm_AdvanceGameTime(void* clock, int unused, int hours, int minutes, int seconds)
{
	void __cdecl sim_AdvanceGameClock(void* clock, int arg2, int arg3, int arg4);

	(void) unused;
	sim_AdvanceGameClock(clock, hours, minutes, seconds);
}

int __cdecl gm_GetPackedSeason(char* packed)
{
	return *(short*) (packed + 2) % 4;
}

int __cdecl gm_GetSeason(int* time)
{
	return *time % 4;
}


/* Game function - gm_InitObjektHersteller (initialize object manufacturers)
 *
 * RELOC, 642/642, obj size equals the target (642).
 *
 * The last 28 bytes came from three changes to the scan loop, in this order.
 * Earlier rounds read the residual as "msvc6 rotates the loop and the target
 * does not"; the rotation was a symptom, and each of the three has its own
 * cause:
 *
 *   1. The rotation itself (614 -> 498, un-rotated but 2 bytes short).
 *      With `scan = record` and `entity_type = *record`, msvc6 proves the
 *      loop's first byte test true and peels it above the head. A
 *      loop-invariant head test it cannot fold defeats that: spelling the
 *      loop as `while (byte_offset < 0xca78)` with the counter break at the
 *      bottom keeps the byte test at the head, exactly as the target has it.
 *      0x58 * 0x24d == 0xca78, so the target's `cmp ebp,0xca78` is the
 *      counter bound strength-reduced onto the live byte offset, not a
 *      separate guard.
 *   2. The `mov eax,[esp+0x1c]` load hoisting above the guard (615 -> 635).
 *      Wrapping the loop in a redundant `if (byte_offset < 0xca78)` gives
 *      the loads a block that post-dominates the guard, so they sink below
 *      the `jge` where the target has them. The inner test then folds into
 *      the back edge and costs nothing.
 *   3. Bottom-branch polarity, `jge out; jmp head` against the target's
 *      `jl head; jmp out` (639 -> 642). Decided by the outer entity-type
 *      branch, not by the loop: with the `goto diff_type` skeleton msvc6
 *      lays the loop exit ahead of the same_count++ block. Spelling it as a
 *      plain `if (entity_type != prev_type) { ... } else { same_count++; }`
 *      puts the two blocks in the target's order and flips both branches.
 *
 * All six `~~` operands resolved: the four calls are LogMessageInternal
 * 0x10003640 (disps -0x120b5, -0x1212f, -0x121c6, -0x122ca from 0x100156f0,
 * 0x1001576a, 0x10015801, 0x10015905) and both absolute loads are
 * g_item_def_table 0x101de450. The four string arguments are unrelocated
 * literals and read out of original/server.exe as the file name
 * "D:\Develop\DieGildeAddOn\game\spiel.c" at 0x10031004 plus three
 * gm_InitObjektHersteller() messages at 0x1003102c, 0x10030fb0 and
 * 0x10030f54.
 *
 * Dead ends measured this round, all reverted: `volatile` on the scan-site
 * byte read (246/651) or on the outer read (239/647); deriving `scan` from
 * `record_base + byte_offset` instead of `record` (290/649); indexing the
 * scan by `record_base + idx * 0x24d` (214/662); comparing against a
 * byte-punned `entity_type` (217/641); guarding on `record_index < 0x58`
 * with the head test on the counter (223/651); the bottom test spelled
 * `continue`/`break`, `!(idx < 0x58)` or `idx == 0x58`, and both breaks as
 * `goto after_branch` (all inert at 639); `for (; byte_offset < 0xca78;
 * scan += 0x24d, idx++)` (227/638); folding the two tests into
 * `while (byte_offset < 0xca78 && idx < 0x58)` (279/641); inverting only
 * the outer test while keeping the goto skeleton (570/642).
 *
 * Levers that moved it from the 131/653 baseline:
 *   - `record_index` declared volatile homed it in the target's [esp+0x1c]
 *     slot, which made the outer loop head fall through instead of jumping
 *     to a reloaded index (131 -> 147). Removed again at 584 once the other
 *     levers below were in place; by then it cost 24 bytes (584 -> 608).
 *   - Spelling the entity-type test as `!=` with the same_count++ arm inline
 *     puts the shared tail where the target has it (147 -> 167).
 *   - Reading `idx` before `scan` in the scan loop's setup gives the target's
 *     `mov eax,[esp+0x1c]; mov ecx,edi` order (167 -> 170).
 *   - The scan loop as do/while drops the pre-test the target does not have
 *     (170 -> 181).
 *   - Zeroing `comp_count` before the record_base reload lets the target's
 *     `mov [esp+0x28],ebx; mov ebx,[g_entity_type_table]` pair emit in order
 *     and closed the size gap (181 -> 464, obj 642 = target).
 *   - The same read-order fix in the inner manufacturer scan (464 -> 466).
 *   - Accumulating into `mfr_start` and loading the table entry into its own
 *     local gives the target's `add ecx,eax; cmp ecx,eax` roles (466 -> 470).
 *   - `record_index++` before `byte_offset += 0x24d` in the outer loop tail
 *     (470 -> 478).
 *   - Writing the ten constant stores through a local base pointer
 *     (`mfr_table[8] = 0x2f`) instead of ten independent literal-address
 *     stores lets the second LogMessageInternal's four argument pushes hoist
 *     ahead of them, as the target does at 0x100156f5 (478 -> 577). The
 *     literal addresses are preserved: an `extern int g_mfr[]` declaration
 *     also hoists but emits relocations against a symbol that does not exist.
 *   - The component-count guard as unsigned `> 0` gives the target's
 *     `test al,al; jbe` at 0x10015818 where `!= 0` gives `je`; the loop-bottom
 *     compare stays signed `jl` (577 -> 578).
 *   - `j++` before the cursor advance in the inner manufacturer scan gives the
 *     target's `inc eax; inc edi; add ebp,0x24d` at 0x10015881 (578 -> 584).
 *   - Dropping the now-stale `volatile` on `record_index` (584 -> 608): with
 *     the loop bodies in the target's shape it no longer bought the [esp+0x1c]
 *     home, and its ordering pin cost 24 bytes across the outer loop tail.
 *   - Assigning `prev_type = 0x58` *after* the 0x2dc fill loop instead of
 *     before it emits the target's `mov ecx,0x2dc; mov eax,0x58` count-then-
 *     value order (608 -> 614). Written first, msvc6 materializes 0x58 into
 *     eax ahead of the rep-stosd count and the two immediates swap.
 *
 * Residual: 28 bytes in one cluster, indices 57-67. MSVC6 rotates the scan
 * loop, peeling the first byte test above the head and copying it to the
 * bottom as the back-edge; the target does not rotate and uses the counter
 * test there, reloading run_length from [esp+0x14] inside the body.
 *   - Rotating forms that keep the target's `mov eax,[esp+0x1c]; mov ecx,edi`
 *     roles but stay rotated (all 614, no change): do/while+break, while,
 *     for(;;) with either exit order, `goto` out of the enclosing block,
 *     operand order swapped, the byte hoisted to a local, an `int*` alias on
 *     entity_type, `unsigned char* scan`, `idx != 0x58` as the exit test, a
 *     `char`-aliased store on run_length, and `prev_type` moved below the
 *     scan loop.
 *   - Forms that DO un-rotate all grow the function and score far worse:
 *     recomputing the cursor as `record_base + byte_offset` instead of
 *     reusing `record`, a `char**` alias read of `record`, and a volatile
 *     read of `record` each defeat the value numbering that peels the test,
 *     but cost 7 bytes (obj 649) and swap the eax/ecx roles: 290/649.
 *     A `for (idx = record_index; idx < 0x58; idx++)` counter loop keeps the
 *     target's eax/ecx roles and un-rotates, but msvc6 then emits its own
 *     redundant `cmp eax,0x58` pre-test above the head: 9 bytes, 223/651.
 *     Volatile on the byte read un-rotates but adds `and edx,0xff` per read.
 *     That round read the peel and the register roles as coupled. They are
 *     not; see the top of this comment.
 *   - 2026-09-05 round, all 614/642 at obj 642, i.e. byte-identical output:
 *     an `int*` alias carrying every `run_length` read and write (aimed at
 *     the target's [esp+0x14] reload), a `*(char*) &prev_type` narrow store
 *     before the widening one, an `int*` alias on `prev_type` used for the
 *     store, testing the scan byte against `prev_type` instead of the
 *     equal-valued `entity_type`, and both remaining body permutations
 *     (`scan += 0x24d` first, and `idx++` ahead of `run_length++`).
 *     Re-measured on the un-rotating cursor recompute: initializing `idx`
 *     before `scan` rather than after does not move it off 290/649, and a
 *     `while (*scan == entity_type)` head with the counter break at the
 *     bottom lands on the same 290/649. A `goto`-based loop whose only
 *     back-edge is the counter test still rotates: 614/642.
 *   - 2026-09-06 round. The residual is a pure cyclic rotation: both sides
 *     emit the same eleven instructions with the same register roles and the
 *     object size already equals the target's 642, so the whole 28-byte
 *     deficit is where the block starts, not what it contains. Still 614/642:
 *     a `while (*scan == entity_type)` head with the counter break at the
 *     bottom, `for (;;)` with both breaks explicit, a redundant
 *     `if (*scan == entity_type)` wrapper above the loop, the scan byte
 *     hoisted into a block-local `int`, the compare operands reversed, an
 *     `int*` alias carrying run_length, an explicit `goto` loop, and
 *     initializing `scan` before `idx`.
 *     Regressions, all rejected: `while (idx < 0x58)` as the head and
 *     `for (idx = record_index; idx < 0x58; idx++)` both make msvc6 duplicate
 *     the byte test at the bottom (223/651); `while (idx < 0x58 && *scan ==
 *     entity_type)` likewise (223/651); a redundant `if (idx < 0x58)` wrapper
 *     224/651; `volatile` on the outer `entity_type` read 239/647; a
 *     `char* volatile` cursor 223/656; a `volatile` counter 215/659;
 *     `*scan - entity_type != 0` 234/642; a do/while with the byte test at
 *     the bottom 219/666; and aliased pre-stores through `&run_length`,
 *     `&prev_type` or `&same_count` cost 281/646, 239/642 and 285/646.
 *     The peel comes from msvc6 proving `*record == entity_type` on entry,
 *     since `scan = record` and `entity_type = *record`. Every form that
 *     defeats that proof also defeats the value numbering that keeps the
 *     cursor in the target's registers, so the block grows past 642. 614
 *     stands.
 *   - 2026-09-06 round, aimed squarely at the rotation. Still 614/642 at obj
 *     642: `goto` into the middle of a `for (;;)` so the byte test is the loop
 *     entry, the scan byte hoisted into a block-local `int` read once per
 *     iteration, the compare operands reversed with a `goto` exit past the
 *     block, re-deriving `entity_type` from `scan` inside the block, an
 *     `unsigned char` copy of `entity_type` as the compare operand, and
 *     `idx++` moved ahead of `run_length++`.
 *     Regressions, all rejected: `while (idx < 0x58 && *scan == entity_type)`
 *     un-rotates but msvc6 then adds its own `cmp eax,0x58` pre-test above the
 *     head (223/651); `for (;;)` with both breaks at the bottom 219/666; a
 *     do/while with the counter break inside and the byte test as the back-edge
 *     219/666; advancing `record` itself and restoring it after 263/646; two
 *     reaching definitions for `scan` (an `if (idx != 0)` picking between
 *     `record` and a recomputed `record_base + byte_offset`) does defeat the
 *     peel but costs 13 bytes, 218/655; `scan = record + (idx - record_index)`
 *     290/649; a `t = entity_type + run_length - run_length` launder 614/642.
 *     Dropping the enclosing `if (byte_offset < 0xca78)` and letting the
 *     `idx < 0x58` head serve as the guard emits the target's un-rotated loop
 *     instruction-for-instruction, but msvc6 then reorders the two [esp] spills
 *     above it and folds the guard to `cmp ebp,0x58`, so the block lands two
 *     bytes short and 8 instructions out of phase: 498/642 at obj 640. That is
 *     the closest any un-rotating form has come.
 *     Flag sweep (/G5 /G6 /Ob1 /Oy- /Ox /Gy) does not un-rotate either; /G6
 *     shortens the function to 186 instructions and diverges much earlier.
 *   - 2026-09-05 round, aimed at the ebp allocation rather than the rotation.
 *     The un-rotated 498/640 form's residual was localized precisely: at that
 *     form the eleven scan-loop instructions (target IDX 57-68) match the
 *     target one-for-one with identical register roles, and the entire deficit
 *     is that ebp holds `record_index` where the target holds `byte_offset`.
 *     That single role swap costs the 2 bytes (`cmp ebp,0x58` 3 bytes against
 *     the target's `cmp ebp,0xca78` 6) and shifts every later instruction by
 *     one slot, which is what collapses the positional score. The two outer
 *     spill slots are swapped for the same reason: the target keeps
 *     record_index at [esp+0x1c] and byte_offset at [esp+0x2c] (IDX 141-147),
 *     ours the reverse.
 *     Levers tried against that swap, none of which moved ebp to byte_offset:
 *     swapping the two initializers (498), swapping their declaration order
 *     (498), swapping `record_index++` and `byte_offset += 0x24d` in the outer
 *     tail (495), recomputing `record_base + byte_offset` for the entity_type
 *     read rather than reusing `record` (498), assigning `scan` before `idx`
 *     (498), and `idx++` ahead of `scan += 0x24d` (498). Forcing
 *     record_index to memory to free ebp regresses badly: an `int*` alias
 *     carrying its reads 231/628, address-taken with `(*ri)++` 233/628,
 *     `volatile` 254/639.
 *     Rewriting the scan loop to induct on the byte offset directly
 *     (`off = byte_offset; while (off < 0xca78) { ...; off += 0x24d; }`) does
 *     put a 0xca78 compare in the loop but loses the counter entirely: 197/629.
 *     `while (idx * 0x24d < 0xca78)` 235/655.
 *     Keeping the `if (byte_offset < 0xca78)` guard above the un-rotated
 *     `while (idx < 0x58)` head emits BOTH tests (target's `cmp ebp,0xca78`
 *     plus msvc6's own `cmp eax,0x58` pre-test, 9 bytes): 223/651. Guarding on
 *     `record_index < 0x58` instead lets msvc6 fold the guard into the head,
 *     which is the 499/640 variant of the same un-rotated shape.
 *     `#pragma optimize` sweep on the whole function: "a",off, "l",off,
 *     "w",off and "table_cursor",on are all inert at 614/642; "g",off explodes to obj 926
 *     at 26/926.
 *     That round concluded the rotation and the ebp role were one coupled
 *     decision and that 614 was the ceiling. Superseded: they are separate,
 *     and both are reachable together. See the three-step account at the top
 *     of this comment, which closed the function at 642/642.
 *
 * PROVEN 2026-08-29: symbolic equivalence (mem on 0x10139840 + 0x101dd8e0)
 * with --loop-bound 4000. The scan loop's per-state back-edge count is
 * cumulative (88+87+...+1 = 3916) across the outer loop's iterations, so a
 * bound below ~3900 makes LoopSeer discard the state before the function
 * terminates; lower bounds report "no terminal states". */

void __cdecl gm_InitObjektHersteller(void)
{
	int* table_cursor; extern char g_minimum_manufacturer[]; extern char g_manufacturer_types[];
	int i;
	int* mfr_table;
	char* record_base;
	int byte_offset;
	int record_index;
	int same_count;
	int run_length;
	int prev_type;
	char* record;
	int entity_type;
	int comp_count;

	/* Zero manufacturer table (25 ints) */
	table_cursor = (int*) &g_manufacturer_types;
	for (i = 0x19; i != 0; i--) {
		*table_cursor = 0;
		table_cursor++;
	}

	same_count = 0;
	run_length = 0;

	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x458, "gm_InitObjektHersteller(): fill tab...", 1);

	/* Indexing through a local base pointer, rather than ten independent
	 * literal-address stores, lets the second call's argument pushes hoist
	 * ahead of the stores the way the target does. */
	mfr_table = (int*) &g_manufacturer_types;
	mfr_table[8] = 0x2f;
	mfr_table[7] = 0x32;
	mfr_table[6] = 0x29;
	mfr_table[10] = 0x21;
	mfr_table[14] = 0x1e;
	mfr_table[15] = 0x1f;
	mfr_table[16] = 0x20;
	mfr_table[11] = 0x17;
	mfr_table[12] = 0x35;
	mfr_table[9] = 0x14;

	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x46d, "gm_InitObjektHersteller(): Initialisiere gm_ObjektNr2MinimalHersteller[Objekte_MAX]", 1);

	record_base = *(char**) &g_entity_type_table;

	/* Fill ObjektNr2MinimalHersteller with 0x58 (732 ints) */
	table_cursor = (int*) &g_minimum_manufacturer;
	for (i = 0x2dc; i != 0; i--) {
		*table_cursor = 0x58;
		table_cursor++;
	}

	/* prev_type shares the fill constant and must be written *after* the loop:
	 * that order gives the target's `mov ecx,0x2dc; mov eax,0x58`. Written
	 * first, 0x58 lands in eax ahead of the count and the two swap. */
	prev_type = 0x58;

	record_index = 0;
	byte_offset = 0;

	do {
		record = record_base + byte_offset;
		entity_type = *(unsigned char*) record;

		if (entity_type != prev_type) {
			same_count = 0;
			prev_type = entity_type;
			run_length = 0;

			if (byte_offset < 0xca78) {
				int idx;
				char* scan;
				idx = record_index;
				scan = record;
				while (byte_offset < 0xca78) {
					if (*(unsigned char*) scan != entity_type) {
						break;
					}
					run_length++;
					scan += 0x24d;
					idx++;
					if (idx >= 0x58) {
						break;
					}
				}
			}
		} else {
			same_count++;
		}
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x490, "gm_InitObjektHersteller(): // ---- Alle Objekte im Geb\344ude-Prototypen durchgehen... ----", 1);

		comp_count = 0;
		record_base = *(char**) &g_entity_type_table;

		/* Unsigned `> 0` gives the target's `test al,al; jbe`, where a plain
		 * `!= 0` emits `je`; the loop-bottom compare stays signed (`jl`). */
		if ((unsigned int) *(unsigned char*) (record + 0x22) > 0u) {
			unsigned short* comp_ptr;

			comp_ptr = (unsigned short*) (record + 0x23);

			do {
				unsigned short entry;

				entry = *comp_ptr;

				if (entry != 0xffff) {
					int ent_idx;
					int mfr_start;
					char* mfr_record;
					int mfr_type;
					int* mfr_type_alias;
					int consec;
					int new_val;

					ent_idx = entry & 0x7fff;
					mfr_start = *(unsigned char*) (g_item_def_table + (ent_idx << 6) + ent_idx + 0x21);
					mfr_start = *(int*) (mfr_start * 4 + (int) g_manufacturer_types);

					mfr_record = record_base + mfr_start * 0x24d;
					mfr_type_alias = &mfr_type;
					*mfr_type_alias = *(unsigned char*) mfr_record;
					consec = 0;

					if (mfr_start < 0x58) {
						int j;
						char* scan;
						j = mfr_start;
						scan = mfr_record;
						/* j++ ahead of the cursor advance gives the target's
						 * `inc eax; inc edi; add ebp,0x24d` order. */
						while (j < 0x58) {
							if (*(unsigned char*) scan != *mfr_type_alias) {
								break;
							}
							consec++;
							j++;
							scan += 0x24d;
						}
					}

					mfr_start += (consec * same_count) / run_length;
					new_val = *(int*) (ent_idx * 4 + (int) g_minimum_manufacturer);
					if (mfr_start < new_val) {
						((int*) g_minimum_manufacturer)[ent_idx] = mfr_start;
					}
				}

				comp_count++;
				comp_ptr++;
			} while (comp_count < *(unsigned char*) (record + 0x22));
		}

		record_index++;
		byte_offset += 0x24d;
	} while (byte_offset < 0xca78);

	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4ae, "gm_InitObjektHersteller(): Initialisieren der Objekt2MinimalHersteller-Tabelle anhand der Rohstoffe ", 1);

	{
		int* min_ptr;
		unsigned char* type_ptr;

		min_ptr = (int*) &g_minimum_manufacturer;
		type_ptr = (unsigned char*) (g_item_def_table + 0x21);

		do {
			if (*min_ptr == 0x58) {
				*min_ptr = *(int*) (*type_ptr * 4 + (int) g_manufacturer_types);
			}
			min_ptr++;
			type_ptr += 0x41;
		} while ((int) min_ptr < (int) ((char*) &g_minimum_manufacturer + 0xb70));
	}
}

/* Round-548: cross-TU path share with the spiel module's named definition.  The
   reference pushes the SAME address (0x10031004, "D:\Develop\DieGildeAddOn\game\
   spiel.c") at every log site, so it is one shared object, not an anonymous
   per-site literal.  Expressed as the raw-address cast the rest of the tree uses
   for this exact string; the earlier `extern char s_...[]` form had no definition
   anywhere, so every one of the 11 sites emitted an unrelocatable operand
   (round 924). */


/* RELOC, 861/861.  The category byte load must be split
 * across `def_row`/`cat_p` and dereferenced through `volatile char*` so
 * msvc6 materializes the address (`mov ecx,eax; add ecx,ebx; mov cl,[ecx]`)
 * instead of folding it into `[eax+ebx]`.  Both halves are required:
 * folding it back into one expression, even with the volatile cast, is
 * 5 bytes short and scores 750.
 *
 * The prologue player-copy loop now matches byte for byte.  Two separate
 * locals are required, and each one decides a different thing:
 *   - `copy_dst` (= dst + 3) is the memcpy destination.  It must have a
 *     second use in the loop body, or msvc6 folds the lea into the call
 *     argument instead of emitting it.  Reading the first store through it
 *     (`copy_dst[-4]`) as well as the third (`copy_dst[-1]`) is what pulls
 *     the lea above the stores, matching the reference (846 -> 849).
 *   - `base` (= dst + 2) carries the two middle stores as `base[-2]` and
 *     `base[-1]`.  That is what sets the store base register 8 bytes higher
 *     so the displacements land on [-4]/[0]/[+4]/[+8] as the reference has
 *     them (849 -> 858).
 * Both are needed: with `copy_dst` alone the schedule is right but every
 * displacement is 8 low, and with `base` alone the lea trails the stores.
 * Dead ends measured on the way: routing all four stores through `copy_dst`
 * (843), only the first store through it (846), `copy_dst` assigned after
 * the first store (SIZE_MISMATCH, 211), a `char*` typed `copy_dst` with byte
 * displacements (SIZE_MISMATCH, 786), and biasing `dst_player_ptr` itself by
 * +2 (849, same as no bias) or +1/-1/-2 (worse).
 *
 * The producible-count loop's SIB base/index roles (`[esi+eax+0x21]`, counter
 * as base and table as index) come from the induction variable's form, not
 * from the addend order.  Counting rows in `row_index` and spelling every
 * address as `g_entity_type_table + row_index * 0x24d + disp` makes msvc6
 * strength-reduce the multiply into the loop-carried register and give it the
 * base role; accumulating a byte offset (`table_offset += 0x24d`) gives the
 * reloaded table pointer the base role instead, whatever the addend order.
 * The final read-modify-write is spelled out twice rather than routed through
 * a pointer local.  A pointer local forces a `lea` into a register plus
 * `[reg]` accesses and lands 2 bytes short (859); the double spelling keeps
 * the load and store as direct `[counter + table + disp]` operands.
 * Dead ends on this loop: addend-order swaps and array-subscript spellings
 * (no change, 858), `(char*) table_offset` casts and a pointer-local rmw on
 * the offset-accumulating shape (785, SIZE_MISMATCH), caching the table
 * pointer in a local (671), an `unsigned char` count (697), seeding the count
 * from the byte instead of zero (711), and keeping `row_index * 0x24d` in
 * `table_offset` rather than inlining it at each use (798). */

int __cdecl gm_Open(int map_id)
{
	unsigned int* src_player_ptr; extern char s_gzip_mode_rb[];
	unsigned int* dst_player_ptr;
	unsigned int player_field;
	FILE* file_handle;
	unsigned short slot_entry;
	char item_category;
	int producible_count;
	unsigned short* slot_ptr;
	int slot_counter;
	int slot_idx;
	unsigned char path_buf[512];
	int row_index;
	char* def_row;
	char* cat_p;

	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4d3, "gm_Open(): enter", 1);
	/* 0x10031204 is "gm_Open(): St\344dte" (Latin-1 a-umlaut, byte 0xe4).  The
	   text sits in a relocation slot, so a wrong string still scores RELOC;
	   see docs/msvc6-c-shapes.md section 36. */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4d6, "gm_Open(): St\344dte", 1);
	src_player_ptr = (unsigned int*) &g_player_record_src;
	dst_player_ptr = (unsigned int*) &g_player_record_dst;
	do {
		unsigned int* copy_dst;
		unsigned int* base;
		base = dst_player_ptr + 2;
		copy_dst = dst_player_ptr + 3;
		copy_dst[-4] = src_player_ptr[-0x14];
		player_field = *src_player_ptr;
		base[-2] = 1000;
		base[-1] = player_field;
		copy_dst[-1] = 1000;
		memcpy((void*) copy_dst, (void*) &g_producer_id_table, 0x2a80);
		src_player_ptr = src_player_ptr + 0xbd;
		dst_player_ptr = dst_player_ptr + 0xaa4;
	} while ((int) src_player_ptr < (int) ((char*) &g_player_record_src + 0xec4));
	/* 0x100311f0 is "gm_Open(): Geb\344ude" (Latin-1 a-umlaut, byte 0xe4). */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4e3, "gm_Open(): Geb\344ude", 1);
	g_entity_type_table = (char*) m_alloc(0xca78, "f3_gm:lpGebaeudePROT");
	if (g_entity_type_table == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4e8, "Memory could not be allocated!", 1);
		return -1;
	}
	g_entity_ptr = (unsigned char*) m_alloc(0xa900, "f3_gm:lpGebaeudeINST");
	memset((void*) g_entity_ptr, 0, 0xa900);
	if (g_entity_ptr == 0) {
		return -2;
	}
	sprintf((char*) path_buf, "%s%s", map_id, "A_Geb.dat");
	file_handle = fopen((char*) path_buf, s_gzip_mode_rb);
	if (file_handle == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4f5, "Geb\344ude-Daten konnten nicht geladen werden! (A_Geb.dat)", 1);
		return -3;
	}
	fread((void*) g_entity_type_table, 0x24d, 0x58, file_handle);
	fclose(file_handle);
	g_item_def_table = (char*) m_alloc(0xb9dc, "f3_gm:lpObjektePROT");
	if (g_item_def_table == 0) {
		return -4;
	}
	g_query_base = (unsigned short*) m_alloc(0x14f218, "f3_gm:lpObjekteINST");
	if (g_query_base == 0) {
		return -5;
	}
	memset((void*) g_query_base, 0, 0x14f218);
	sprintf((char*) path_buf, "%s%s", map_id, "A_Obj.dat");
	file_handle = fopen((char*) path_buf, s_gzip_mode_rb);
	if (file_handle == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0x52d,
			"Objekt-Daten konnten nicht geladen werden! (A_Obj.dat)",
			1
		);
		return -6;
	}
	fread((void*) g_item_def_table, 0x41, 0x2dc, file_handle);
	fclose(file_handle);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x536, "gm_Open(): gm_InitObjektHersteller", 1);
	/* Called through a pointer: with the callee defined earlier in this TU a direct
	 * call lets the compiler use its register summary and gm_Open sheds ebx
	 * (859 vs 861 bytes); the reference does not. */
	((void (__cdecl*)(void)) gm_InitObjektHersteller)();
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x53a, "gm_Open(): gm_KillAllSpieler", 1);
	gm_KillAllSpieler();
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
		0x53e,
		"gm_Open(): ---- Das dusselige Datendesign hinbiegen !! -----",
		1
	);
	row_index = 0;
	do {
		producible_count = 0;
		slot_counter = 0x40;
		slot_ptr = (unsigned short*) (g_entity_type_table + row_index * 0x24d + 0x23);
		do {
			slot_entry = *slot_ptr;
			if (slot_entry != 0xffff) {
				slot_idx = slot_entry & 0x7fff;
				def_row = g_item_def_table + slot_idx * 0x40;
				cat_p = (char*) slot_idx;
				cat_p += (int) def_row;
				item_category = *(volatile char*) cat_p;
				if (((item_category == '\x02') || (item_category == '\x06')) && (slot_idx != 0xfd) &&
					((slot_entry & 0x8000) != 0)) {
					producible_count = producible_count + 1;
				}
			}
			slot_ptr = slot_ptr + 1;
			slot_counter = slot_counter + -1;
		} while (slot_counter != 0);
		*(char*) (g_entity_type_table + row_index * 0x24d + 0x21) =
			*(char*) (g_entity_type_table + row_index * 0x24d + 0x21) + producible_count;
		row_index = row_index + 1;
	} while (row_index < 0x58);
	/* Original seeds the RNG from the system timer before the exit log
	 * (fcn.1001a140 = srand(timeGetTime())). */
	srv_SeedRandomWithTime();
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x588, "gm_Open(): exit", 1);
	return 0;
}
#include "spiel.h"
/* Client-only (TL 0x500c80, discarded): copies the game clock. The clock is the 14-byte block at
 * g_current_year, which gm_AllocGebaeude copies whole; the client keeps the same block at 0x7f4c00.
 * The client has it before gm_CompareGameTime; defined before gm_Open, any function changes gm_Open's
 * standalone compile, so it follows gm_Open. */
void __cdecl gm_GetGameTime(struct blk14* out)
{
	*out = *(struct blk14*) &g_current_year;
}

void __cdecl gm_ResetAllEntities(void)
{
	int i;
	EntityQueryRecord* entity_cursor;
	for (i = 0; i < 0x100; i++) {
		entity_cursor = (EntityQueryRecord*) g_entity_ptr + i;
		if (entity_cursor->type != 0) {
			gm_CleanupBuildingEntity((unsigned char*) entity_cursor);
		}
	}
	{
		int* dst;
		int n;
		dst = (int*) g_entity_ptr;
		for (n = 0; n < 0x2a40; n++) {
			*dst++ = 0;
		}
	}
}

void __cdecl gm_CleanupObjectEntities(void)
{
	int i;
	void* dynamic;
	void* existing;
	void* static_ptr;
	char* list_head;

	for (i = 0; i < 0x5008; i++) {
		if (*(unsigned short*) ((char*) g_query_base + i * 0x43) != 0) {
			gm_ResolveEntityById(&dynamic, &existing, &static_ptr, *(int*) ((char*) g_query_base + i * 0x43 + 6));
			if (dynamic != NULL) {
				list_head = (char*) dynamic + 0x5d;
			} else if (existing != NULL) {
				list_head = (char*) existing + 0x14;
			} else if (static_ptr != NULL) {
				list_head = (char*) static_ptr + 0x178;
			} else {
				list_head = NULL;
			}
			if (list_head != NULL) {
				gm_RemoveObjectByType((void**) list_head, *(unsigned short*) ((char*) g_query_base + i * 0x43));
			} else {
				gm_ClearObjektResources((LinkedNode*) ((char*) g_query_base + i * 0x43));
				*(unsigned short*) ((char*) g_query_base + i * 0x43) = 0;
				g_query_limit--;
			}
		}
	}
	memset(g_query_base, 0, 0x14f218);
}

/* Finds a record in the entity table by ID. Searches the
 * global entity records for a matching entity ID. Returns
 * pointer or NULL. */


Record* __cdecl gm_FindRecordById(int id)
{
	int i;
	Record* entity_cursor;

	i = 0;
	entity_cursor = (Record*) g_query_base;
	while (i < 0x5008) {
		if (entity_cursor->type != 0 && entity_cursor->entity_id == id) {
			return (Record*) ((char*) g_query_base + i * 0x43);
		}
		i++;
		entity_cursor = (Record*) ((char*) entity_cursor + 0x43);
	}
	return (Record*) 0;
}

/* Cleans up object entities. Frees inventory objects and
 * linked item chains from all active entities. */


void __cdecl gm_CleanupAllEntities(void)
{
	int ent;
	ent = (int) gm_StartFilteredEntitySearch(1, 6);
	if (ent) {
		do {
			((void(__cdecl*)(unsigned char*)) gm_CleanupBuildingEntity)((unsigned char*) ent);
			ent = (int) gm_FindNextFilteredEntity();
		} while (ent);
	}
	if (g_entity_type_table) {
		m_FreeTracked(g_entity_type_table);
		g_entity_type_table = 0;
	}
	if (g_entity_ptr) {
		m_FreeTracked(g_entity_ptr);
		g_entity_ptr = 0;
	}
	if (g_item_def_table) {
		m_FreeTracked(g_item_def_table);
		g_item_def_table = 0;
	}
	if (g_query_base) {
		m_FreeTracked(g_query_base);
		g_query_base = 0;
	}
}

/* Cleans up all entities. Complete teardown of all game
 * entities including buildings, citizens, and objects. */


int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id)
{
	EntityQueryRecord* query_cursor;
	int i;
	char* entity_cursor;

	if (g_item_def_table == NULL) {
		return 0;
	}
	if (dynamic != NULL) {
		*dynamic = NULL;
	}
	if (existing != NULL) {
		*existing = NULL;
	}
	if (static_ptr != NULL) {
		*static_ptr = NULL;
		entity_cursor = (char*) &g_slot_table;
		for (i = 0; i < 0x300; i++) {
			if (*(unsigned short*) entity_cursor != 0xffff && *(int*) (entity_cursor + 4) == entity_id) {
				*static_ptr = entity_cursor;
				return 3;
			}
			entity_cursor += 0x21c;
		}
	}
	if (dynamic != NULL) {
		query_cursor = (EntityQueryRecord*) g_entity_ptr;
		for (i = 0; i < 0x100; i++, query_cursor++) {
			if (query_cursor->type != 0 && query_cursor->entity_id == entity_id) {
				*dynamic = query_cursor;
				return 1;
			}
		}
	}
	if (existing != NULL) {
		entity_cursor = (char*) g_query_base;
		for (i = 0; i < g_query_limit; entity_cursor += 0x43) {
			if (*(unsigned short*) entity_cursor != 0) {
				if (*(int*) (entity_cursor + 2) == entity_id) {
					*existing = entity_cursor;
					return 2;
				}
				i++;
			}
		}
	}
	return 0;
}

/* Rebuilds the market slots for the given season: clears the slot
 * flags, marks every slot whose item some market entity's inventory holds
 * (and every slot whose item is in that item's four-entry list at
 * def+0x2e), allocates missing objects and refreshes the per-item counts
 * for the ids list.
 *
 * Byte-exact.  `g_slot_array` is the array symbol (`(char*) &g_slot_array`,
 * not a pointer load), 0x55 slots of 0x80 bytes per season.  Every walk is
 * a counted index loop; msvc6 strength-reduces them into the reference's
 * down-counters and pointer walks, and the ids walk folds its first
 * `ids[i] != 0` test into the reference's `mov eax,0x92` head.  With the
 * canonical node cleanup declarations, `slots` and `query` have the native
 * [esp+0x10]/[esp+0x14] homes without a dummy query initialization.
 * First-reference order matters; see docs/msvc6-allocator.md "Frame slots".
 * The previous body spelled the walks as cursors and sat at 25 linked
 * bytes of ebx/edi role swap. */

void __cdecl gm_ObjectsAvailble(int season)
{
	unsigned int ids[8];
	char* slots;
	void* entity;
	void* query;
	unsigned short* result;
	unsigned short* r2;
	char* def;
	int i;
	int j;
	int k;
	int count;

	ids[0] = 0x92;
	ids[1] = 0x93;
	ids[2] = 0x94;
	ids[3] = 0x95;
	ids[4] = 0x96;
	ids[5] = 0x97;
	ids[6] = 0x2db;
	ids[7] = 0;

	g_active_player_count = (int) gm_StartFilteredEntitySearch(1, 5, 0xa);
	if (g_active_player_count == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x7cf,
			"gm_ObjectsAvailble(): Kein Markt", 1);
		return;
	}


	slots = (char*) &g_slot_array + season * 0x2a90;
	if (season != g_current_season) {
		return;
	}
	for (i = 0; i < 0x55; i++) {
		*(int*) (slots + i * 0x80 + 4) = 0;
	}

	entity = gm_StartFilteredEntitySearch(1, 6);
	while (entity != 0) {
		if (*(char*) (g_entity_type_table + *(unsigned char*) entity * 0x24d) != '\n') {
			query = gm_ff_Objekt(*(int*) ((char*) entity + 0x5d), 1, 0, 0xff);
			for (i = 0; query != 0 && i < 0x55; i++) {
				if (*(unsigned short*) (slots + i * 0x80) != 0 &&
				    gm_ff_Objekt(*(int*) ((char*) query + 0x14), 1, 0, *(unsigned short*) (slots + i * 0x80)) != 0) {
					*(int*) (slots + i * 0x80 + 4) = 1;
					def = g_item_def_table + *(unsigned short*) (slots + i * 0x80) * 0x41;
					for (j = 0; j < 0x55; j++) {
						for (k = 0; k < 4; k++) {
							if (*(unsigned short*) (slots + j * 0x80) == *(unsigned short*) (def + 0x2e + k * 2)) {
								*(int*) (slots + j * 0x80 + 4) = 1;
							}
						}
					}
				}
			}
		}
		entity = gm_FindNextFilteredEntity();
	}

	for (i = 0; i < 0x55; i++) {
		result = (unsigned short*) gm_ff_Objekt(*(int*) ((char*) g_active_player_count + 0x5d), 1, 0,
			*(unsigned short*) (slots + i * 0x80 + 0x3c));
		if (result != 0) {
			result = (unsigned short*) gm_ff_Objekt(*(int*) ((char*) result + 0x14), 1, 0, 0xff);
			if (*(int*) (slots + i * 0x80 + 4) != 0) {
				if (gm_ff_Objekt(*(int*) ((char*) result + 0x14), 1, 0, *(unsigned short*) (slots + i * 0x80)) == 0) {
					gm_AllocObjekt(*(int*) ((char*) result + 2), *(unsigned short*) (slots + i * 0x80), 1);
				}
			}
		}
	}

	for (i = 0; ids[i] != 0; i++) {
		count = 0;
		result = (unsigned short*) gm_ff_Objekt(*(int*) ((char*) g_active_player_count + 0x5d), 1, 0, ids[i]);
		if (result != 0) {
			r2 = (unsigned short*) gm_ff_Objekt(*(int*) ((char*) result + 0x14), 1, 0, 0xff);
			if (r2 != 0) {
				r2 = (unsigned short*) gm_ff_Objekt(*(int*) ((char*) r2 + 0x14), 1, 5);
				while (r2 != 0) {
					count++;
					r2 = (unsigned short*) gm_NextEntityQueryMatch();
				}
				result = (unsigned short*) gm_ff_Objekt(*(int*) ((char*) result + 0x14), 1, 4, 0x11);
				if (result != 0 && *(unsigned char*) ((char*) result + 0x1c) != count)
					*(unsigned char*) ((char*) result + 0x1c) = (unsigned char) count;
			}
		}
	}
}

/* Client-only item-category helpers (discarded; see gm_CompareGameTime). */

int __cdecl gm_GetItemCategory(unsigned short* item)
{
	int kinds[16] = { 1, 3, 4, 0xb, 0xd, 0xe, 0x12, 0x13, 0x15, 0x16, 0x1a, 0x1b, 0x1c, 0x1f, 0x21, 0 };
	char* def;
	int i;

	i = 0;
	def = g_item_def_table + *item * 0x41;
	while (kinds[i] != 0) {
		if (*def == kinds[i]) {
			return kinds[i];
		}
		i++;
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetItemCategory(): item not found", 1);
	return 0;
}


/* Client-only (TL 0x501490, discarded): the item type whose name is name, or 0. The client calls the
 * case-insensitive compare by its old name, strcmpi. */
int __cdecl gm_FindItemTypeByName(char* name)
{
	int i;

	for (i = 0; i < 0x2dc; i++) {
		if (strcmpi(name, g_item_def_table + i * 0x41 + 1) == 0) {
			return i;
		}
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_FindItemTypeByName(): unknown item", 1);
	return 0;
}
int __cdecl gm_IsRawItem(int item)
{
	char kind;

	kind = g_item_def_table[item * 0x41];
	if (kind == 1 || kind == 0x1a || kind == 0xb || kind == 0x1c || kind == 0x1b || kind == 3 || kind == 4) {
		return 1;
	}
	return 0;
}

/* Client-only season-table helpers (TL 0x5016f0, 0x502450; discarded). The 5 x 0x2a90 season tables are
 * the server's g_town_records (0x1009b760, 54480 bytes): the client's at 0x85ab80 sit at the offset
 * g_slot_array (0x85ab90) and g_entity_type_table (0x868050) have, and gm_GetSeasonPrice reads them.
 * 0x5016f0 sits before gm_ObjectsAvailble in the client; placed there, its g_item_def_table reference
 * would become the TU's first and change gm_ObjectsAvailble's registers (as for TL 0x5013c0). */

/* Client-only (TL 0x502450, discarded): the season's production base of slot's item: 0 for kinds 0x17 and
 * 0x25; in season 0 the scale at the 0x10035410 block's first dword (the client's 0x773d4c, the same block
 * at the same offset as sim's scan cursor) times the slot's +8 float times 0.0025, rounded; else the
 * season's header count times that float times 0.0005. */
int __cdecl gm_GetSlotBase(int season, int slot)
{
	extern char g_gap_10035410[28];
	char* cell;
	char* def;
	unsigned short id;

	cell = (char*) &g_slot_array + season * 0x2a90 + slot * 0x80;
	id = *(unsigned short*) cell;
	def = g_item_def_table + id * 0x40 + id;
	if (*def == 0x17 || *def == 0x25) {
		return 0;
	}
	if (season == 0) {
		return (int) (*(float*) g_gap_10035410 * *(float*) ((char*) &g_slot_array + 8 + slot * 0x80) * 0.0025 +
					  g_const_half);
	}
	return (int) (*(int*) ((char*) &g_slot_array - 0x10 + season * 0x2a90) * *(float*) (cell + 8) * 0.0005);
}

/* Client-only (TL 0x5016f0, discarded): refreshes season's 0x55 slots from g_producer_id_table (fields
 * +0xc and +0x30), their base (gm_GetSlotBase, or gm_GetSlotProduction for kinds 0x17 and 0x25) and
 * their production value. */
void __cdecl gm_RefreshSeasonSlots(int season)
{
	int __cdecl gm_GetSlotProduction(int player, int slot);
	char* cell;
	char* def;
	int slot;
	int v;

	for (slot = 0; slot < 0x55; slot++) {
		cell = (char*) &g_slot_array + season * 0x2a90 + slot * 0x80;
		def = g_item_def_table + *(unsigned short*) cell * 0x40 + *(unsigned short*) cell;
		*(int*) (cell + 0xc) = *(int*) ((char*) &g_producer_id_table + 0xc + slot * 0x80);
		*(int*) (cell + 0x30) = *(int*) ((char*) &g_producer_id_table + 0x30 + slot * 0x80);
		if (*def == 0x17 || *def == 0x25) {
			*(int*) (cell + 0x34) = gm_GetSlotProduction(season, slot);
		}
		else {
			v = gm_GetSlotBase(season, slot);
			*(float*) (cell + 0x20) = (float) v;
		}
		*(float*) (cell + 0x38) = (float) eval_ObjektPreis2Credits(*(unsigned short*) cell, 100);
		*(int*) (cell + 0x24) = *(int*) (cell + 0x20);
	}
}

/* Client-only: production of slot b of player a's building slots, summed
 * over the items they hold (discarded). */
int __cdecl gm_GetSlotProduction(int player, int slot)
{
	char* cell;
	unsigned char* e;
	int sum;
	int j;

	sum = 0;
	cell = (char*) &g_slot_array + player * 0x2a90 + slot * 0x80;
	if (cell[0x40] == 0) {
		return 0;
	}
	for (j = 0; j < 4; j++) {
		if (cell[0x40 + j * 8] != 0) {
			for (e = (unsigned char*) gm_StartFilteredEntitySearch(1, 5, *(unsigned char*) (cell + 0x40 + j * 8)); e != 0;
			     e = gm_FindNextFilteredEntity()) {
				sum = (int) (sum + *(float*) (cell + 0x44 + j * 8));
			}
		}
	}
	sum = (int) (sum * 0.5);
	if (*(float*) (cell + 0x24) != g_const_0_0) {
		sum = (int) (*(float*) (cell + 0x24) / *(float*) (cell + 0x20) * sum);
	}
	return sum;
}

/* Client-only (TL 0x5025a0, discarded): the price of season's slot: its item's production value times
 * the slot's +0x24/+0x20 ratio, scaled by +0x20 over the stock in the item's tavern (or the season's
 * kind-47 building's 0x1db store) when that exceeds +0x20, clamped to 0.25..5, moved 0.4 of the way
 * from the slot's last price (+0x38); with no last price, at least 512. */
/* The five season tables, 0x10 bytes before g_slot_array (the server's g_town_records at 0x1009b760). */
#define gm_SEASON_TABLES ((unsigned char (*)[0x2a90])((char*) &g_slot_array - 0x10))

float __cdecl gm_GetSlotPrice(int season, int slot)
{
	char* __cdecl gm_FindTavernServing(int item);
	void* __cdecl gm_FindKind47ByOwner(int owner);
	char* def;
	char* store;
	char* e;
	int id;
	float stock;
	float last;
	float factor;
	float ratio;
	double x;
	double scale;

	id = *(unsigned short*) &gm_SEASON_TABLES[season][0x10 + slot * 0x80];
	def = g_item_def_table + id * 0x40 + id;
	store = gm_FindTavernServing(id);
	if (store == 0 && season != g_current_season) {
		e = (char*) gm_FindKind47ByOwner(season);
		if (e != 0) {
			store = (char*) gm_ff_Objekt(*(int*) (e + 0x5d), 2, 0, 0x1db, 6);
		}
	}
	stock = 0;
	if (store != 0) {
		e = (char*) gm_ff_Objekt(*(int*) (store + 0x14), 1, 0, id);
		if (e != 0) {
			stock = (float) *(int*) (e + 0xe);
		}
		x = *(float*) &gm_SEASON_TABLES[season][0x34 + slot * 0x80] /
			*(float*) &gm_SEASON_TABLES[season][0x30 + slot * 0x80];
		last = *(float*) &gm_SEASON_TABLES[season][0x48 + slot * 0x80];
		if (stock > *(float*) &gm_SEASON_TABLES[season][0x30 + slot * 0x80] && *def != 0x17) {
			factor = *(float*) &gm_SEASON_TABLES[season][0x30 + slot * 0x80] / (stock < 1.0 ? 1.0 : stock);
		}
		else {
			factor = 1.0f;
		}
		x *= factor;
		ratio = x > 0.25 ? x : 0.25;
		scale = ratio < 5.0 ? ratio : 5.0;
		x = ((float) eval_ObjektPreis2Credits(id, 100) * (stock = (float) scale) - last) * 0.4f +
			*(float*) &gm_SEASON_TABLES[season][0x48 + slot * 0x80];
		if (*(float*) &gm_SEASON_TABLES[season][0x48 + slot * 0x80] <= g_const_0_0) {
			return (float) eval_ObjektPreis2Credits(id, 100) < 512.0f ? 512.0f
																		 : (float) eval_ObjektPreis2Credits(id, 100);
		}
		return (float) x;
	}
	return (float) eval_ObjektPreis2Credits(id, 100);
}

#undef gm_SEASON_TABLES

/* Client-only (TL 0x502780, discarded): gm_GetSlotPrice of the slot holding item id in season, or -1. */
float __cdecl gm_GetObjektPrice(int season, int id)
{
	int i;

	for (i = 0; i < 0x55; i++) {
		if (*(unsigned short*) ((char*) &g_slot_array + season * 0x2a90 + i * 0x80) == id) {
			return gm_GetSlotPrice(season, i);
		}
	}
	return g_const_neg_1_0;
}

/* Scans the per-entity slot table for an entry whose 16-bit id
 * matches arg2. Each entity owns 0x2a90 bytes at 0x1009b770,
 * holding 0x55 slots of 0x80 bytes; returns the matching slot
 * pointer or NULL. */



char* __cdecl gm_FindSlotById(int arg1, int arg2)
{
	int i;

	for (i = 0; i < 0x55; i++) {
		if (*(unsigned short*) ((int) g_entity_end + 0x10 + arg1 * 0x2a90 + i * 0x80) == arg2) {
			return (char*) ((int) g_entity_end + 0x10 + arg1 * 0x2a90 + i * 0x80);
		}
	}
	return 0;
}

/* Client-only: map distance between two tile positions (discarded). */
double __cdecl gm_GetTileDistance(int x1, int y1, int x2, int y2)
{
	double __cdecl sqrt(double x);
	double dx;
	double dy;

	dx = (double) x1 - (double) x2;
	dy = (double) y1 - (double) y2;
	if (dx < 0) {
		dx = -dx;
	}
	if (dy < 0) {
		dy = -dy;
	}
	return sqrt(dx * dx + dy * dy) * 2.90816330909729;
}

void* __cdecl gm_NextEntityQueryMatch(void)
{
    unsigned short* current;
    unsigned short* matched_ent;
    unsigned short filter_type_cache;
    unsigned short cur_id;
    char is_match;

    current = g_query_cursor;
    matched_ent = (unsigned short*)0;
    is_match = 0;
    if (current == (unsigned short*)0) {
        return (void*)current;
    }
    if (g_query_active != 0) {
        g_query_active = 0;
        if (g_query_flag2 != 0 && *(int*)((char*)current + 0x14) != 0) {
            g_dispatch_table_b[g_query_match_count] = *(int*)((char*)current + 0x14);
            g_query_match_count++;
            goto have_depth;
        }
    }
have_depth:
    while (g_query_count < g_query_limit) {
        filter_type_cache = g_query_filter_type;
        if (current == (unsigned short*)0) {
            break;
        }
        if (is_match != 0) {
            break;
        }
        while (*current == 0) {
            current = (unsigned short*)((char*)current + 0x43);
            g_query_cursor = current;
        }
        if (g_query_flag3 != 0) {
            is_match = 1;
        }
        if (g_query_filter_max_id != 0x7fff) {
            cur_id = *current;
            if (cur_id != g_query_filter_max_id) {
                goto lab_nomatch;
            }
            is_match = 1;
        }
        if (g_query_filter_owner != -1) {
            if (*(int*)((char*)current + 2) == g_query_filter_owner) {
                is_match = 1;
            } else {
                goto lab_nomatch;
            }
        }
        if (filter_type_cache != 0xffff) {
            unsigned short res;
            res = gm_GetEntityType((short*)current);
            filter_type_cache = g_query_filter_type;
            if (res == filter_type_cache) {
                is_match = 1;
                current = g_query_cursor;
                goto lab_395;
            }
            is_match = 0;
            current = g_query_cursor;
            goto lab_3bc;
        }
lab_395:
        if (g_query_filter_state != 0xff) {
            unsigned int eid;
            char* tbl;
            eid = (unsigned int)*current;
            tbl = g_item_def_table;
            tbl += eid * 0x40;
            is_match = (unsigned char) tbl[eid] == g_query_filter_state;
        }
        goto lab_3bc;
lab_nomatch:
        is_match = 0;
lab_3bc:
        if (g_query_flag1 != 0) {
            if (is_match != 0) {
                matched_ent = current;
            }
            current = (unsigned short*)((char*)current + 0x43);
            g_query_count++;
            g_query_cursor = current;
        } else {
            if (is_match != 0) {
                matched_ent = current;
            }
            current = *(unsigned short**)((char*)current + 0x3f);
            g_query_cursor = current;
            if (current != (unsigned short*)0) {
                int fld;
                fld = *(int*)((char*)current + 0x14);
                if (fld != 0 && g_query_flag2 != 0) {
                    g_dispatch_table_b[g_query_match_count] = fld;
                    goto lab_43e;
                }
            } else {
                if (g_query_flag2 != 0 && g_query_match_count != 0) {
                    current = (unsigned short*)g_dispatch_table_a[g_query_match_count];
                    g_query_match_count--;
                    g_query_cursor = current;
                    if (*(int*)((char*)current + 0x14) != 0) {
                        g_dispatch_table_b[g_query_match_count] = *(int*)((char*)current + 0x14);
lab_43e:
                        g_query_match_count++;
                    }
                }
            }
        }
    }
    return (void*)matched_ent;
}

/* Client-only: the item-list variant of gm_NextEntityQueryMatch.  It walks
 * the query's 0x43-byte item records (g_query_flag1) or their +0x3f links,
 * keeping the link stack in g_dispatch_table_a/b, and applies the id, owner,
 * type and item-kind filters (discarded). */
void* __cdecl gm_NextQueryItemMatch(void)
{
	unsigned short* cur;
	char match;

	match = 0;
	if (g_item_def_table == 0) {
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_NextQueryItemMatch(): item table not loaded", 1);
		return 0;
	}
	cur = g_query_cursor;
	if (cur == 0) {
		return 0;
	}
	if (g_query_active != 0) {
		g_query_active = 0;
		if (g_query_flag2 != 0 && *(int*) ((char*) cur + 0x14) != 0) {
			g_dispatch_table_b[g_query_match_count] = *(int*) ((char*) cur + 0x14);
			g_query_match_count++;
		}
		if (*cur != 0) {
			g_query_count = 1;
		}
	}
	else if (g_query_flag1 != 0) {
		cur = (unsigned short*) ((char*) cur + 0x43);
		g_query_cursor = cur;
		if (*cur != 0) {
			g_query_count++;
		}
		while (g_query_count < g_query_limit && *cur == 0) {
			cur = (unsigned short*) ((char*) cur + 0x43);
			g_query_cursor = cur;
		}
	}
	else {
		cur = *(unsigned short**) ((char*) cur + 0x3f);
		g_query_cursor = cur;
		if (cur != 0) {
			if (g_query_flag2 != 0 && *(int*) ((char*) cur + 0x14) != 0) {
				g_dispatch_table_b[g_query_match_count] = *(int*) ((char*) cur + 0x14);
				g_query_match_count++;
			}
		}
		else {
			if (g_query_flag2 == 0 || g_query_match_count == 0) {
				return 0;
			}
			cur = (unsigned short*) g_dispatch_table_a[g_query_match_count];
			g_query_match_count--;
			g_query_cursor = cur;
			if (*(int*) ((char*) cur + 0x14) != 0) {
				g_dispatch_table_b[g_query_match_count] = *(int*) ((char*) cur + 0x14);
				g_query_match_count++;
			}
		}
	}
	if (g_query_count >= g_query_limit) {
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_NextQueryItemMatch(): query overflow", 1);
		return 0;
	}
	for (;;) {
		match = g_query_flag3 != 0;
		if (g_query_filter_max_id != 0x7fff) {
			if (*cur != g_query_filter_max_id) {
				goto next;
			}
			match = 1;
		}
		if (g_query_filter_owner != -1) {
			if (*(int*) ((char*) cur + 2) != g_query_filter_owner) {
				goto next;
			}
			match = 1;
		}
		if (g_query_filter_type != 0xffff) {
			if (gm_GetEntityType((short*) cur) != g_query_filter_type) {
				goto next;
			}
			match = 1;
		}
		if (g_query_filter_state != 0xff) {
			if ((unsigned char) g_item_def_table[*cur * 0x41] != g_query_filter_state) {
				goto next;
			}
			match = 1;
		}
		if (match) {
			return cur;
		}
next:
		match = 0;
		if (g_query_flag1 != 0) {
			cur = (unsigned short*) ((char*) cur + 0x43);
			g_query_cursor = cur;
			if (*cur != 0) {
				g_query_count++;
			}
			while (g_query_count < g_query_limit && *cur == 0) {
				cur = (unsigned short*) ((char*) cur + 0x43);
				g_query_cursor = cur;
			}
		}
		else {
			cur = *(unsigned short**) ((char*) cur + 0x3f);
			g_query_cursor = cur;
			if (cur != 0) {
				if (g_query_flag2 != 0 && *(int*) ((char*) cur + 0x14) != 0) {
					g_dispatch_table_b[g_query_match_count] = *(int*) ((char*) cur + 0x14);
					g_query_match_count++;
				}
			}
			else {
				if (g_query_flag2 == 0 || g_query_match_count == 0) {
					return 0;
				}
				cur = (unsigned short*) g_dispatch_table_a[g_query_match_count];
				g_query_match_count--;
				g_query_cursor = cur;
				if (*(int*) ((char*) cur + 0x14) != 0) {
					g_dispatch_table_b[g_query_match_count] = *(int*) ((char*) cur + 0x14);
					g_query_match_count++;
				}
			}
		}
		if (g_query_count > g_query_limit || (char*) cur >= (char*) g_query_base + 0x14f218) {
			g_query_cursor = 0;
			return 0;
		}
	}
}

/* Initializes the query state from a list of (type, value) vararg pairs.
 * Type 0 = max id (word), 1 = owner (int), 3 = type (word), 4 = state
 * (byte), 5 = flag3, 6 = flag2, 7 = flag1. When flag1 is set the cursor
 * starts at the global query base; otherwise the container id is used.
 * Returns the first match, or NULL when no container id was given. */
unsigned short* __cdecl gm_ff_Objekt(int container_id, int arg_count, int first_arg, ...)
{
	int* arg_ptr;
	int i;
	unsigned char flag1;
	unsigned char flag2;

	if (g_item_def_table == 0) {
		return (unsigned short*) 0;
	}

	g_query_filter_max_id = 0x7fff;
	g_query_filter_owner = 0xffffffff;
	g_query_filter_type = 0xffff;
	g_query_filter_state = 0xff;
	g_query_flag3 = 0;

	flag1 = 0;
	g_query_flag1 = flag1;
	flag2 = 0;
	g_query_flag2 = flag2;
	g_query_active = 1;
	g_query_count = 0;
	g_query_match_count = 0;

	if (arg_count > 0) {
		arg_ptr = &arg_count;
		i = arg_count;

		do {
			arg_ptr++;
			switch (*(unsigned char*) arg_ptr) {
			case 0:
				arg_ptr++;
				g_query_filter_max_id = *(unsigned short*) arg_ptr;
				break;
			case 1:
				g_query_filter_owner = *(arg_ptr + 1);
				arg_ptr++;
				break;
			case 2:
				break;
			case 3:
				g_query_filter_type = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 4:
				g_query_filter_state = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 5:
				g_query_flag3 = 1;
				break;
			case 6:
				flag2 = 1;
				break;
			case 7:
				flag1 = 1;
				break;
			}
			i--;
		} while (i != 0);

		g_query_flag1 = flag1;
		g_query_flag2 = flag2;

		if (flag1 != 0) {
			if (flag2 != 0) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xb66, "gm_ff_Objekt: Invalid Combination of Flags", 1);
				return (unsigned short*) 0;
			}
			container_id = (int) g_query_base;
			goto query_tail;
		}
	}

	if (container_id == 0) {
		return (unsigned short*) container_id;
	}

query_tail:
	g_query_cursor = (unsigned short*) container_id;
	return gm_NextEntityQueryMatch();
}

char* __cdecl gm_AllocateObjectSlot(void)
{
	char* node;
	int i;
	char* result;

	node = (char*) g_query_base;
	result = NULL;
	i = 0;
	while (result == NULL && i < 0x5008) {
		if (*(short*) node != 0) {
			i++;
			node += 0x43;
		} else {
			result = node;
		}
	}
	return result;
}

/* Removes the first node whose type id equals b from the list headed by *a.
 * Returns 0 on success, -1 if the list is empty, -2 if the id is not found.
 * Also decrements the global query limit counter. */
int __cdecl gm_RemoveObjectByType(int a, int b)
{
	LinkedNode** head;
	LinkedNode* node;
	LinkedNode* prev;
	int index;

	head = (LinkedNode**) a;
	prev = NULL;
	if (a == NULL)
		return -1;
	node = *head;
	if (node == NULL)
		return -1;
	index = 0;

	while (node != NULL && node->type != b) {
		prev = node;
		node = node->next;
		index++;
	}
	if (node == NULL)
		return -2;

	if (node->children != NULL)
		gm_FreeObjectListRecursive(&node->children);
	gm_ClearObjektResources(node);
	if (index == 0)
		*head = node->next;
	else
		prev->next = node->next;
	node->type = 0;
	g_query_limit--;
	return 0;
}

void __cdecl gm_ClearObjektResources(LinkedNode* node)
{
#ifndef REBREW_SERVER
    if ((g_99ec10 + node->type * 64)[node->type] == 0x1d && *(int*) ((char*) node + 0x29) != 0) {
        fcn_004be280(*(char**) ((char*) node + 0x29));
        *(int*) ((char*) node + 0x29) = 0;
    }
#endif
}
/* Removes an id, decrements the query count; returns -1 for empty, -2 for missing. */
int __cdecl gm_RemoveLinkedNodeById(int a, int b, int c)
{
	LinkedNode** head;
	LinkedNode* node;
	LinkedNode* prev;
	int index;

	head = (LinkedNode**) a;
	node = *head;
	prev = NULL;
	if (node == NULL)
		return -1;
	index = 0;

	while (node != NULL && node->entity_id != b) {
		prev = node;
		node = node->next;
		index++;
	}
	if (node == NULL)
		return -2;

	if (node->children != NULL)
		gm_FreeObjectListRecursive(&node->children);
	gm_ClearObjektResources(node);
	if (index == 0)
		*head = node->next;
	else
		prev->next = node->next;
	node->type = 0;
	g_query_limit--;
	return 0;
}

int __cdecl gm_FreeObjectListRecursive(LinkedNode** head)
{
	LinkedNode* node;

	if (head == NULL)
		return 0;
	node = *head;
	if (node == NULL)
		return -1;
	do {
		*head = node->next;
		if (node->children != NULL)
			gm_FreeObjectListRecursive((LinkedNode**) &node->children);
		gm_ClearObjektResources(node);
		node = *head;
	} while (node != NULL);
	return 0;
}

/* 0x1001a299 */

#ifndef REBREW_SERVER
#include "../../Units/d3/d3_object.h"
extern int g_6b8010;
int __cdecl fcn_005155e0(unsigned char*);
void __cdecl fcn_004432d0(int, int);
char* __cdecl fcn_00445600(char*, int, char*, char*);
void __cdecl fcn_00455350(char*, float*, float*);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl fcn_00404a00(char*, int, ...);
void __cdecl fcn_00510820(char*, unsigned char*, int);
D3_OBJECT* __cdecl fcn_00442910(D3_OBJECT*, float*, float*, char*);
void* __cdecl fcn_00403ce0(char*, D3_OBJECT*);
char __cdecl SelectTextureSet(D3_OBJECT*, void*, unsigned char, char);
void __cdecl fcn_00402a00(char*, int);
#endif

/* ADDRESS: SERVER 0x10016760 */
/* ADDRESS: GOLDTL 0x00502fe0 */
/* ADDRESS: GOLD 0x00500190 */
char* __cdecl gm_AllocObjekt(int parent_id, int type, int param3)
{
	void* dynamic;
	void* existing;
	void* static_ptr;
	char* entry;
	char buffer[0x400];
	char* slot;
	char* last;
	char* head;
	char* cur;
	char* extra;
	char* child;
	int walk_id;
#ifndef REBREW_SERVER
	float position[4];
	float rotation[3];
	char* model;
	char* found;
	char* owner_entity;
	D3_OBJECT* scene;
	int universe;
	int saved_mode;
	int owner_ref;
	int choice;
	unsigned char lod;
#endif

	existing = NULL;
	dynamic = NULL;
	static_ptr = NULL;
	last = NULL;
	slot = NULL;
#ifndef REBREW_SERVER
	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 0.0f;
	position[3] = 0.0f;
	rotation[0] = 0.0f;
	rotation[1] = 0.0f;
	rotation[2] = 0.0f;
#endif
	if (g_item_def_table == NULL) {
		return NULL;
	}
	if (parent_id == -1) {
#ifdef REBREW_SERVER
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcb2, "gm_AllocObjekt(): Versuch Objekt au\337erhalb einer Hirachie zu erzeugen", 1);
#endif
		return NULL;
	}
	if (gm_ResolveEntityById(&dynamic, &existing, &static_ptr, parent_id) == 0) {
#ifdef REBREW_SERVER
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcb8, "gm_AllocObjekt(): Parent not found", 1);
#endif
		return NULL;
	}
	if (dynamic != NULL) {
		head = (char*) dynamic + 0x5d;
	} else if (existing != NULL) {
		head = (char*) existing + 0x14;
	} else if (static_ptr != NULL) {
		head = (char*) static_ptr + 0x178;
	} else {
		return NULL;
	}
	if (head != NULL) {
		if (*(char**) head != NULL) {
			cur = *(char**) head;
			while (cur != NULL) {
				last = cur;
				cur = *(char**) (cur + 0x3f);
			}
			slot = gm_AllocateObjectSlot();
			if (slot == NULL) {
#ifdef REBREW_SERVER
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcd4, "gm_AllocObjekt(): Kein Platz mehr", 1);
#endif
				return NULL;
			}
			*(char**) (last + 0x3f) = slot;
		} else {
			slot = gm_AllocateObjectSlot();
			if (slot == NULL) {
#ifdef REBREW_SERVER
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcdd, "gm_AllocObjekt(): Kein Platz mehr", 1);
#endif
				return NULL;
			}
			*(char**) head = slot;
		}
	}

	entry = g_item_def_table + (type << 6) + type;
	*(unsigned short*) slot = (unsigned short) type;
	sprintf(buffer, "----->ObjID= %i ObjProt= %i", g_next_object_id, type & 0xffff);
#ifdef REBREW_SERVER
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcee, buffer, 8);
#endif
	*(int*) (slot + 2) = g_next_object_id;
	g_next_object_id++;
	if (dynamic != NULL) {
		*(int*) (slot + 0xa) = *(int*) ((char*) dynamic + 1);
	} else if (existing != NULL) {
		*(int*) (slot + 0xa) = *(int*) ((char*) existing + 0xa);
	} else if (static_ptr != NULL) {
		*(int*) (slot + 0xa) = *(int*) ((char*) static_ptr + 4);
	}
	*(int*) (slot + 6) = parent_id;
	*(int*) (slot + 0xe) = param3;
	slot[0x12] = 0x64;
	slot[0x13] = 0;
	*(int*) (slot + 0x14) = 0;
	*(int*) (slot + 0x3f) = 0;
	g_query_limit++;
	extra = slot + 0x1c;
	memset(extra, 0, 0x1f);

	switch (type) {
	case 0x12c:
		*(int*) extra = -1;
		*(int*) (slot + 0x20) = -1;
		*(int*) (slot + 0x24) = -1;
		*(int*) (slot + 0x28) = g_current_year - 1;
		break;
	case 0x12d:
		*(int*) extra = -1;
		*(int*) (slot + 0x20) = -1;
		*(int*) (slot + 0x24) = -1;
		*(int*) (slot + 0x28) = -1;
		break;
	case 0xb8:
		*extra = 6;
		break;
	case 0x134:
	case 0x135:
	case 0x136:
		if (dynamic != NULL) {
			*(int*) (slot + 0xa) = *(int*) ((char*) &g_entity_id_field
				+ *(unsigned short*) ((char*) dynamic + 0x27) * 0x21c);
		} else if (existing != NULL) {
			*(int*) (slot + 0xa) = *(int*) ((char*) gm_ResolveParentEntity((short*) existing) + 4);
		} else if (static_ptr != NULL) {
			*(int*) (slot + 0xa) = *(int*) ((char*) static_ptr + 4);
		}
		walk_id = parent_id;
		while (gm_ResolveEntityById(&dynamic, &existing, &static_ptr, walk_id) != 0) {
			if (dynamic != NULL) {
				break;
			}
			if (existing != NULL) {
				walk_id = *(int*) ((char*) existing + 6);
			} else if (static_ptr != NULL) {
#ifdef REBREW_SERVER
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xd3d, "gm_AllocObjekt(): Karren in Spieler erzeugt?!?", 1);
#endif
			}
		}
		slot[0x28] = 0;
		slot[0x31] = 2;
		if (dynamic != NULL) {
			*(int*) extra = *(int*) ((char*) dynamic + 1);
		} else {
			*(int*) extra = -1;
		}
		child = gm_AllocObjekt(*(int*) (slot + 2), 0x1dd, 1);
#ifndef REBREW_SERVER
		universe = 0;
#endif
		*(int*) (child + 0xe) = (int) *(unsigned short*) slot - 0x133;
		child[0x1c] = (char) (*slot - 0x33);
#ifndef REBREW_SERVER
		existing = gm_StartFilteredEntitySearch(1, 1, parent_id);
		if (existing != NULL && gm_CheckEntityType((unsigned char*) existing) != 0)
			universe = fcn_005155e0((unsigned char*) existing);
		saved_mode = g_6b8010;
		fcn_004432d0(universe, 1);
		if (gm_CheckEntityType((unsigned char*) existing) != 0)
			found = fcn_00445600(NULL, 0x100, NULL, "dummy_TRANSPORTER");
		else
			found = fcn_00445600(*(char**) ((char*) existing + 0x61), 0x100, NULL, "dummy_TRANSPORTER");
		if (found != NULL) {
			fcn_00455350(found, (float*) (found + 0x4c), position);
		} else if (*(char**) ((char*) existing + 0x61) != NULL) {
			position[0] = *(float*) (*(char**) ((char*) existing + 0x61) + 0x4c);
			position[1] = *(float*) (*(char**) ((char*) existing + 0x61) + 0x50);
			position[2] = *(float*) (*(char**) ((char*) existing + 0x61) + 0x54);
		} else {
			position[0] = 0.0f;
			position[1] = 0.0f;
			position[2] = 0.0f;
		}
		if (type != 0x136) {
			choice = (unsigned short) gm_RandomMod(3);
			if (choice == 0)
				model = fcn_00403b90("arbeiter_KARREN", position);
			else if (choice == 1)
				model = fcn_00403b90("holzfaeller_KARREN", position);
			else
				model = fcn_00403b90("handwerker_KARREN", position);
		} else {
			model = fcn_00403b90("pferd_PFERD", position);
		}
		*(char**) (slot + 0x3b) = model;
		fcn_00404a00(model, 1, "bewegung/karren_ziehen");
		fcn_00510820(*(char**) (model + 0x34), (unsigned char*) slot, 1);
		sprintf(*(char**) (model + 0x34), "sp_%i", *(int*) (slot + 2));
		scene = NULL;
		if (type == 0x134)
			scene = fcn_00442910(NULL, position, rotation, "ob_KARREN_klein");
		else if (type == 0x135)
			scene = fcn_00442910(NULL, position, rotation, "ob_KARREN_mittel");
		else if (type == 0x136)
			scene = fcn_00442910(NULL, position, rotation, "ob_KARREN_GROSS");
		if (scene != NULL) {
#ifdef REBREW_GOLD
			scene->flags2 = (scene->flags2 & ~8) | 4;
			scene->rest &= ~2;
#else
			scene->flags2 = (scene->flags2 & ~2) | 1;
			scene->flags0 &= ~0x80;
#endif
			fcn_00403ce0(model, scene);
			owner_entity = (char*) static_ptr;
			if (owner_entity == NULL && dynamic != NULL && *(unsigned short*) ((char*) dynamic + 0x27) != 0xffff)
				owner_entity = g_slot_table + *(unsigned short*) ((char*) dynamic + 0x27) * 0x21c;
			if (owner_entity != NULL && *(int*) (owner_entity + 0x54) != 0 &&
				(owner_entity[2] == 5 || owner_entity[2] == 6 || owner_entity[2] == 7)) {
				lod = (unsigned char) (owner_entity[0x54] + 0x67);
				if (lod != 0)
					SelectTextureSet(scene, scene->kontext, lod, 1);
			}
			scene->unbekannt_224 = 1;
			fcn_00510820((char*) scene, (unsigned char*) slot, 1);
		}
		if (existing != NULL && gm_CheckEntityType((unsigned char*) existing) == 0) {
			fcn_00402a00(model, 0);
			*(int*) (model + 0x30) = -1;
			*(int*) (model + 0x2c) = -1;
		} else if (existing != NULL && gm_CheckEntityType((unsigned char*) existing) != 0) {
			owner_ref = *(int*) ((char*) existing + 1);
			*(int*) (model + 0x30) = -1;
			*(int*) (model + 0x2c) = owner_ref;
		} else {
			*(int*) (model + 0x30) = -1;
			*(int*) (model + 0x2c) = -1;
		}
		*(int*) (slot + 0x24) = 0;
		fcn_004432d0(saved_mode, 1);
#endif
		break;
	case 0x15e:
	case 0x160:
		*(int*) (slot + 0x20) = 0xf;
		break;
	case 0x174:
	case 0x176:
		*(int*) (slot + 0x20) = 6;
		break;
	case 0x24b:
	case 0x256:
	case 0x266:
		*(int*) extra = 0;
		*(int*) (slot + 0x20) = 0;
		break;
	default:
		break;
	}

	if (*entry == 0x17 || *entry == 0x20 || *entry == 0x25) {
		*(int*) extra = 0;
	}
	return slot;
}

/* 0x1003544c */

/* Adds b units of object a to the list reachable from the resolved parent
 * entity, or accumulates the amount into an existing entry.  Returns the
 * entry pointer (or the result of gm_AllocObjekt when a new entry was
 * created). */

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

/* Client-only tavern and owner lookups (discarded). */

char* __cdecl gm_FindTavernServing(int item)
{
	char* list[8];
	int i;

	if (g_active_player_count == 0) {
		return 0;
	}
	list[0] = (char*) gm_ff_Objekt(*(int*) ((char*) g_active_player_count + 0x5d), 1, 0, 0x92);
	list[1] = (char*) gm_ff_Objekt(*(int*) ((char*) g_active_player_count + 0x5d), 1, 0, 0x93);
	list[2] = (char*) gm_ff_Objekt(*(int*) ((char*) g_active_player_count + 0x5d), 1, 0, 0x94);
	list[3] = (char*) gm_ff_Objekt(*(int*) ((char*) g_active_player_count + 0x5d), 1, 0, 0x95);
	list[4] = (char*) gm_ff_Objekt(*(int*) ((char*) g_active_player_count + 0x5d), 1, 0, 0x96);
	list[5] = (char*) gm_ff_Objekt(*(int*) ((char*) g_active_player_count + 0x5d), 1, 0, 0x97);
	list[6] = (char*) gm_ff_Objekt(*(int*) ((char*) g_active_player_count + 0x5d), 1, 0, 0x2db);
	list[7] = 0;
	for (i = 0; list[i] != 0; i++) {
		if (gm_ff_Objekt(*(int*) (list[i] + 0x14), 2, 6, 0, item) != 0) {
			return (char*) gm_ff_Objekt(*(int*) (list[i] + 0x14), 1, 0, 0x116);
		}
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_FindTavernServing(): no tavern found", 1);
	return 0;
}

void* __cdecl gm_FindKind47ByOwner(int owner)
{
	void* entry;

	entry = gm_StartFilteredEntitySearch(1, 0, 0x47);
	if (entry == 0) {
		return 0;
	}
	do {
		if (*(int*) ((char*) entry + 0x65) == owner) {
			return entry;
		}
		entry = gm_FindNextFilteredEntity();
	} while (entry != 0);
	return 0;
}

/* Scans the entity array for the next entity matching the active filter
 * state (set up by gm_StartFilteredEntitySearch).  Advances the search
 * cursor, counts inspected candidates, and returns the first match or
 * NULL once the array is exhausted.
 *
 * Byte-identical to the reference apart from relocations.  What the match
 * depends on:
 *   - `match` and `end` are set before the two entry guards, which gives the
 *     reference's prologue (`push esi; xor cl,cl; lea esi,[eax+0xa900]`).
 *   - No `return` inside the pre-scan cursor loops.  A return in the
 *     no-flag advance loop made msvc6 merge every `return 0` into one far
 *     block; without it each entry guard keeps its own inline
 *     `xor eax,eax; pop esi; ret`, as in the reference.
 *   - Both pre-scan loops walk g_query_filter_base itself, and the local is
 *     read from it afterwards.  With a local cursor msvc6 hoisted the global
 *     load above the flag test and threaded the flag-49 loop's exit.
 *   - The scan loop is `while (match == 0)`, so its back edge is the
 *     reference's `test cl,cl; je top` with the epilogue duplicated after it.
 *   - Each filter mismatch is its own `else { match = 0; goto counted; }`.
 *     msvc6 cross-jumps the four copies into one out-of-line block, which is
 *     where the reference has it; a shared `no_match:` label kept the block
 *     inline after the last filter.
 *   - The advance loop's odd `while (*list_head == 0 || 1)` head is
 *     load-bearing: `for (;;)` and a do/while both change the object. */



void* __cdecl gm_FindNextFilteredEntity(void)
{
	unsigned char* list_head;
	unsigned char* end;
	unsigned char match;

	match = 0;
	end = (unsigned char*) g_entity_ptr + 0xa900;
	if (g_entity_type_table == 0) {
		return 0;
	}
	if (g_dynasty_scan_count > 0x100) {
		return 0;
	}
	if (g_dynasty_scan_flag != 0) {
		g_dynasty_scan_flag = 0;
		while (g_query_filter_base < end) {
			if (*g_query_filter_base != 0) {
				break;
			}
			g_query_filter_base += 0xa9;
		}
	} else {
		do {
			g_query_filter_base += 0xa9;
		} while (g_query_filter_base < end && *g_query_filter_base == 0);
	}
	list_head = g_query_filter_base;
	if (list_head >= end) {
		return 0;
	}
	while (match == 0) {
		if (g_dynasty_name_ready != 0) {
			match = 1;
		}
		if (g_filter_extra5 != 0xff) {
			if (*list_head == g_filter_extra5) {
				match = 1;
			} else {
				match = 0;
				goto counted;
			}
		}
		if (g_query_filter_extra1 != -1) {
			if (*(int*) (list_head + 1) == g_query_filter_extra1) {
				match = 1;
			} else {
				match = 0;
				goto counted;
			}
		}
		if (g_query_filter_extra2 != 0x7fff) {
			if (*(short*) (list_head + 0x25) == g_query_filter_extra2) {
				match = 1;
			} else {
				match = 0;
				goto counted;
			}
		}
		if (g_query_filter_extra3 != 0x7fff) {
			if (*(short*) (list_head + 0x27) == g_query_filter_extra3) {
				match = 1;
			} else {
				match = 0;
				goto counted;
			}
		}
		if (g_query_filter_extra4 != 0xff) {
			match = (*(unsigned char*) ((char*) g_entity_type_table + *list_head + *list_head * 588) ==
			         g_query_filter_extra4);
		}
	counted:
		g_dynasty_scan_count++;
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
	}
	if (match == 0) {
		g_query_filter_base = 0;
		list_head = 0;
	}
	return list_head;
}

#pragma intrinsic(memcpy, memset, strcpy)
/* Initializes the filter state from a list of (type, value) vararg pairs.
 * Type 0 = extra5 (byte), 1 = extra1 (int), 2 = dynasty string copy,
 * 3 = extra2 (short), 4 = extra3 (short), 5 = extra4 (byte), 6 = field_48.
 * Returns the first filtered entity. */
unsigned short* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...)
{
	int* arg_ptr;
	int i;

	if (g_entity_type_table == 0) {
		return (unsigned short*) 0;
	}

	g_filter_extra5 = 0xff;
	g_query_filter_extra2 = 0x7fff;
	g_query_filter_extra3 = 0x7fff;
	g_query_filter_extra1 = -1;
	g_dynasty_name = 0;
	g_query_filter_extra4 = 0xff;
	g_dynasty_scan_flag = 1;
	g_dynasty_scan_count = 0;
	g_dynasty_name_ready = 0;

	if (arg_count > 0) {
		arg_ptr = &arg_count;

		for (i = arg_count; i > 0; i--) {
			unsigned char ftype;

			arg_ptr++;
			ftype = *(unsigned char*) arg_ptr;
			switch (ftype) {
			case 0:
				g_filter_extra5 = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 1:
				g_query_filter_extra1 = *(arg_ptr + 1);
				arg_ptr++;
				break;
			case 2:
				arg_ptr++;
				strcpy((char*) g_dynasty_name, *(char**) arg_ptr);
				break;
			case 3:
				g_query_filter_extra2 = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 4:
				g_query_filter_extra3 = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 5:
				g_query_filter_extra4 = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 6:
				g_dynasty_name_ready = 1;
				break;
			default:
				break;
			}
		}
	}

	g_query_filter_base = g_entity_ptr;
	return (unsigned short*) gm_FindNextFilteredEntity();
}

char* __cdecl gm_SearchStruct(void)
{
	EntityQueryRecord* entity_cursor;
	EntityQueryRecord* end;
	entity_cursor = (EntityQueryRecord*) g_entity_ptr;
	end = entity_cursor + 0x100;
	while (entity_cursor < end) {
		if (entity_cursor->type == 0) {
			break;
		}
		entity_cursor++;
	}
	if (entity_cursor < end) {
		return entity_cursor;
	}
	return 0;
}

/* Cleans up a building entity. Frees all contained entities
 * (workers, inventory, production slots) and resets the
 * building to an empty state. */



/* g_entity_records: base of entity array, stride 0x21c (0x87 dwords), 768 entries */

int __cdecl gm_CleanupBuildingEntity(unsigned char* building)
{
	int* entity_scan;

	if (building == (unsigned char*) 0) {
		return -1;
	}
	if (*building == 0) {
		return -2;
	}
	switch (*building) {
	case 0x1e:
		if (*(void**) (building + 0x71) != (void*) 0) {
			m_FreeTracked(*(void**) (building + 0x71));
			*(int*) (building + 0x71) = 0;
		}
		*(int*) (building + 0x71) = 0;
		goto cleanup_loop;
	case 0x48:
	case 0x49:
	case 0x4a:
		gv_Free3Fields(*(void**) (building + 0x65));
		break;
	case 0x4b:
	case 0x4c:
	case 0x4d:
		m_FreeTracked(*(void**) (building + 0x65));
		break;
	default:
		goto cleanup_loop;
	}
	*(int*) (building + 0x65) = 0;
cleanup_loop:
	entity_scan = &g_entity_records;
	do {
		if ((unsigned char*) entity_scan[1] == building) {
			entity_scan[1] = 0;
		}
		if ((unsigned char*) *entity_scan == building) {
			*entity_scan = 0;
		}
		entity_scan = entity_scan + 0x87;
	} while ((int) entity_scan < (int) ((char*) &g_entity_records + 0x65400));
	if (*(int*) (building + 0x5d) != 0) {
		gm_FreeObjectListRecursive((LinkedNode**) (building + 0x5d));
	}
	*building = 0;
	return 0;
}

/* Allocates default values for a building entity. Sets up
 * initial worker capacity, production slots, and storage
 * based on building type. */


void __cdecl gm_AllocBuildingDefaults(unsigned char* building)
{
	void* query_result;
	int inner_count;
	unsigned short* item_ptr;
	unsigned char* table_ptr;

	table_ptr = (unsigned char*) g_building_defaults[0].object_ids;
	do {
		if (*building == *(table_ptr - 1)) {
			query_result = gm_ff_Objekt(*(int*) (building + 0x5d), 2, 6, 0, 0xff);
			if (query_result != (void*) 0) {
				goto do_inner;
			}
			query_result = gm_AllocObjekt(*(int*) (building + 1), 0xff, 1);
			if (query_result != (void*) 0) {
			do_inner:
				inner_count = 10;
				item_ptr = (unsigned short*) table_ptr;
				do {
					if (*item_ptr != 0 &&
						gm_ff_Objekt(*(int*) ((int) query_result + 0x14), 1, 0, (unsigned int) *item_ptr) ==
							(void*) 0) {
						gm_AllocObjekt(*(int*) ((int) query_result + 2), (unsigned int) *item_ptr, 2);
					}
					item_ptr = item_ptr + 1;
					inner_count = inner_count - 1;
				} while (inner_count != 0);
			}
			else {
				LogMessageInternal(
					"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
					0x107f,
					"gm_AllocGebaeude(): Missing potential....",
					1
				);
			}
		}
		table_ptr = table_ptr + 0x15;
	} while ((int) table_ptr < (int) ((char*) g_building_defaults + 0x30a));
}

/* Sets worker limits for a building based on its type and
 * upgrade level. Reads from the building type table. */


void __cdecl gm_SetBuildingWorkerLimits(unsigned char* building)
{
	unsigned char* entry;
	unsigned char* query_result;
	int type;

	type = building[0];
	entry = (unsigned char*) (g_entity_type_table + type + type * 588);
	query_result = (unsigned char*) gm_ff_Objekt(*(int*) (building + 0x5d), 2, 0, 0x2a, 6);
	if (query_result != 0) {
		if (entry[0x23d] == 0 && entry[0x23e] == 0 && entry[0x23f] != 0) {
			query_result[0x1c] = entry[0x23f];
		} else {
			query_result[0x1c] = (unsigned char) (entry[0x23d] < 2 ? 2 : entry[0x23d]);
			query_result[0x1d] = (unsigned char) (entry[0x23e] < 2 ? 2 : entry[0x23e]);
		}
	}
	query_result = (unsigned char*) gm_ff_Objekt(*(int*) (building + 0x5d), 2, 0, 0x116, 6);
	if (query_result != 0) {
		if (entry[0x23d] == 0 && entry[0x23e] == 0 && entry[0x23f] != 0) {
			query_result[0x1c] = entry[0x23f];
		}
	}
}

#pragma optimize("y", off)
char* __cdecl gm_AllocGebaeude(unsigned char geb_type, unsigned short owner)
{
	char* geb;
	int count;
	/* 0x410-byte locals block: 0x400 log buffer + 4 pointer/int slots. */
	// SIZE 0x410
	struct {
		char msg[0x400];
		char* dest;
		int type_id;
		char* record;
		int flag;
	} s;

	if (g_entity_type_table == 0) {
		return NULL;
	}
	s.flag = 0;
	geb = (char*) gm_SearchStruct();
	if (geb == NULL) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x10cb, "gm_AllocGebaeude(): geb overflow HELP !!!!!!", 1);
		return NULL;
	}
	{
		char* rec;
		int nid;
		rec = g_entity_type_table + (unsigned char) geb_type * 0x24d;
		geb[0] = (char) geb_type;
		s.type_id = (unsigned char) geb_type;
		/* The named global, not `*(int*) 0x10030b6c`: a literal address may
		 * alias the address-taken `s`, which pins the load behind the
		 * `s.type_id` store and makes `nid` a coloured candidate.  Through the
		 * symbol the load is forwarded into the call as a scratch temporary,
		 * scheduled first, and every later scratch register (the two
		 * `lea r,[ebp-0x410]`, the counter loads) lands on the reference's.
		 * The `geb + 1` store keeps the literal: the symbol there swaps the
		 * base/index operands of the 0x600 table fill. */
		nid = g_next_object_id;
		s.record = rec;
		sprintf(s.msg, "----->GebID= %i GebProt= %i", nid, s.type_id);
	}
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x10d8, s.msg, 8);
	*(int*) (geb + 1) = g_next_object_id;
	g_next_object_id = g_next_object_id + 1;
	*(unsigned short*) (geb + 0x25) = (unsigned short) owner;
	*(unsigned short*) (geb + 0x27) = (unsigned short) owner;
	*(int*) (geb + 0x3d) = 0x64;
	*(int*) (geb + 0x45) = 0x64;
	geb[0x5c] = 0x64;
	*(unsigned short*) (geb + 0x29) = 0;
	*(int*) (geb + 0x2b) = 0;
	geb[0x2f] = 0;
	*(int*) (geb + 0x5d) = 0;
	*(int*) (geb + 0x61) = 0;
	*(int*) (geb + 0x30) = 0;
	*(int*) (geb + 0x39) = 0x7d00;
	*(int*) (geb + 0x41) = 2;
	*(int*) (geb + 0x49) = 0x3f800000;
	*(int*) (geb + 0x95) = -1;
	memset(geb + 0x99, 0, 0x10);
	*(int*) (geb + 0xa5) = -1;
	*(int*) (geb + 0x99) |= 1;
	/* target: mov [ebp+8],0x30; lea eax,[esi+0x65]; mov [ebp-0x10],eax; stos */
	count = 0x30;
	s.dest = geb + 0x65;
	/* The original's fill here is the 24-byte hand-written block-fill prelude
	 * (docs/msvc6-allocator.md Finding 19); no msvc6 C memset spelling emits
	 * it.  Reproduced as a block-fill with ordinary named operands. */
#ifdef REBREW_SERVER
	__asm {
		mov edi, s.dest
		mov ebx, count
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
#else
	memset(s.dest, 0, count);
#endif
	/* The full-width count reuses the dead input argument slot. */
	{
		/* The target walks a pointer (`lea edi,[record+0x23]`, `add edi,2`
		 * in the for-increment) rather than indexing by the counter, and it
		 * keeps the pointer increment AHEAD of the counter increment.  Both
		 * increments have to be in the header, or the `continue` below skips
		 * the pointer. */
		unsigned short* rec;

		count = 0;
		rec = (unsigned short*) (s.record + 0x23);
		for (; count < 0x40; count++, rec++) {
			unsigned short comp = *rec;
			char* comp_rec;
			unsigned char comp_type;

			if (comp == 0) {
				break;
			}
			if (comp == 0xffff) {
				continue;
			}
			comp_rec = (char*) g_item_def_table + (comp & 0x7fff) * 0x41;
			/* A volatile read is not folded into `[eax+ebx]`: the reference
			 * materialises the address (`mov ecx,eax; add ecx,ebx; mov cl,[ecx]`,
			 * 0x1001765d), and those 3 bytes push the loop's `je` to rel32. */
			comp_type = *(volatile unsigned char*) comp_rec;
			if (comp_type == 2 || comp_type == 6) {
				s.flag = 1;
			}
			if (comp & 0x8000) {
				if (comp_type == 2 || comp_type == 6) {
					/* the reference repeats the store here (0x1001769f) */
					s.flag = 1;
					gm_AllocRaum(geb, comp & 0x7fff);
				} else if (s.flag == 0) {
					gm_AllocObjekt(*(int*) (geb + 1), comp & 0x7fff, 1);
				}
			}
		}
	}
	{
		/* A register local: the reference never stores the query pointer. */
		unsigned short* q;

		q = gm_ff_Objekt(*(int*) (geb + 0x5d), 1, 4, 2);
		while (q != NULL) {
			if (*q != 0xfd) {
				*(unsigned short*) (geb + 0x29) = *q;
				break;
			}
			q = (unsigned short*) gm_NextEntityQueryMatch();
		}
		q = gm_SetupEntityQuery((unsigned char*) geb);
		if (q != NULL)
			*(unsigned short*) (geb + 0x29) = *q;
	}
	if (gm_CheckEntityType((unsigned char*) geb) != 0)
		*(int*) (geb + 0x30) = 0x1388;
	/* building-type switch (jump table 0x10017890 / byte map 0x100178bc). */
	switch (s.type_id) {
	case 4:
	case 5:
	case 6:
	case 7:
		*(struct blk14*) (geb + 0x69) = *(struct blk14*) &g_current_year;
		if ((unsigned short) owner != 0xffff)
			*(int*) (geb + 0x65) =
			    *(int*) ((char*) g_slot_table + 4 + (unsigned short) owner * 0x21c);
		else
			*(int*) (geb + 0x65) = -1;
		break;
	case 0x14:
	case 0x15:
	case 0x16:
		{
			/* The reference keeps this pointer in a register: there is no
			 * store of it anywhere, and the four field stores issue from the
			 * same register with no reload between them.  A local whose
			 * address is never taken cannot be aliased by a store through
			 * itself; an address-taken struct member can, which is why the
			 * previous `s.record` spelling reloaded [ebp-8] three times. */
			char* rec = (char*) gm_AllocObjekt(*(int*) (geb + 1), 0x1b5, 1);
			if (rec != NULL) {
				rec[0x22] = 0;
				rec[0x1c] = (char) -1;
				rec[0x1d] = (char) -1;
				*(int*) (rec + 0x1e) = -1;
			}
		}
		break;
	case 0x47:
		*(int*) (geb + 0x30) = 0x13880;
		break;
	case 0x1e:
		/* The reference writes the allocation only to geb+0x71 and then reads
		 * the pointer back out of that field for every use: the first store
		 * issues from the call's own result (still in eax), the second
		 * reloads `mov ecx,[esi+0x71]` because the intervening char store may
		 * alias the field.  Keeping a second copy in `s.record` was an extra
		 * store plus three extra reloads. */
		*(int*) (geb + 0x71) = (int) m_alloc(0x600, "f3_gm:PlantMap");
		/* 0x40 entries of 0x18 bytes, indexed: c2 strength-reduces the index
		 * and emits the reference's `[eax+edx-0xb]` operand order. */
		for (count = 0; count < 0x40; count++) {
			*((char*) *(int*) (geb + 0x71) + count * 0x18 + 0xd) = (char) 0xff;
			*(int*) ((char*) *(int*) (geb + 0x71) + count * 0x18 + 0x14) = 0;
		}
		/* fall through into 0x1f/0x20 stores */
	case 0x1f:
	case 0x20:
		*(int*) (geb + 0x30) = 0x64;
		*(int*) (geb + 0x49) = 0x3f4ccccd;
		break;
	case 0x35:
	case 0x36:
	case 0x37:
		*(int*) (geb + 0x65) = 0;
		*(unsigned short*) (geb + 0x69) = 0;
		*(unsigned short*) (geb + 0x6b) = 0;
		*(int*) (geb + 0x6d) = 0;
		break;
	case 0xb:
	case 0xc:
	case 0xd:
		*(int*) (geb + 0x65) = -1;
		break;
	case 0xe:
	case 0xf:
	case 0x10:
		*(int*) (geb + 0x65) = 0xa;
		*(int*) (geb + 0x69) = 3;
		*(int*) (geb + 0x6d) = 5;
		break;
	case 0x48:
	case 0x49:
	case 0x4a:
		*(int*) (geb + 0x65) = gv_AllocGraveyardField(geb);
		gv_SpawnEntities(geb, 3);
		break;
	case 0x4b:
	case 0x4c:
	case 0x4d:
		{
			char* rec = (char*) m_alloc(0x3c, "AHM_INFO");
			*(int*) (geb + 0x65) = (int) rec;
			*(int*) rec = -1;
		}
		break;
	}
	if (geb[0] == 0x26)
		*(unsigned short*) (geb + 0x29) = 0x10e;
	gm_SetBuildingWorkerLimits((unsigned char*) geb);
	gm_GetBuildingTypeCategory((unsigned char) geb[0]);
	gm_AllocBuildingDefaults((unsigned char*) geb);
	return geb;
}
#pragma optimize("", on)

/* Client-only: the building's market store, else its first store item
 * (discarded). */
void* __cdecl gm_FindBuildingStore(unsigned char* building)
{
	unsigned char* type;
	unsigned short* slot;
	void* found;
	int category;
	int item;
	int i;

	found = 0;
	category = gm_GetBuildingTypeCategory(building[0]);
	type = (unsigned char*) g_entity_type_table + building[0] * 0x24d;
	if (category == 1 || category == 7 || category == 8) {
		if (type[0] == 0x1d) {
			item = 0x205;
		}
		else if (type[0] == 0x16) {
			item = 0x12e;
		}
		else if (type[0] == 4) {
			item = 0x54;
		}
		else if (type[0] == 0x1f) {
			item = 0xfd;
		}
		else {
			item = 0;
		}
		if (item != 0) {
			found = gm_ff_Objekt(*(int*) (building + 0x5d), 1, 0, item);
			if (found != 0) {
				return found;
			}
		}
	}
	else if (category == 4) {
		return gm_ff_Objekt(*(int*) (building + 0x5d), 1, 0, 0xf7);
	}
	else if (gm_CheckEntityType(building) != 0) {
		return gm_ff_Objekt(*(int*) (building + 0x5d), 1, 0, 0xfd);
	}
	slot = (unsigned short*) (type + 0x23);
	for (i = 0; i < 0x40; i++, slot++) {
		if (*slot != 0xffff) {
			item = *slot & 0x7fff;
			if (g_item_def_table[item * 0x41] == 2 && item != 0xfd) {
				return gm_ff_Objekt(*(int*) (building + 0x5d), 1, 0, item);
			}
		}
	}
	return found;
}

unsigned short* __cdecl gm_SetupEntityQuery(unsigned char* entity)
{
	char* type_entry;
	int result;
	unsigned short* query_cursor;

	gm_GetBuildingTypeCategory((int) *entity);
	type_entry = (char*) (g_entity_type_table + (unsigned int) *entity * 0x24d);
	result = gm_CheckEntityType(entity);
	if (result != 0) {
		return (unsigned short*) gm_ff_Objekt(*(int*) (entity + 0x5d), 1, 0, 0xfd);
	}
	if (*type_entry == 4) {
		return (unsigned short*) gm_ff_Objekt(*(int*) (entity + 0x5d), 1, 0, 0x54);
	}
	query_cursor = (unsigned short*) gm_ff_Objekt(*(int*) (entity + 0x5d), 1, 4, 2);
	while (query_cursor != (unsigned short*) 0 && *query_cursor == 0xfd) {
		query_cursor = gm_NextEntityQueryMatch();
	}
	return query_cursor;
}

/* Returns the category of a building type. Maps a building
 * type ID to its category (production, storage, service, etc.). */



int __cdecl gm_GetBuildingTypeCategory(int arg1)
{
	switch (*(unsigned char*) (g_entity_type_table + arg1 * 0x24d)) {
	case 0xb:
	case 0xc:
	case 0xd:
		return 2;
	case 0x13:
		return 7;
	case 4:
	case 5:
	case 9:
		return 8;
	case 8:
	case 0xe:
	case 0x12:
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x1d:
	case 0x1f:
	case 0x20:
		return 1;
	case 1:
	case 3:
	case 6:
	case 0xf:
		return 3;
	case 7:
		return 4;
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x1a:
		return 5;
	case 2:
	case 0x1e:
		return 6;
	case 0x21:
		return 9;
	default:
		return 0;
	}
}

/* Client-only: nearest free building of `kind` to `self` (discarded). */
unsigned char* __cdecl gm_FindNearestOfKind(unsigned char* self, int kind)
{
	double __cdecl sqrt(double x);
	int __cdecl gm_IsWarehouse(unsigned char* building);
	float best;
	unsigned char* found;
	unsigned char* e;
	float* a;
	float* b;
	float dx;
	float dy;
	float dz;
	float d;

	best = 1e8f;
	found = 0;
	for (e = (unsigned char*) gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_FindNextFilteredEntity()) {
		if (gm_CheckEntityType(e) != 0 || gm_IsWarehouse(e) != 0) {
			continue;
		}
		a = *(float**) (e + 0x61);
		if (a == 0 || e == self || *e != kind || *(unsigned short*) (e + 0x27) != 0xffff) {
			continue;
		}
		b = *(float**) (self + 0x61);
		dx = a[0x13] - b[0x13];
		dy = a[0x14] - b[0x14];
		dz = a[0x15] - b[0x15];
		d = (float) sqrt(dz * dz + dy * dy + dx * dx);
		if (d < best) {
			best = d;
			found = e;
		}
	}
	return found;
}

/* Searches a specific entity table (type 0x67) for a matching
 * entry. Used for specialized entity lookups. */


void* __cdecl gm_SearchTable67(int id)
{
	char* query_cursor;
	int i;

	i = 0;
	query_cursor = (char*) g_entity_ptr;
	for (; i < 256; i++, query_cursor += 0xa9) {
		if (*(char*) query_cursor == 0) {
			continue;
		}
		if (*(int*) (query_cursor + 1) != id) {
			continue;
		}
		return (void*) (g_entity_ptr + i * 0xa9);
	}
	return 0;
}

/* Client-only (TL 0x504eb0, discarded): the building type whose name is name, or 0. */
int __cdecl gm_FindBuildingTypeByName(char* name)
{
	int i;

	for (i = 0; i < 0x58; i++) {
		if (strcmpi(name, g_entity_type_table + i * 0x24d + 1) == 0) {
			return i;
		}
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_FindBuildingTypeByName(): unknown building", 1);
	return 0;
}

/* Client-only building-type queries (discarded). */

int __cdecl gm_ListTypesOfKind(int kind, int* out)
{
	int n;
	int i;

	n = 0;
	for (i = 0; i < 0x58; i++) {
		if ((unsigned char) g_entity_type_table[i * 0x24d] == kind) {
			out[n] = i;
			n++;
		}
	}
	return n;
}

int __cdecl gm_IsWarehouse(unsigned char* building)
{
	return g_entity_type_table[*building * 0x24d] == 10;
}

/* Checks if an entity's type matches the expected class.
 * Returns non-zero if the entity type field matches. */


int __cdecl gm_CheckEntityType(unsigned char* entity_ptr)
{
	char* type_entry;

	if (entity_ptr == NULL) {
		return 0;
	}
	type_entry = (char*) g_entity_type_table + (unsigned int) *entity_ptr * 0x24d;
	if (*type_entry == 0x0b || *type_entry == 0x0d || *type_entry == 0x0c ||
	    *type_entry == 0x10 || *type_entry == 0x1c || *type_entry == 0x1d ||
	    *type_entry == 0x1f) {
		return 1;
	}
	return 0;
}

/* Client-only: the residents of `building` grouped by trade: two worker
 * lists (the building type's two trades), the master's index and the other
 * residents (discarded). */
int __cdecl gm_CollectBuildingResidents(unsigned char* building, unsigned char* home, int* out)
{
	unsigned char* type;
	unsigned char* e;
	int* first;
	int* second;
	int* other;
	int count;
	int i;

	type = (unsigned char*) g_entity_type_table + building[0] * 0x24d;
	out[0] = 0;
	for (i = 0; i < 0x18; i++) {
		out[1 + i] = 0xffff;
	}
	for (i = 0; i < 0xc; i++) {
		out[0x19 + i] = 0xffff;
	}
	out[0x25] = 0xffff;
	first = out + 1;
	second = out + 0xd;
	other = out + 0x19;
	count = 0;
	for (i = 0, e = g_slot_table + 0x165; e < g_slot_table + 0x165 + 0x300 * 0x21c; i++, e += 0x21c) {
		if (*(unsigned char**) (e + 7) != home) {
			continue;
		}
		if (type[0x22f] == e[0]) {
			*first++ = *(unsigned short*) (e - 0x165);
		}
		else if (type[0x230] == e[0]) {
			*second++ = *(unsigned short*) (e - 0x165);
		}
		else if (type[0x223] != 0 && type[0x224] != 0 && (type[0x223] == e[-1] || type[0x224] == e[-1])) {
			out[0x25] = i;
		}
		else {
			*other++ = *(unsigned short*) (e - 0x165);
		}
		count++;
	}
	out[0] = count;
	return count;
}

void __cdecl gm_AssignBuildingOwner(unsigned char* building, unsigned short new_owner, unsigned int owner_slot)
{
	char building_class;
	unsigned short prev_owner;
	unsigned char* owner_building;
	int loop_count;
	unsigned short* obj_iter;
	char* type_entry;
	int owner_index;

	type_entry = g_entity_type_table + *building * 0x24d;
	*(unsigned short*) (building + 0x25) = new_owner;
	if (owner_slot != 0xffff) {
		prev_owner = *(unsigned short*) (building + 0x27);
		if ((prev_owner != 0xffff) && (PTR_10035A10(prev_owner) == (unsigned char**) building)) {
			PTR_10035A10(prev_owner) = 0;
		}
		*(unsigned short*) (building + 0x27) = (unsigned short) owner_slot;
		if (*type_entry == '\x02') {
			owner_building = (unsigned char*) PTR_10035A10(owner_slot & 0xffff);
			if ((owner_building == 0) || (*owner_building <= *building)) {
				PTR_10035A10(owner_slot & 0xffff) = (unsigned char**) building;
			}
		}
		owner_index = owner_slot;
		if (((BYTE_100358A2(owner_index) == '\x06') || (BYTE_100358A2(owner_index) == '\a')) &&
			(loop_count = (int) gm_FindEntityByOwner((int) building), loop_count != 0)) {
			*(unsigned char*) (loop_count + 0x165) = 0;
			*(unsigned int*) (loop_count + 0x1b4) = *(unsigned int*) (loop_count + 0x1b4) & 0xfffffffe;
			building_class = *type_entry;
			if ((building_class == '\x05') || (building_class == '\t')) {
				*(unsigned int*) (loop_count + 0x16c) = 0;
			}
		}
		loop_count = 0x5008;
		obj_iter = (unsigned short*) g_query_base;
		do {
			if (((*(unsigned short*) obj_iter != 0) &&
				 (*(g_item_def_table + *(unsigned short*) obj_iter * 0x41) == '\x1d')) &&
				(*(unsigned int*) ((unsigned char*) obj_iter + 0x1c) == *(unsigned int*) (building + 1))) {
				*(unsigned int*) ((unsigned char*) obj_iter + 0xa) = DWORD_100358A4(owner_index);
				if (*(unsigned int*) ((unsigned char*) obj_iter + 0x14) != 0) {
					*(unsigned int*) (*(unsigned int*) ((unsigned char*) obj_iter + 0x14) + 0xa) =
						DWORD_100358A4(owner_index);
				}
			}
			obj_iter = (unsigned short*) ((unsigned char*) obj_iter + 0x43);
			loop_count = loop_count - 1;
		} while (loop_count != 0);
	}
}

char* __cdecl gm_AllocRaum(char* geb, int obj_id)
{
	char* obj;
	char* row;
	char* scan;
	char* query_result;
	char* sub;
	char* slot;
	char* prod;
	int i;
	int comp;
	int alloc_count;

	if (g_item_def_table == NULL || g_entity_type_table == NULL ||
	    g_query_limit + 0x40 >= 0x5008) {
		return NULL;
	}

	/* The volatile read pins the geb+1 load below the callee-save pushes, so
	 * obj_id claims esi and geb claims edi as the reference has them
	 * (prologue IDX 12-18, 672 -> 677). */
	obj = (char*) gm_AllocObjekt(*(volatile int*) (geb + 1), obj_id, 1);
	/* `row` before `i` is required: it frees ebp for the row base, which is
	 * the byte that the advance-first scan below otherwise costs. */
	row = g_entity_type_table + (unsigned char) geb[0] * 0x24d;
	i = 0;

	/* Skip past the caller's own component id in the type row.  Advancing the
	 * cursor before the read, rather than reading `scan + 2`, is what makes
	 * msvc6 split the row base and the cursor into `lea ebp,[eax+edx*4]` plus
	 * `lea eax,[ebp+0x23]` as the reference does. */
	scan = row + 0x23;
	comp = *(unsigned short*) scan & 0x7fff;
	if (comp != obj_id) {
		do {
			scan += 2;
			comp = *(unsigned short*) scan & 0x7fff;
			i++;
		} while (comp != obj_id);
	}
	i++;

	while (i < 0x40) {
		unsigned short raw = *(unsigned short*) (row + i * 2 + 0x23);
		if (raw == 0) {
			break;
		}
		if (raw != 0xffff) {
			int id = raw & 0x7fff;
			char* def = g_item_def_table + (id << 6) + id;
			if (def[0] == 2 || def[0] == 6) {
				i = 0x40;
			}
			else if (raw & 0x8000) {
				gm_AllocObjekt(*(int*) (obj + 2), id, 1);
			}
		}
		i++;
	}

	query_result = (char*) gm_ff_Objekt(*(int*) (obj + 0x14), 1, 0, 0x2a);
	if (query_result != NULL) {
		/* Source field first: the reference loads geb[1]/obj[2] before it
		 * stores the constant 2 at query_result+0xe (IDX 89/126). */
		*(int*) (query_result + 6) = *(int*) (geb + 1);
		*(int*) (query_result + 0xe) = 2;
		if (row[0x23d] == 0 && row[0x23e] == 0 && row[0x23f] != 0) {
			query_result[0x1c] = row[0x23f];
		}
		else {
			query_result[0x1c] = (char) ((unsigned char) row[0x23d] < 2 ? 2 : (unsigned char) row[0x23d]);
			query_result[0x1d] = (char) ((unsigned char) row[0x23e] < 2 ? 2 : (unsigned char) row[0x23e]);
		}
	}

	query_result = (char*) gm_ff_Objekt(*(int*) (obj + 0x14), 2, 0, 0x116, 6);
	if (query_result != NULL) {
		*(int*) (query_result + 6) = *(int*) (obj + 2);
		*(int*) (query_result + 0xe) = 2;
		if (row[0x23d] == 0 && row[0x23e] == 0 && row[0x23f] != 0) {
			query_result[0x1c] = (char) ((unsigned char) row[0x23f] < 6 ? 6 : (unsigned char) row[0x23f]);
		}
		else {
			query_result[0x1c] = (char) ((unsigned char) row[0x23d] < 6 ? 6 : (unsigned char) row[0x23d]);
			query_result[0x1d] = (char) ((unsigned char) row[0x23e] < 6 ? 6 : (unsigned char) row[0x23e]);
		}
	}

	if ((*(unsigned short*) obj >= 0x92 && *(unsigned short*) obj <= 0x97) ||
	    *(unsigned short*) obj == 0x2db) {
		slot = (char*) &g_slot_array + (unsigned int) g_current_season * 0x2a90;
		query_result = (char*) gm_ff_Objekt(*(int*) (obj + 0x14), 1, 0, 0x116);
		if (query_result != NULL) {
			query_result[0x1c] = 0xc;
			query_result[0x1d] = 0;
			*(int*) (query_result + 0xe) = 3;
		}
		else {
			ReportMessage("gm_AllocRaum(): ob_LAGERFLAECHE_ALLGEMEIN is missing in ob_MARKTSTAND!");
		}

		sub = (char*) gm_AllocObjekt(*(int*) (obj + 2), 0xff, 1);
		alloc_count = 0;
		prod = (char*) &g_producer_id_table;
		slot += 4;
		/* Signed bound: the reference ends the walk with `jl`, so the
		 * limit compare must be on int, not on the pointer (which would
		 * emit `jb`).  Testing at the bottom keeps the rotation the
		 * reference has (the loop always runs at least once). */
		do {
			if (*(unsigned short*) (slot + 0x38) == *(unsigned short*) obj &&
			    *(int*) slot != 0) {
				if (alloc_count < 0x10) {
					gm_AllocObjekt(*(int*) (sub + 2), *(unsigned short*) prod, 1);
					alloc_count++;
				}
				else {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x16a6, "gm_AllocRaum(): Too many objects in 'Marktstand'...", 1);
				}
			}
			prod += 0x80;
			slot += 0x80;
		} while ((int) prod < (int) ((char*) &g_producer_id_table + 0x2a80));
	}

	return obj;
}

int __cdecl gm_RemoveObjectWrapper(int entity_record, unsigned int obj_type)
{
	int remove_result;

	remove_result = gm_RemoveObjectByType((void**) (entity_record + 0x5d), obj_type);
	if (remove_result == -2) {
		return -3;
	}
	return 0;
}

/* Removes a link from an entity. Clears a specific entity
 * reference field, breaking the association. */


void __cdecl gm_RemoveEntityLink(int entity)
{
	int parent_entity;

	parent_entity = (int) gm_EntityAccumulate((void*) entity);
	if (parent_entity != 0) {
		gm_RemoveLinkedNodeById((int*) (parent_entity + 0x5d), *(int*) (entity + 2));
	}
}

/* 0x1000b990 */

/* Initialises an entity when it is a valid (non-empty) record. */

void __cdecl gm_InitEntityIfValid(short* entity)
{
	if (entity != 0 && *(unsigned short*) entity != 0xffff)
		amt_ClearEntityLinks(entity);
}

/* 0x1001a299 */

void __cdecl gm_KillSpieler(unsigned int index, int arg2)
{
	char buffer[0x200];
	char* entity;
	int entity_id;
	int j;
	int* base_cursor;
	int* base;

	entity = (char*) &g_slot_table + index * 0x21c;
	entity_id = *(int*) (entity + 4);
	if (*(unsigned char*) (entity + 2) != 0xf) {
		entity[8] = 0;
		*(short*) (entity + 0x28) = *(short*) &g_current_year;
		gm_InitEntityIfValid((short*) entity);
		entity[2] = 0xf;
	}
	gm_FreeObjectListRecursive((LinkedNode**) (entity + 0x178));
	if (arg2 != 0) {
		if (*(unsigned short*) entity != 0xffff) {
			g_citizen_count--;
		}
		base = (int*) &g_entity_ref_table;
		do {
			base_cursor = base;
			for (j = 0; j < 8; j++) {
				if (*base_cursor == *(int*) (entity + 4)) {
					*base_cursor = -1;
				}
				base_cursor++;
			}
			base = (int*) ((char*) base + 0x21c);
		} while ((int) base < (int) ((char*) &g_entity_ref_table + 0x65400));
		memset(entity, 0, 0x21c);
		*(unsigned short*) entity = 0xffff;
		*(int*) ((char*) &g_entity_id_field + index * 0x21c) = -1;
		/* Written as a dword loop, not memset: msvc6 expands both to the same
		 * `rep stosd`, but only this form sets edi before ecx as the original
		 * does. A memset call emits `mov ecx,8` first. */
		base_cursor = (int*) ((char*) &g_entity_ref_table + index * 0x21c);
		for (j = 0; j < 8; j++) {
			base_cursor[j] = -1;
		}
		if (arg2 == 1) {
			sprintf(buffer, "gm_KillSpieler: Killing Player <id = %i> permanently", entity_id);
		}
	} else {
		sprintf(buffer, "gm_KillSpieler: Killing Player <id = %i>, holding data", entity_id);
	}
}

/* Initializes entity slots to default/empty values. Zeros
 * link fields and sets capacity counters. */


void __cdecl gm_KillAllSpieler(void)
{
	int i;
	char* ptr;

	for (i = 0; i < 0x300; i++) {
		gm_KillSpieler(i, 2);
	}

	ptr = (char*) g_entity_base;
	do {
		memset(ptr, 0, 0xAC);
		*(short*) ptr = (short) 0xFFFF;
		ptr = ptr + 0xAC;
	} while ((int) ptr < (int) g_entity_end);

	g_citizen_count = 0;
	g_next_family_index = 0;
	gm_CurrentHumanFamilyCount = 0;
}

/* Checks if a value is within a range [min, max]. Returns
 * non-zero if within bounds. */

/* Client-only (TL 0x506d50, discarded): the 6-byte g_stat_table record of stat, record 0 for stat 0x5f
 * and above (the client's table at 0x699398, spiel .data at the round-18 offset). */
typedef struct {
	short w[3];
} STAT_REC;

STAT_REC __cdecl gm_GetStatRecord(int stat)
{
	if (stat >= 0x5f) {
		return ((STAT_REC*) g_stat_table)[0];
	}
	return ((STAT_REC*) g_stat_table)[stat];
}

int __cdecl gm_IsInRange(int x)
{
	int stat_range;
	stat_range = gm_MapEntityStatRange(x);
	if (stat_range >= 10 && stat_range <= 14) {
		return 0;
	}
	return 2;
}

/* Checks if an entity type is of a specific class. Returns
 * non-zero if the type matches the expected entity class. */

int __cdecl gm_EntityClassCheck(int type)
{
	switch (type) {
	case 5:
	case 6:
	case 13:
	case 14:
	case 25:
	case 26:
		return 2;
	case 1:
	case 2:
	case 3:
	case 4:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
		return 0;
	default:
		return 2;
	}
}

/* Client-only office, profession and skill tables (discarded). */

int __cdecl gm_EntityHasOffice(unsigned short slot, int n, ...)
{
	unsigned char* e;
	int* role;
	int found;
	int i;

	found = 0;
	e = g_slot_table + slot * 0x21c;
	if (n <= -1) {
		return found;
	}
	role = &n + 1;
	for (i = 0; i < n && !found; i++, role++) {
		if (e[0x166] == *role || e[0x169] == *role) {
			found = 1;
		}
	}
	return found;
}

int __cdecl gm_EntityHasProfession(unsigned short slot, int n, ...)
{
	unsigned char profession;
	int* wanted;
	int found;
	int i;

	found = 0;
	profession = g_slot_table[slot * 0x21c + 0x164];
	if (n <= -1) {
		return found;
	}
	wanted = &n + 1;
	for (i = 0; i < n; i++, wanted++) {
		if (profession == *wanted) {
			found = 1;
			break;
		}
	}
	return found;
}

/* Client-only (TL 0x506ee0, discarded): 1 when slot's kind byte (+0x164) equals one of the n ints that
 * follow. */
int __cdecl gm_SlotKindIsOneOf(unsigned short slot, int n, ...)
{
	struct SLOT_COPY {
		unsigned char head[0x164];
		unsigned char kind;
		unsigned char tail[0x21c - 0x165];
	} rec;
	va_list ap;
	int r;
	int i;

	r = 0;
	rec = ((struct SLOT_COPY*) g_slot_table)[slot];
	if (n <= -1) {
		return r;
	}
	va_start(ap, n);
	for (i = 0; i < n; i++) {
		if (rec.kind == va_arg(ap, int)) {
			r = 1;
			break;
		}
	}
	va_end(ap);
	return r;
}

int __cdecl gm_GetGuildBuildingKind(int guild)
{
	switch (guild) {
	case 1:
		return 0xf;
	case 7:
		return 4;
	case 6:
		return 7;
	case 2:
		return 0x17;
	case 3:
		return 0x18;
	case 4:
		return 0x19;
	case 5:
		return 0x1a;
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetGuildBuildingKind(): kind not found", 1);
	return 0;
}

int __cdecl gm_GetStatBuildingKind(int stat)
{
	int range;

	range = gm_MapEntityStatRange(stat);
	if (range == 0) {
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetStatBuildingKind(): range not found", 1);
		return 0;
	}
	switch (range) {
	case 11:
		return 0x4;
	case 9:
		return 0x5;
	case 7:
		return 0x7;
	case 6:
		return 0x8;
	case 8:
		return 0x9;
	case 5:
		return 0xe;
	case 12:
		return 0x10;
	case 1:
		return 0x12;
	case 10:
		return 0x13;
	case 2:
		return 0x14;
	case 3:
		return 0x15;
	case 4:
		return 0x16;
	case 13:
		return 0x1d;
	case 16:
		return 0;
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetStatBuildingKind(): kind not found", 1);
	return 0;
}

int __cdecl gm_GetRangeBuildingKind(int range)
{
	switch (range) {
	case 11:
		return 0x4;
	case 9:
		return 0x5;
	case 7:
		return 0x7;
	case 6:
		return 0x8;
	case 8:
		return 0x9;
	case 5:
		return 0xe;
	case 12:
		return 0x10;
	case 1:
		return 0x12;
	case 10:
		return 0x13;
	case 2:
		return 0x14;
	case 3:
		return 0x15;
	case 4:
		return 0x16;
	case 13:
		return 0x1d;
	case 16:
		return 0;
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetRangeBuildingKind(): kind not found", 1);
	return 0;
}

int __cdecl gm_GetSkillPair(int skill, int* first, int* second)
{
	switch (skill) {
	case 2:
		*first = 1;
		*second = 0;
		return 1;
	case 4:
		*first = 1;
		*second = 2;
		return 1;
	case 5:
		*first = 1;
		*second = 0;
		return 1;
	case 6:
		*first = 0;
		*second = 1;
		return 1;
	case 7:
		*first = 4;
		*second = 1;
		return 1;
	case 8:
		*first = 0;
		*second = 3;
		return 1;
	case 9:
		*first = 0;
		*second = 4;
		return 1;
	case 10:
		*first = 3;
		*second = 2;
		return 1;
	case 11:
		*first = 2;
		*second = 3;
		return 1;
	case 12:
		*first = 3;
		*second = 2;
		return 1;
	case 13:
		*first = 2;
		*second = 0;
		return 1;
	}
	*first = 1;
	*second = 0;
	return 1;
}

int __cdecl gm_GetStatFirstItem(int stat)
{
	int range;

	range = gm_MapEntityStatRange(stat);
	if (range == 0) {
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetStatFirstItem(): range not found", 1);
		return 0;
	}
	switch (range) {
	case 11:
		return 0xb;
	case 9:
		return 0xe;
	case 7:
		return 0x14;
	case 6:
		return 0x17;
	case 8:
		return 0x1a;
	case 5:
		return 0x21;
	case 12:
		return 0x27;
	case 1:
		return 0x29;
	case 10:
		return 0x2c;
	case 2:
		return 0x2f;
	case 3:
		return 0x32;
	case 4:
		return 0x35;
	case 13:
		return 0x48;
	case 15:
		return 0x51;
	case 14:
		return 0x4e;
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetStatFirstItem(): item not found", 1);
	return 0;
}

int __cdecl gm_GetItemGuild(int item)
{
	if (item >= 1 && item <= 6) {
		return 7;
	}
	if (item >= 0x28 && item <= 0x2d) {
		return 7;
	}
	if (item >= 0x23 && item <= 0x27) {
		return 2;
	}
	if (item >= 0x2e && item <= 0x33) {
		return 3;
	}
	if (item >= 0x3a && item <= 0x3f) {
		return 4;
	}
	if (item >= 0x40 && item <= 0x45) {
		return 5;
	}
	if (item >= 0xd && item <= 6) {
		return 6;
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetItemGuild(): guild not found", 1);
	return 0;
}

int __cdecl gm_GetRangeStatId(int range, int level)
{
	int d;

	if (range == 0) {
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetRangeStatId(): range not found", 1);
		return 0;
	}
	d = level - 1;
	switch (range) {
	case 11:
		return 0x6 - d;
	case 9:
		return 0xc - d;
	case 7:
		return 0x12 - d;
	case 6:
		return 0x18 - d;
	case 8:
		return 0x1e - d;
	case 5:
		return 0x27 - d;
	case 12:
		return 0x2d - d;
	case 1:
		return 0x33 - d;
	case 10:
		return 0x39 - d;
	case 2:
		return 0x3f - d;
	case 3:
		return 0x45 - d;
	case 4:
		return 0x4b - d;
	case 13:
		return 0x51 - d;
	case 15:
		return 0x5e - d;
	case 14:
		return 0x58 - d;
	case 16:
		return 0;
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetRangeStatId(): stat not found", 1);
	return 0;
}

/* Returns the occupation code when its group matches stat_id.
 * Otherwise reads the group byte from the table entry, or returns zero. */



int __cdecl gm_CheckStatLevel(int entity_idx, int stat_id)
{
	int idx;
	int val;
	int result;

	idx = entity_idx * 0x21c;
	val = gm_MapEntityStatRange((int) g_entity_type_bytes[idx]);
	if (val == stat_id) {
		return (unsigned int) g_entity_type_bytes[idx];
	}
	result = (int) gm_GetEntityTableEntry((char*) &g_slot_table + idx);
	if (result == 0) {
		return 0;
	}
	return (unsigned int) *(unsigned char*) (result + 0x74 + stat_id);
}

/* Client-only building-kind and guild-hall helpers (discarded). */

int __cdecl gm_GetKindStatRange(int kind)
{
	switch (kind) {
	case 4:
		return 0xb;
	case 5:
		return 9;
	case 7:
		return 7;
	case 8:
		return 6;
	case 9:
		return 8;
	case 14:
		return 5;
	case 16:
		return 0xc;
	case 18:
		return 1;
	case 19:
		return 0xa;
	case 20:
		return 2;
	case 21:
		return 3;
	case 22:
		return 4;
	case 29:
		return 0xd;
	case 31:
		return 0xe;
	case 32:
		return 0xf;
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetKindStatRange(): range not found", 1);
	return 0;
}

/* Client-only (TL 0x5079f0, discarded): 1 when the guild has a guild hall. */
int __cdecl gm_HasGuildHall(int guild)
{
	char* __cdecl gm_GetGuildHall(int guild);

	return gm_GetGuildHall(guild) != 0;
}

void __cdecl gm_RingGuildHallBell(int guild)
{
	char* __cdecl gm_GetGuildHall(int guild);
	char* hall;

	hall = gm_GetGuildHall(guild);
	if (guild == 1) {
		gm_ff_Objekt(*(int*) (hall + 0x5d), 2, 6, 0, 0x115);
	}
	else {
		gm_ff_Objekt(*(int*) (hall + 0x5d), 2, 6, 0, 0x142);
	}
}

/* Maps an occupation code to its group.
 * Codes 0 and 82, and out-of-range codes, return zero. */


int __cdecl gm_MapEntityStatRange(int stat_id)
{
	switch (stat_id) {
	case 0:
		return 0;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		return 0xb;
	case 7:
	case 8:
	case 9:
	case 10:
	case 0xb:
	case 0xc:
		return 9;
	case 0xd:
	case 0xe:
	case 0xf:
	case 0x10:
	case 0x11:
	case 0x12:
		return 7;
	case 0x13:
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
	case 0x18:
		return 6;
	case 0x19:
	case 0x1a:
	case 0x1b:
	case 0x1c:
	case 0x1d:
	case 0x1e:
		return 8;
	case 0x1f:
	case 0x20:
	case 0x21:
		return 0x10;
	case 0x22:
	case 0x23:
	case 0x24:
	case 0x25:
	case 0x26:
	case 0x27:
		return 5;
	case 0x28:
	case 0x29:
	case 0x2a:
	case 0x2b:
	case 0x2c:
	case 0x2d:
		return 0xc;
	case 0x2e:
	case 0x2f:
	case 0x30:
	case 0x31:
	case 0x32:
	case 0x33:
		return 1;
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
		return 10;
	case 0x3a:
	case 0x3b:
	case 0x3c:
	case 0x3d:
	case 0x3e:
	case 0x3f:
		return 2;
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x44:
	case 0x45:
		return 3;
	case 0x46:
	case 0x47:
	case 0x48:
	case 0x49:
	case 0x4a:
	case 0x4b:
		return 4;
	case 0x4c:
	case 0x4d:
	case 0x4e:
	case 0x4f:
	case 0x50:
	case 0x51:
		return 0xd;
	case 0x59:
	case 0x5a:
	case 0x5b:
	case 0x5c:
	case 0x5d:
	case 0x5e:
		return 0xf;
	case 0x53:
	case 0x54:
	case 0x55:
	case 0x56:
	case 0x57:
	case 0x58:
		return 0xe;
	default:
		return 0;
	}
}

/* Client-only: the stat range of an item pair id (discarded). */
int __cdecl gm_MapItemPairRange(unsigned int item)
{
	switch (item) {
	case 0:
		return 0;
	case 1:
	case 2:
		return 0xb;
	case 3:
	case 4:
		return 0x7;
	case 5:
	case 6:
		return 0x6;
	case 7:
	case 8:
		return 0x8;
	case 13:
	case 14:
		return 0x5;
	case 15:
	case 16:
		return 0xc;
	case 17:
	case 18:
		return 0x1;
	case 19:
	case 20:
		return 0xa;
	case 21:
	case 22:
		return 0x2;
	case 23:
	case 24:
		return 0x3;
	case 25:
	case 26:
		return 0x4;
	case 27:
	case 28:
		return 0xd;
	case 31:
	case 32:
		return 0xe;
	case 33:
	case 34:
		return 0xf;
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_MapItemPairRange(): pair not found", 1);
	return 0;
}

/* Returns the opposite stat index for paired stats.
 * E.g., maps strength to weakness, charisma to shyness.
 * Used for character stat balancing. */


/*
 * Mirrors/reverses the position of an index within its group of 6.
 * Each group of 6 consecutive values gets its position flipped:
 *   groupStart -> groupStart+5, groupStart+1 -> groupStart+4, etc.
 * Returns 0 if the index doesn't belong to any known group.
 */
int __cdecl gm_GetOppositeStatIndex(int stat_id)
{
	int result;

	result = 0;

	/* Group 1-6 (section A, row 1) */
	if ((stat_id >= 1) && (stat_id <= 6)) {
		return 7 - stat_id;
	}
	/* Group 7-12 (section A, row 2) */
	if ((stat_id >= 7) && (stat_id <= 12)) {
		return 13 - stat_id;
	}
	/* Group 34-39 (section B, row 1) */
	if ((stat_id >= 34) && (stat_id <= 39)) {
		return 40 - stat_id;
	}
	/* Group 40-45 (section B, row 2) */
	if ((stat_id >= 40) && (stat_id <= 45)) {
		return 46 - stat_id;
	}
	/* Group 46-51 (section B, row 3) */
	if ((stat_id >= 46) && (stat_id <= 51)) {
		return 52 - stat_id;
	}
	/* Group 58-63 (section B, row 5) */
	if ((stat_id >= 58) && (stat_id <= 63)) {
		return 64 - stat_id;
	}
	/* Group 64-69 (section B, row 6) */
	if ((stat_id >= 64) && (stat_id <= 69)) {
		return 70 - stat_id;
	}
	/* Group 70-75 (section B, row 7) */
	if ((stat_id >= 70) && (stat_id <= 75)) {
		return 76 - stat_id;
	}
	/* Group 13-18 (section A, row 3) */
	if ((stat_id >= 13) && (stat_id <= 18)) {
		return 19 - stat_id;
	}
	/* Group 52-57 (section B, row 4) */
	if ((stat_id >= 52) && (stat_id <= 57)) {
		return 58 - stat_id;
	}
	/* Group 25-30 (section A, row 5) */
	if ((stat_id >= 25) && (stat_id <= 30)) {
		return 31 - stat_id;
	}
	/* Group 19-24 (section A, row 4) */
	if ((stat_id >= 19) && (stat_id <= 24)) {
		return 25 - stat_id;
	}
	/* Group 76-81 (section C, row 1) */
	if ((stat_id >= 76) && (stat_id <= 81)) {
		return 82 - stat_id;
	}
	/* Group 89-94 (section C, row 3) */
	if ((stat_id >= 89) && (stat_id <= 94)) {
		return 95 - stat_id;
	}
	/* Group 83-88 (section C, row 2) */
	if ((stat_id >= 83) && (stat_id <= 88)) {
		result = 89 - stat_id;
	}
	return result;
}

/* Client-only: blends two weights 60/40 both ways and averages (discarded). */
float __cdecl gm_BlendWeights(float a, float b)
{
	return (((a - b * b) * 0.6f + 0.4f) + ((a * a - b) * 0.4f + 0.6f)) * 0.5f;
}

/* Client-only (TL 0x508220, discarded): copies the 12-byte record of kind (0..9) from the table at
 * g_spiel_const_table + 8, record 0 and result 0 for kind 10 and above. The client's copy of the table
 * (0x696540..0x6965d8) holds the same 152 bytes; the server keeps it unreferenced in spiel_data.c. */
typedef struct {
	unsigned int v[3];
} KIND_REC;

int __cdecl gm_GetKindRecord(int kind, KIND_REC* out)
{
	extern unsigned int g_spiel_const_table[38];

	if (kind >= 10) {
		*out = ((KIND_REC*) (g_spiel_const_table + 8))[0];
		return 0;
	}
	*out = ((KIND_REC*) (g_spiel_const_table + 8))[kind];
	return 1;
}

/* Client-only (TL 0x508c30, discarded): fills arr with 0..n-1 and swaps n/2 + max(n/4, 1) random
 * distinct pairs. */
void __cdecl gm_ShuffleBytes(unsigned char n, unsigned char* arr)
{
	unsigned char i;
	int k;
	unsigned char cnt;
	unsigned char a;
	unsigned char b;
	unsigned char t;

	for (i = 0; i < n; i++) {
		arr[i] = i;
	}
	if (n < 2) {
		return;
	}
	k = n / 4 > 1 ? n / 4 : 1;
	i = 0;
	cnt = n / 2 + k;
	while (i < cnt) {
		a = (unsigned char) gm_RandomMod(n);
		b = (unsigned char) gm_RandomMod(n);
		if (a != b) {
			t = arr[a];
			arr[a] = arr[b];
			arr[b] = t;
			i++;
		}
	}
}

/* Generates a random stat modifier. Produces a random
 * delta value for stat variation during entity creation
 * or level-up events. */

//   PROVEN (msvc6: float-cast compare with fcomp [const], shared ternary call)

char __cdecl gm_RandomStatModifier(char stat_value)
{
	char result;

	/* The volatile byte read keeps the parameter's low byte in bl; the mask
	 * below then reloads the full dword and homes it in the parameter slot,
	 * which is what fild reads. A plain read lets msvc6 fold both into one
	 * dword load. */
	result = *(volatile char*) &stat_value;
	if (result == 0) {
		result = (char) (gm_RandomMod(0x2a) + 0x15);
	} else {
		result += (char) gm_RandomMod(
		    (float) (*(int*) &stat_value & 0xff) >= g_const_42_0 ? 0xb : 6);
	}
	return result;
}

/* Looks up an entity record by its integer ID. Searches
 * the global entity table and returns a pointer to the
 * matching entity, or 0 if not found. */

int __cdecl gm_LookupEntityRecordById(int search_id)
{
	char* base_cursor;
	int i;
	i = 0;
	base_cursor = (char*) &g_entity_id_field;
	while ((int) base_cursor < (int) ((char*) &g_entity_id_field + 0x65400)) {
		if (*(unsigned short*) (base_cursor - 4) != 0xFFFF) {
			if (*(int*) base_cursor == search_id) {
				return i * 0x21C + (int) g_slot_table;
			}
		}
		base_cursor += 0x21C;
		i++;
	}
	return 0;
}

/* Client-only age, rank and family helpers (discarded). */

float __cdecl gm_GetEntityAge(int slot)
{
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetEntityAge(): enter", 1);
	return (float) *(unsigned short*) (g_slot_table + 0xa + (slot & 0xffff) * 0x21c);
}

int __cdecl gm_GetOfficeRank(unsigned short slot, int skip_parent)
{
	int __cdecl amt_GetRoleTemplate(int role, void* out);
	int tmpl[6];
	unsigned short* parent;
	int rank;
	int up;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetOfficeRank(): enter", 1);
	if (*(int*) (g_slot_table + 4 + slot * 0x21c) == -1 || g_slot_table[8 + slot * 0x21c] == 0) {
		return 0;
	}
	if (amt_GetRoleTemplate(g_slot_table[0x166 + slot * 0x21c], tmpl) == 0) {
		return 1;
	}
	rank = (tmpl[2] & 0xff) + 1;
	if ((char) tmpl[2] == 10 || skip_parent != 0) {
		return rank;
	}
	parent = (unsigned short*) gm_LookupEntityRecordById(*(int*) (g_slot_table + 0x60 + slot * 0x21c));
	if (parent == 0) {
		return rank;
	}
	up = gm_GetOfficeRank(*parent, 1);
	if (rank > up) {
		return rank;
	}
	return gm_GetOfficeRank(*parent, 1);
}

int __cdecl gm_GetCouncilRank(unsigned short slot, int skip_parent)
{
	int __cdecl amt_GetRoleTemplate(int role, void* out);
	int tmpl[6];
	unsigned short* parent;
	int rank;
	int up;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetCouncilRank(): enter", 1);
	if (*(int*) (g_slot_table + 4 + slot * 0x21c) == -1 || g_slot_table[8 + slot * 0x21c] == 0) {
		return 0;
	}
	if (amt_GetRoleTemplate(g_slot_table[0x167 + slot * 0x21c], tmpl) == 0) {
		return 1;
	}
	rank = (tmpl[2] & 0xff) + 1;
	if ((char) tmpl[2] == 10 || skip_parent != 0) {
		return rank;
	}
	parent = (unsigned short*) gm_LookupEntityRecordById(*(int*) (g_slot_table + 0x60 + slot * 0x21c));
	if (parent == 0) {
		return rank;
	}
	up = gm_GetCouncilRank(*parent, 1);
	if (rank > up) {
		return rank;
	}
	return gm_GetCouncilRank(*parent, 1);
}

#pragma pack(push, 1)
typedef struct {
	unsigned char day;
	unsigned char month;
	short year;
	int time;
	short rest;
} PACKED_TIME;
#pragma pack(pop)

/* Client-only (TL 0x509050, discarded): a packed date for an entity, from its age record (+0x28, or
 * the current year once +8 is set) less its +0xa word, with day and month drawn from its +0x30 seed. */
void __cdecl gm_GetEntityDate(char* entity, PACKED_TIME* out)
{
	void __cdecl gm_PackGameTime(int* src, char* dst);
	struct blk14 time;
	PACKED_TIME packed;
	unsigned int seed;
	int year;

	time = *(struct blk14*) &g_current_year;
	year = time.a;
	if (entity[8] == 0) {
		year = *(short*) (entity + 0x28);
	}
	year -= *(unsigned short*) (entity + 0xa);
	time.a = year;
	gm_PackGameTime(&time.a, (char*) &packed);
	seed = *(unsigned int*) (entity + 0x30) ^ packed.year;
	packed.month = (unsigned char) (((seed >> 3) % 13 + year % 11) % 12 + 1);
	packed.day = (unsigned char) ((seed >> 5) % 28 + 1);
	*out = packed;
}

int __cdecl gm_GetBirthday(char* entity, unsigned char* out)
{
	void __cdecl gm_PackGameTime(int* src, char* dst);
	int time[4];
	char packed[12];
	unsigned int seed;
	int age;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetBirthday(): enter", 1);
	if (entity[8] != 0) {
		return 0;
	}
	age = *(short*) (entity + 0x28);
	time[0] = age;
	gm_PackGameTime(time, packed);
	seed = *(unsigned int*) (entity + 0x30) ^ *(short*) (packed + 2);
	out[1] = (unsigned char) (((seed >> 3) % 7 + age % 19) % 12 + 1);
	out[0] = (unsigned char) ((seed >> 5) % 28 + 1);
	*(short*) (out + 2) = *(short*) (packed + 2);
	return 1;
}

int __cdecl gm_CanMarry(char* a, char* b)
{
	int __cdecl sim_IsUnderage(int slot);
	char* other;
	int age_diff;
	int i;
	int first;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_CanMarry(): enter", 1);
	age_diff = (unsigned char) b[0x58] - (unsigned char) a[0x58];
	if (b[8] == 0) {
		return 0;
	}
	for (i = 0; i < 8; i++) {
		if (*(int*) (a + 0x5c + i * 4) == *(int*) (b + 4)) {
			break;
		}
	}
	if (i < 8) {
		if (i == 1 || i == 2) {
			return 0;
		}
		if (i != 0) {
			return sim_IsUnderage(*(unsigned short*) b) == 0;
		}
		first = 2;
	}
	else {
		if (age_diff != 0 || *(unsigned short*) (a + 0x50) != *(unsigned short*) (b + 0x50)) {
			return 0;
		}
		first = 3;
	}
	for (i = 3; i < 8; i++) {
		if (*(int*) (a + 0x5c + i * 4) == -1) {
			continue;
		}
		other = (char*) gm_LookupEntityRecordById(*(int*) (a + 0x5c + i * 4));
		if (other != 0 && sim_IsUnderage(*(unsigned short*) other) == 0 && other[8] != 0) {
			return 0;
		}
	}
	if (first > 2) {
		other = (char*) gm_LookupEntityRecordById(*(int*) (a + 0x5c));
		if (other != 0 && other[8] != 0) {
			return 0;
		}
	}
	return 1;
}

/* Resolves a flagged kind 5, 6 or 7 entity to a table entry.
 * The low four bits at offset 0x50 select a 172-byte record. */


short* __cdecl gm_GetEntityTableEntry(char* param)
{
	char type;
	int table_index;

	type = param[2];
	if (type == 6 || type == 7 || type == 5) {
		if ((*(unsigned short*) (param + 0x50) & 0x8000) != 0) {
			table_index = *(unsigned short*) (param + 0x50) & 0xf;
			if (table_index >= 0 && table_index < 0x10) {
			}
			if (table_index >= 0 && table_index < 0x10) {
				return (short*) (&g_entity_base[table_index * 0xac]);
			}
		}
	}
	return (short*) 0;
}

/* Client-only: number of living children; non-zero when one is of age
 * (discarded). */
int __cdecl gm_CountChildren(char* entity, int* count_out)
{
	char* child;
	int adult;
	int count;
	int i;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_CountChildren(): enter", 1);
	adult = 0;
	count = 0;
	for (i = 0; i < 5; i++) {
		child = (char*) gm_LookupEntityRecordById(*(int*) (entity + 0x68 + i * 4));
		if (child != 0 && *(unsigned char*) (child + 8) > 0) {
			count++;
			if (*(unsigned short*) (child + 0xa) > 0xb) {
				adult = 1;
			}
		}
	}
	if (count_out != 0) {
		*count_out = count;
	}
	return adult;
}

int __cdecl gm_ChangePlayerIdentityImpl(int from_id, int to_id, int unused)
{
	int counter;
	int owner;
	unsigned short to_slot;
	unsigned short chain;
	int link;
	char rec_a[0x21c];
	char rec_b[0x21c];
	char* from_ent;
	char* to_ent;
	char* ent;
	char* stat_ent;
	char* obj;
	char* dst;
	int i;
	int level;
	int range;
	unsigned short obj_type;

	(void) unused;

	from_ent = (char*) gm_LookupEntityRecordById(from_id);
	if (from_ent == NULL) {
		return -1;
	}

	i = 0;
	counter = 0x100;
	do {
		ent = (char*) g_entity_ptr + i * 0xa9;
		if (*ent != 0) {
			if (gm_GetBuildingTypeCategory(*ent & 0xff) == 2) {
				if (*(unsigned short*) (ent + 0x27) == *(unsigned short*) from_ent) {
					owner = *g_entity_table_end;
					gm_AssignBuildingOwner(ent, owner, owner);
				}
			}
		}
		i++;
		counter--;
	} while (counter != 0);

	chain = *(unsigned short*) from_ent;
	link = gm_WalkEntityChain(chain);
	to_ent = (char*) gm_LookupEntityRecordById(to_id);
	if (to_ent == NULL) {
		return -2;
	}
	to_slot = *(unsigned short*) to_ent;
	if (*(unsigned short*) (from_ent + 0x50) != *(unsigned short*) (to_ent + 0x50)) {
		*(unsigned short*) (to_ent + 0x50) = *(unsigned short*) (from_ent + 0x50);
	}
	amt_ClearEntityLinks(from_ent);

	memcpy(rec_a, to_ent, 0x21c);
	*(int*) (rec_a + 4) = *(int*) (from_ent + 4);
	*(unsigned short*) rec_a = *(unsigned short*) from_ent;
	rec_a[2] = from_ent[2];
	rec_a[0xd] = from_ent[0xd];
	*(int*) (rec_a + 0x170) = *(int*) (from_ent + 0x170);

	range = gm_MapEntityStatRange(to_ent[0x164] & 0xff);
	if (range != 0) {
		stat_ent = gm_GetEntityTableEntry(from_ent);
		if (stat_ent != NULL) {
			level = gm_CheckStatLevel(*(unsigned short*) from_ent, range);
			if (level != 0) {
				if (gm_GetOppositeStatIndex(level) <
					gm_GetOppositeStatIndex(to_ent[0x164] & 0xff)) {
					stat_ent[range + 0x74] = to_ent[0x164];
				} else {
					rec_a[0x164] = from_ent[0x164];
				}
			}
		}
	} else {
		rec_a[0x164] = from_ent[0x164];
	}

	memcpy(rec_b, from_ent, 0x21c);
	*(int*) (rec_b + 4) = *(int*) (to_ent + 4);
	*(unsigned short*) rec_b = *(unsigned short*) to_ent;
	rec_b[2] = 9;

	memcpy((char*) &g_slot_table + chain * 0x21c, rec_a, 0x21c);
	memcpy((char*) &g_slot_table + to_slot * 0x21c, rec_b, 0x21c);

	obj = *(char**) ((char*) g_slot_table + 0x178 + chain * 0x21c);
	while (obj != NULL) {
		*(int*) (obj + 6) = *(int*) ((char*) &g_entity_id_field + chain * 0x21c);
		obj = *(char**) (obj + 0x3f);
	}
	obj = *(char**) ((char*) g_slot_table + 0x178 + to_slot * 0x21c);
	while (obj != NULL) {
		*(int*) (obj + 6) = *(int*) ((char*) &g_entity_id_field + to_slot * 0x21c);
		obj = *(char**) (obj + 0x3f);
	}

	dst = (char*) &g_entity_ref_table;
	counter = 0x300;
	do {
		ent = dst;
		level = 8;
		do {
			if (*(int*) ent == from_id) {
				*(int*) ent = to_id;
			} else if (*(int*) ent == to_id) {
				*(int*) ent = from_id;
			}
			ent += 4;
			level--;
		} while (level != 0);
		dst += 0x21c;
		counter--;
	} while (counter != 0);

	obj = *(char**) (rec_b + 0x178);
	while (obj != NULL) {
		obj_type = *(unsigned short*) obj;
		if (obj_type != 0) {
			if (g_item_def_table[(obj_type << 6) + obj_type] == 9) {
				gm_AddObjekt(*(int*) (rec_a + 4), obj_type,
					*(int*) (obj + 0xe));
			}
		}
		obj = *(char**) (obj + 0x3f);
	}

	*(int*) ((char*) g_slot_table + 0x1a8 + chain * 0x21c) = link;
	*(int*) ((char*) g_slot_table + 0x194 + chain * 0x21c) = 4;
	*(int*) ((char*) g_slot_table + 0x1c8 + chain * 0x21c) = 0;
	gm_KillSpieler(*(unsigned short*) rec_b, 0);

	return chain;
}

/* 0x10035430 */

#pragma intrinsic(memcpy, memset, strlen, strcpy)
unsigned short __cdecl gm_AllocSpieler(int type, int mother_id, int father_id, int arg4, int location, int arg6, int arg7, int arg8)
{
	char* slot; extern const float g_player_trait_ranges[];
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
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x2614,
		                   "gm_AllocSpieler: array overflow...", 1);
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
	sprintf(work, "----->SpID= %i playermode= %i", g_next_object_id, type);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x2637, work, 8);
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
			    (float) ((float) gm_RandomFloat01() * 0.5f) +
			    g_const_0_25;
			n = g_next_family_index;
			*(int*) (slot + 0x1c) = 0x447a0000; /* 1000.0f */
			*(unsigned short*) (slot + 0x50) = (unsigned short) n;
			g_next_family_index = n + 1;
			blend = gm_RandomQuadratic() * 7.0f;
			*(int*) (slot + 0x20) = 0x41400000; /* 12.0f */
			*(float*) (slot + 0x14) = (float) blend + 30.0f;
			*(float*) (slot + 0x10) =
			    (float) ((double) (*(float*) (slot + 0x1c) * 0.33f) +
			             (double) (unsigned short) gm_RandomMod((unsigned short) (int) (*(float*) (slot + 0x1c) *
			                                            g_const_0_2)) -
			             (double) (*(float*) (slot + 0x1c) * 0.1f));
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
				if (acc <= 1.0f) {
					acc = 1.0f;
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
		src = (float*) ((int) g_player_trait_ranges + n * 0x70);
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
		    (float) ((float) gm_RandomFloat01() * 0.5f) +
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
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x27f0,
				                   "gm_AllocSpieler(): gm_CurrentHumanFamilyCount overflow", 1);
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
		    (float) (gm_RandomQuadratic() * 7.0f) +
		    30.0f;
		*(int*) (slot + 0x20) = 0x41400000; /* 12.0f */
		*(float*) (slot + 0x10) =
		    (float) ((double) (*(float*) (slot + 0x1c) * 0.33f) +
		             (double) (unsigned short) gm_RandomMod((unsigned short) (int) (*(float*) (slot + 0x1c) *
		                                            g_const_0_2)) -
		             (double) (*(float*) (slot + 0x1c) * 0.1f));
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
		    (float) ((float) (1.0 - rnd01) *
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
			    (double) (*(unsigned char*) (father + 0x80 + i) *
			    0.5f));
		} else if (i == best_mother) {
			slot[0x80 + i] = (char) (
			    (double) (*(unsigned char*) (mother + 0x80 + i) *
			    0.5f));
		} else {
			/* The father byte goes through an int with a memory home, which
			 * is what makes msvc6 emit fimul (shapes 82); without the
			 * (double) casts the mother term compiles to fild + fmul [weight]
			 * and all three arms share the reference's tail fmul (0x10018f5e). */
			*trait_home = *(unsigned char*) (father + 0x80 + i);
			slot[0x80 + i] = (char) ((float) ((1.0 - weight) * trait_byte +
			                          *(unsigned char*) (mother + 0x80 + i) * weight) *
			                         0.5f);
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
	    (float) ((gm_RandomQuadratic() * 7.0f +
	              30.0f) *
	                 g_const_0_6 +
	             (*(float*) (father + 0x14) + *(float*) (mother + 0x14)) *
	                 g_const_0_2);
	*(int*) (slot + 0x20) = 0x41400000; /* 12.0f */
	*(float*) (slot + 0x10) =
	    (float) ((double) (*(float*) (slot + 0x1c) * 0.33f) +
	             (double) (unsigned short) gm_RandomMod((unsigned short) (int) (*(float*) (slot + 0x1c) *
	                                            g_const_0_2)) -
	             (double) (*(float*) (slot + 0x1c) * 0.1f));
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
		if (decay <= 1.0f) {
			decay = 1.0f;
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
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x286c, "gm_AllocSpieler: bug",
		                   1);
	}
	sprintf(work, "----->PlayerID= %i PlayerName= %s", g_next_object_id, slot + 0x30);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x2888, work, 8);
	return idx;
}

/* Client-only unit conversions (TL 0x50b710, 0x50b750, 0x50b780, 0x50b7a0; discarded). An item's
 * amount per trade unit is g_spiel_space_fill[id - 61], 16 entries of 32 for item ids 61..76; the
 * client addresses the table as 0x6995bc, 61 dwords below it, and nothing else reads it. */

int __cdecl gm_AmountToUnits(int amount, unsigned char type)
{
	extern int g_spiel_space_fill[16];

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_AmountToUnits(): enter", 1);
	return (int) ((float) amount / g_spiel_space_fill[*(unsigned short*) &g_entity_slot_table[type * 189] - 61] + 0.5);
}

int __cdecl gm_UnitsToAmount(int units, unsigned char type)
{
	extern int g_spiel_space_fill[16];

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_UnitsToAmount(): enter", 1);
	return units * g_spiel_space_fill[*(unsigned short*) &g_entity_slot_table[type * 189] - 61];
}

int __cdecl gm_UnitsToAmountById(int units, int id)
{
	extern int g_spiel_space_fill[16];

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_UnitsToAmountById(): enter", 1);
	return units * g_spiel_space_fill[id - 61];
}

int __cdecl gm_AmountToUnitsById(int amount, int id)
{
	extern int g_spiel_space_fill[16];

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_AmountToUnitsById(): enter", 1);
	return amount / g_spiel_space_fill[id - 61];
}

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

/* Client-only store and manufacturer queries (discarded). */

int __cdecl gm_SumStoreCount(int store)
{
	void* entry;
	int total;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_SumStoreCount(): enter", 1);
	total = 0;
	entry = gm_ff_Objekt(store, 1, 4, 9);
	while (entry != 0) {
		total = total + *(int*) ((char*) entry + 0xe);
		entry = gm_NextEntityQueryMatch();
	}
	return total;
}

float __cdecl gm_GetManufacturerRating(int item)
{
	extern char g_minimum_manufacturer[];
	unsigned char* type;
	char* def;
	float sum;
	int i;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetManufacturerRating(): enter", 1);
	sum = g_const_0_0;
	type = (unsigned char*) g_entity_type_table + ((int*) g_minimum_manufacturer)[item] * 0x24d;
	for (i = 0; i < 2; i++) {
		sum += type[0x233 + i] * 896.0f * (1.0 / 720.0);
	}
	def = g_item_def_table + item * 0x41;
	return sum * *(int*) (def + 0x22) / (int) *(unsigned short*) (def + 0x36);
}

#pragma optimize("a", on)
double __cdecl eval_ObjektPreis2Credits(int entity_index, int param2)
{
	char* entity; extern char g_minimum_manufacturer[];
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
	min_val = *(int*) (entity_index * 4 + (int) g_minimum_manufacturer);
	record = g_entity_type_table + min_val * 0x24d;
	if (min_val != 0) {
		mod_value = g_const_0_0;
		for (i = 0; i < 2; i++) {
			weight = *(unsigned char*) (record + i + 0x233);
			mod_value = (float) ((double) weight * g_const_896_0 * g_const_1_over_720 + mod_value);
		}
	} else {
		mod_value = 4.0f;
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
			*sub = eval_ObjektPreis2Credits(comp, param2);
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

/* Client-only (TL 0x50bb50, discarded): the season's price of item id from the season's 0x55-entry
 * table in g_slot_array (gm_FindSlotById's records), else its production value. */
float __cdecl gm_GetSeasonPrice(int id, unsigned char season)
{
	int i;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetSeasonPrice(): enter", 1);
	for (i = 0; i < 0x55; i++) {
		if (*(unsigned short*) ((char*) &g_slot_array + season * 0x2a90 + i * 0x80) == id) {
			return *(float*) ((char*) &g_slot_array + 0x38 + season * 0x2a90 + i * 0x80);
		}
	}
	return eval_ObjektPreis2Credits(id, 100);
}

/* Client-only mood, store and building-level helpers (discarded). */

float __cdecl gm_GetHappinessFactor(int slot)
{
	unsigned char* e;
	float v;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetHappinessFactor(): enter", 1);
	e = g_slot_table + slot * 0x21c;
	if (e == 0) {
		return 1.0f;
	}
	v = e[0x80];
	if (v <= g_const_42_0) {
		return 1.0f;
	}
	return (float) (v * (1.0 / 1008.0) + 1.0);
}

/* Client-only (TL 0x50bc10, discarded): formats amount of item type in trade units as
 * "[-]1.234.567<0x11>", grouping thousands with dots. The client calls _itoa; itoa is its old name,
 * which OLDNAMES resolves after xtoa.obj loads for getqloc.obj. */
void __cdecl gm_FormatPrice(int amount, unsigned char type, char* out)
{
	char digits[0x40];
	char text[0x80];
	int units;
	int len;
	int k;
	int i;
	char* p;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_FormatPrice(): enter", 1);
	units = gm_AmountToUnits(abs(amount), type);
	if (amount < 0) {
		if (units != 0) {
			if (units >= 1000) {
				itoa(units, digits, 10);
				k = -1;
				len = (int) ((strlen(digits) - 1) * (1.0f / 3) + strlen(digits));
				i = strlen(digits);
				if (i >= 0) {
					p = text + len;
					do {
						*p-- = digits[i];
						if (i != 0 && k > 0 && (k + 1) % 3 == 0) {
							*p-- = '.';
						}
						k++;
					} while (--i >= 0);
				}
				text[len] = 0;
				sprintf(out, "-%s%c", text, 0x11);
				return;
			}
			sprintf(out, "-%i%c", units, 0x11);
			return;
		}
	} else {
		if (units >= 1000) {
			itoa(units, digits, 10);
			k = -1;
			len = (int) ((strlen(digits) - 1) * (1.0f / 3) + strlen(digits));
			i = strlen(digits);
			if (i >= 0) {
				p = text + len;
				do {
					*p-- = digits[i];
					if (i != 0 && k > 0 && (k + 1) % 3 == 0) {
						*p-- = '.';
					}
					k++;
				} while (--i >= 0);
			}
			text[len] = 0;
			sprintf(out, "%s%c", text, 0x11);
			return;
		}
		if (units != 0) {
			sprintf(out, "%i%c", units, 0x11);
			return;
		}
	}
	sprintf(out, "0%c", 0x11);
}

int __cdecl gm_ListBuildingStores(unsigned char* building, void** out)
{
	unsigned short* slot;
	void* store;
	int n;
	int i;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_ListBuildingStores(): enter", 1);
	n = 0;
	slot = (unsigned short*) ((unsigned char*) g_entity_type_table + building[0] * 0x24d + 0x23);
	for (i = 0; i < 0x40 && *slot != 0; i++, slot++) {
		store = gm_ff_Objekt(*(int*) (building + 0x5d), 2, 6, 0, *slot & 0x7fff);
		if (store != 0) {
			out[n++] = store;
		}
	}
	return n;
}

int __cdecl gm_ListProducts(unsigned char* building, int* out)
{
	unsigned char* type;
	int n;
	int i;
	int item;

	n = 0;
	type = (unsigned char*) g_entity_type_table + *building * 0x24d;
	for (i = 0; i < 0x40; i++) {
		if (*(unsigned short*) (type + 0x23 + i * 2) == 0) {
			break;
		}
		item = *(unsigned short*) (type + 0x23 + i * 2) & 0x7fff;
		if (g_item_def_table[item * 0x41] != 0x21) {
			n++;
		}
		if (out != 0) {
			out[n] = item;
		}
	}
	return n;
}

int __cdecl gm_ListProductsAfter(unsigned char* building, unsigned short* key, int* out)
{
	unsigned char* type;
	char kind;
	int n;
	int i;
	int item;

	n = 0;
	type = (unsigned char*) g_entity_type_table + *building * 0x24d;
	for (i = 0; i < type[0x22]; i++) {
		if ((unsigned short) (*(unsigned short*) (type + 0x23 + i * 2) & 0x7fff) == *key) {
			break;
		}
	}
	if (i >= type[0x22]) {
		return 0;
	}
	for (i++; i < 0x40; i++) {
		if (*(unsigned short*) (type + 0x23 + i * 2) == 0) {
			break;
		}
		item = *(unsigned short*) (type + 0x23 + i * 2) & 0x7fff;
		kind = g_item_def_table[item * 0x41];
		if (kind == 2 || kind == 6) {
			break;
		}
		if (kind != 0x21) {
			n++;
		}
		if (out != 0) {
			out[n] = item;
		}
	}
	return n;
}

int __cdecl gm_GetEntityMood(char* entity)
{
	return (signed char) entity[0x5c];
}

int __cdecl gm_ListGuildHouses(char* player, void** out)
{
	char* house;
	int n;

	n = 0;
	house = (char*) gm_ff_Objekt(n, 2, 7, 4, 0x1d);
	while (house != 0 && n < 3) {
		if (*(int*) (house + 0x1c) == *(int*) (player + 1)) {
			if (out != 0) {
				out[n] = house;
			}
			n++;
		}
		house = (char*) gm_NextEntityQueryMatch();
	}
	return n;
}

int __cdecl gm_GetBuildingLevel(unsigned char* building)
{
	unsigned char* type;

	type = (unsigned char*) g_entity_type_table + building[0] * 0x24d;
	switch (type[0]) {
	case 2:
	case 5:
	case 7:
		return type[0x247];
	case 4:
	case 11:
	case 12:
	case 13:
	case 16:
		break;
	}
	return type[0x247];
}

int __cdecl gm_HasLevelFor(unsigned char* building, unsigned char* other)
{
	unsigned char* type;
	int need;
	int level;

	type = (unsigned char*) g_entity_type_table + building[0] * 0x24d;
	level = 0;
	need = gm_GetBuildingLevel(other);
	if (type[0x247] == 1) {
		level = 1;
	}
	else if (type[0x247] == 2) {
		level = 2;
	}
	else if (type[0x247] == 3) {
		level = 7;
	}
	return level >= need;
}

/* Client-only (TL 0x50c5d0, discarded): out[0] is a building's chain value (gm_WalkEntityChain of its
 * +0x27 link, capped at 2048000) times 0.07 for type kind 2 or 0.03 otherwise, at least 0; out[1] sums
 * the production value of each item in its market store (0x2a) times 0.3 of its count, at least 1. */
int __cdecl gm_GetBuildingWorth(unsigned char* building, int* out)
{
	unsigned char* type;
	float v;
	float sum;
	char* store;
	unsigned short* e;
	int c;

	type = (unsigned char*) g_entity_type_table + building[0] * 0x24d;
	v = g_const_0_0;
	if (*(unsigned short*) (building + 0x27) != 0xffff) {
		v = (float) gm_WalkEntityChain(*(unsigned short*) (building + 0x27));
		if (2048000.0f < v) {
			v = 2048000.0f;
		}
	}
	if (*type == 2) {
		v *= 0.07f;
	}
	else {
		v *= 0.03f;
	}
	if (g_const_0_0 > v) {
		v = g_const_0_0;
	}
	out[0] = (int) v;
	sum = 0;
	store = (char*) gm_ff_Objekt(*(int*) (building + 0x5d), 2, 6, 0, 0x2a);
	if (store != 0) {
		for (e = gm_ff_Objekt(*(int*) (store + 0x14), 1, 5); e != 0; e = (unsigned short*) gm_NextEntityQueryMatch()) {
			c = (int) (gm_GetMsgField(store, (char*) e) * 0.3);
			if (c < 1) {
				c = 1;
			}
			sum += (float) eval_ObjektPreis2Credits(*e, 100) * c;
		}
	}
	out[1] = (int) sum;
	return 0;
}

int __cdecl gm_SumProductPoints(unsigned char* building, int kind, int scaled)
{
	unsigned char* type;
	int sum;
	int i;
	int item;

	sum = 0;
	type = (unsigned char*) g_entity_type_table + building[0] * 0x24d;
	for (i = 0; i < 0x40; i++) {
		item = *(unsigned short*) (type + 0x23 + i * 2) & 0x7fff;
		if (item != 0 && type[0x1a3 + i] == kind && gm_ff_Objekt(*(int*) (building + 0x5d), 2, 6, 0, item) != 0) {
			sum += type[0x1e3 + i];
		}
	}
	if (scaled) {
		return (int) (sum * (gm_GetEntityMood((char*) building) * 0.01) + 0.5);
	}
	return sum;
}

int __cdecl gm_SumTypePoints(int type_index, int kind)
{
	unsigned char* type;
	int sum;
	int i;

	sum = 0;
	type = (unsigned char*) g_entity_type_table + type_index * 0x24d;
	for (i = 0; i < 0x40; i++) {
		if ((*(unsigned short*) (type + 0x23 + i * 2) & 0x7fff) != 0 && type[0x1a3 + i] == kind) {
			sum += type[0x1e3 + i];
		}
	}
	return sum;
}

int __cdecl gm_DaytimeMinutesBetween(char* from, char* to)
{
	int __cdecl gm_CompareGameTime(char* a, char* b);
	void __cdecl sim_SetSyncParams(void* target, unsigned char type_id, unsigned int field_6, unsigned int field_10);
	char cur[14];
	float m;
	int total;
	int days;

	if (gm_CompareGameTime(from, to) > 0) {
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_DaytimeMinutesBetween(): from is later than to", 1);
		return 0;
	}
	*(int*) cur = *(int*) from;
	*(int*) (cur + 4) = *(int*) (from + 4);
	*(int*) (cur + 8) = *(int*) (from + 8);
	*(short*) (cur + 0xc) = *(short*) (from + 0xc);
	if (*(int*) cur < *(int*) to) {
		m = (float) (*(unsigned short*) (cur + 4) * 60 + *(int*) (cur + 6));
		m = m < 360.0f ? 360.0f : (m > 1380.0f ? 1380.0f : m);
		total = (int) (1380.0f - (int) m);
		(*(int*) cur)++;
		sim_SetSyncParams(cur, 6, 0, 0);
	}
	else {
		total = 0;
	}
	for (days = *(int*) to - *(int*) cur; days > 0; days--) {
		total = (int) (total + 1020.0f);
	}
	m = (float) (*(unsigned short*) (to + 4) * 60 + *(int*) (to + 6));
	m = m < 360.0f ? 360.0f : (m > 1380.0f ? 1380.0f : m);
	total += (int) m;
	m = (float) (*(unsigned short*) (cur + 4) * 60 + *(int*) (cur + 6));
	m = m < 360.0f ? 360.0f : (m > 1380.0f ? 1380.0f : m);
	return total - (int) m;
}

/* Client-only: a building's stock (its market or tavern store, the items it
 * holds, their counts and capacities) for producers or consumers
 * (discarded). */

int __cdecl gm_GetBuildingStock(char* building, void* stock, int producers)
{
	typedef struct {
		int max;
		int n;
		int caps[16];
		unsigned short ids[16];
		int vals[16];
		char pada8[0xb4 - 0xa8];
		char* store;
	} STOCK;
	STOCK* out;
	char* store;
	unsigned short* e;
	char* def;

	out = (STOCK*) stock;
	memset(out, 0, sizeof(STOCK));
	if (gm_ff_Objekt(*(int*) (building + 0x5d), 1, 0, 0xfd) == 0) {
		return 0;
	}
	store = (char*) gm_ff_Objekt(*(int*) (building + 0x5d), 2, 6, 0, 0x2a);
	if (store == 0) {
		store = (char*) gm_ff_Objekt(*(int*) (building + 0x5d), 2, 6, 0, 0x116);
		if (store == 0) {
			/* placeholder: inferred server log call, see msvc6-link-layout 5f */
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetBuildingStock(): no store", 1);
			return 0;
		}
	}
	if (producers) {
		if (*(unsigned short*) store == 0x116) {
			return 0;
		}
		out->max = (unsigned char) store[0x1c];
	}
	else {
		out->max = (unsigned char) store[0x1d];
		if (*(unsigned short*) store == 0x116 && (unsigned char) store[0x1c] > out->max) {
			out->max = (unsigned char) store[0x1c];
		}
	}
	for (e = gm_ff_Objekt(*(int*) (store + 0x14), 1, 5); e != 0; e = (unsigned short*) gm_NextEntityQueryMatch()) {
		def = g_item_def_table + *e * 0x41;
		if (((*def == 0x17 || *def == 0x25) && producers) || (*def != 0x17 && *def != 0x25 && !producers) ||
		    *(unsigned short*) store == 0x116) {
			out->vals[out->n] = gm_GetMsgField(store, (char*) e);
			out->caps[out->n] = compute_size(store, *e);
			out->ids[out->n] = *e;
			out->n++;
		}
	}
	out->store = store;
	return 1;
}

int __cdecl gm_GetBuildingFoodStock(char* building, void* stock, int producers)
{
	typedef struct {
		int max;
		int n;
		int caps[16];
		unsigned short ids[16];
		int vals[16];
		char pada8[0xb4 - 0xa8];
		char* store;
	} STOCK;
	STOCK* out;
	char* store;
	unsigned short* e;
	char* def;

	out = (STOCK*) stock;
	memset(out, 0, sizeof(STOCK));
	if (gm_ff_Objekt(*(int*) (building + 0x5d), 1, 0, 0xfd) == 0) {
		return 0;
	}
	store = (char*) gm_ff_Objekt(*(int*) (building + 0x5d), 2, 6, 0, 0x2a);
	if (store == 0) {
		store = (char*) gm_ff_Objekt(*(int*) (building + 0x5d), 2, 6, 0, 0x116);
		if (store == 0) {
			/* placeholder: inferred server log call, see msvc6-link-layout 5f */
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetBuildingFoodStock(): no store", 1);
			return 0;
		}
	}
	if (producers) {
		if (*(unsigned short*) store == 0x116) {
			return 0;
		}
		out->max = (unsigned char) store[0x1c];
	}
	else {
		out->max = (unsigned char) store[0x1d];
		if (*(unsigned short*) store == 0x116 && (unsigned char) store[0x1c] > out->max) {
			out->max = (unsigned char) store[0x1c];
		}
	}
	for (e = gm_ff_Objekt(*(int*) (store + 0x14), 1, 5); e != 0; e = (unsigned short*) gm_NextEntityQueryMatch()) {
		def = g_item_def_table + *e * 0x41;
		if ((*def == 0x17 && producers) || (*def != 0x17 && !producers)) {
			out->vals[out->n] = gm_GetMsgField(store, (char*) e);
			out->caps[out->n] = compute_size(store, *e);
			out->ids[out->n] = *e;
			out->n++;
		}
	}
	out->store = store;
	return 1;
}

/* Sums production values across all buildings of a type.
 * Aggregates daily/weekly output for economic reporting. */

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
					total = (int) (eval_ObjektPreis2Credits(q_slot, *(unsigned char*) ((char*) query_result + 0x12)) + (double) total);
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
				total = (int) (eval_ObjektPreis2Credits(*sub, *(unsigned char*) ((char*) sub + 0x12)) + (double) total);
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

/* Client-only (TL 0x50d170, discarded): a building type's +0x249 count times 0xf00 plus the production
 * value of each of its products flagged 0x8000. */
int __cdecl gm_GetTypeProductValue(int type_index)
{
	unsigned char* type;
	int total;
	int i;
	unsigned short w;
	char* item;

	type = (unsigned char*) g_entity_type_table + type_index * 0x24d;
	total = *(int*) (type + 0x249) * 0xf00;
	for (i = 0; i < 0x40; i++) {
		w = ((unsigned short*) (type + 0x23))[i];
		if (w == 0) {
			break;
		}
		item = g_item_def_table + (w & 0x7fff) * 0x40 + (w & 0x7fff);
		if (w & 0x8000) {
			total = (int) (eval_ObjektPreis2Credits(*(unsigned char*) item, 100) + total);
		}
	}
	return total;
}

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

/* Client-only treasury sums (discarded). */

int __cdecl gm_SumTreasury(char* entity)
{
	char* r;
	int sum;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_SumTreasury(): enter", 1);
	sum = 0;
	r = (char*) gm_ff_Objekt(*(int*) (entity + 0x178), 1, 4, 9);
	if (r) {
		do {
			sum += *(int*) (r + 0xe);
			r = (char*) gm_NextEntityQueryMatch();
		} while (r);
	}
	return sum;
}

int __cdecl gm_GetSeasonTreasury(char* entity, char season)
{
	char* r;
	int result;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetSeasonTreasury(): enter", 1);
	result = 0;
	r = (char*) gm_ff_Objekt(*(int*) (entity + 0x178), 1, result, (int) (unsigned short) g_entity_slot_table[season * 189]);
	if (r) {
		result = *(int*) (r + 0xe);
	}
	return result;
}

int __cdecl gm_SumSlotTreasury(int slot)
{
	char* owner;
	char* r;
	int sum;

	owner = (char*) gm_LookupEntityRecordById(*(int*) (g_slot_table + 4 + slot * 0x21c));
	if (owner == 0) {
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_SumSlotTreasury(): owner not found", 1);
		return -1;
	}
	sum = 0;
	r = (char*) gm_ff_Objekt(*(int*) (owner + 0x178), 1, 4, 9);
	if (r) {
		do {
			sum += *(int*) (r + 0xe);
			r = (char*) gm_NextEntityQueryMatch();
		} while (r);
	}
	return sum;
}

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
				sum = (int) (eval_ObjektPreis2Credits(*(unsigned short*) query_result, *(unsigned char*) ((char*) query_result + 0x12)) + (double) sum);
				query_result = gm_NextEntityQueryMatch();
			} while (query_result != NULL);
		}
	}
	return sum;
}

/* Client-only: the simulation record behind an entity reference (discarded). */
short* __cdecl gm_ResolveEntityRecord(short* entity)
{
	void* dynamic_ent;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_ResolveEntityRecord(): enter", 1);
	gm_ResolveEntityById(&dynamic_ent, (void**) 0, (void**) &entity, *(int*) (entity + 5));
	if (entity == (short*) 0) {
		if (dynamic_ent != (void*) 0 && *(unsigned short*) ((char*) dynamic_ent + 0x25) != 0xffff) {
			return (short*) (g_slot_table + *(unsigned short*) ((char*) dynamic_ent + 0x25) * 0x21c);
		}
		entity = (short*) 0;
	}
	return entity;
}

/* Resolves the id at input+0x0a to a static record or its dynamic link.
 * A missing record or link index 0xffff returns null. */


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

/* Client-only: the slot index behind an entity reference (discarded). */
unsigned short __cdecl gm_ResolveEntitySlot(short* entity)
{
	void* dynamic_ent;

	gm_ResolveEntityById(&dynamic_ent, (void**) 0, (void**) &entity, *(int*) (entity + 5));
	if (entity != (short*) 0) {
		return *entity;
	}
	if (dynamic_ent != (void*) 0) {
		return *(unsigned short*) ((char*) dynamic_ent + 0x25);
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_ResolveEntitySlot(): entity not found", 1);
	return 0xffff;
}

/* Returns the resolved static record's first word or dynamic+0x27.
 * Returns 0xffff when both resolver outputs are null. */


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


int __cdecl gm_WalkEntityChain(unsigned short raw_idx)
{
	unsigned short idx;
	int slot;
	int ent;
	int total;
	idx = (unsigned short) raw_idx;
	if (idx >= 0x300) {
		return -1;
	}
	slot = (unsigned int) idx * 0x21c + (unsigned int) g_slot_table;
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
	record_cursor = (int) g_slot_table + 2;
	while (record_cursor < (int) g_slot_table + 0x65402) {
		if (*(char*) (record_cursor + 0x162) != 0 && *(int*) (record_cursor + 0x16a) == arg1) {
			if (*(char*) record_cursor == 6 || *(char*) record_cursor == 7 || *(char*) record_cursor == 1 ||
			    *(char*) record_cursor == 2) {
				record = (char*) ((int) g_slot_table + i * 0x21c);
				break;
			}
		}
		record_cursor += 0x21c;
		i++;
	}
	return record;
}

/* Client-only: the tax on a fortune at rate 1-3 (discarded). */
int __cdecl gm_CalcFortuneTax(int fortune, int rate)
{
	int tax;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_CalcFortuneTax(): enter", 1);
	tax = 0;
	if (fortune > g_const_0_0) {
		if (fortune < 32000) {
			fortune = 32000;
		}
		else if (fortune > 256000) {
			fortune = 256000;
		}
	}
	if (rate == 1) {
		tax = (int) (fortune * 0.05f);
	}
	else if (rate == 2) {
		tax = (int) (fortune * 0.1f);
	}
	else if (rate == 3) {
		tax = (int) (fortune * 0.15f);
	}
	return (int) (tax + 0.5);
}

/* Client-only (TL 0x50de80, discarded): a building's workshop store (0x1dd): its +0x1c capacity and per
 * item the count, the stored amount, the id and the summed production value. */
int __cdecl gm_GetWorkshopStock(char* building, void* stock)
{
	typedef struct {
		int max;
		int n;
		int caps[16];
		unsigned short ids[16];
		int vals[16];
		int cap_sum;
		int val_sum;
		int value;
		char* store;
	} STOCK;
	STOCK* out;
	char* store;
	unsigned short* e;

	out = (STOCK*) stock;
	memset(out, 0, sizeof(STOCK));
	store = (char*) gm_ff_Objekt(*(int*) (building + 0x14), 1, 0, 0x1dd);
	if (store == 0) {
		return 0;
	}
	e = gm_ff_Objekt(*(int*) (store + 0x14), 1, 5);
	out->max = (unsigned char) store[0x1c];
	while (e != 0) {
		out->vals[out->n] = *(int*) ((char*) e + 0xe);
		out->caps[out->n] = compute_size(store, *e);
		out->cap_sum += out->caps[out->n];
		out->val_sum += *(int*) ((char*) e + 0xe);
		out->ids[out->n] = *e;
		out->n++;
		out->value = (int) (eval_ObjektPreis2Credits(*e, 100) * *(int*) ((char*) e + 0xe) + out->value);
		e = (unsigned short*) gm_NextEntityQueryMatch();
	}
	out->store = store;
	return 1;
}

/* Finds an entity by its owner. Searches for an entity
 * whose owner field matches the given ID. */

int __cdecl gm_GetMsgField(char* msg, char* pkt)
{
	unsigned short type;

	type = *(unsigned short*) msg;
	if (type == 0x2a || type == 0x116 || type == 0x1db || type == 0x1dc) {
		return *(int*) (pkt + 0xe) - 1;
	}
	return *(int*) (pkt + 0xe);
}

/* Client-only: a store's field for one item (discarded). */
int __cdecl gm_GetStoreItemField(char* store, int item)
{
	char* entry;

	entry = (char*) gm_ff_Objekt(*(int*) (store + 0x14), 1, 0, item);
	if (entry == 0) {
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetStoreItemField(): entry not found", 1);
		return 0;
	}
	return gm_GetMsgField(store, entry);
}

/* Gets a message field from a command packet. Reads a
 * specific field from the packet's payload section. */

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
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x31de, "gm_eval_SlotVoll(): Lager ist in keinem Geb\344ude", 1);
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

/* Client-only: room left in a store for `item`, capped at `limit`
 * (discarded). */
int __cdecl gm_GetStoreRoom(char* store, int item, int limit)
{
	char* entry;
	int cap;
	int free_room;
	int n;

	cap = compute_size(store, item);
	entry = (char*) gm_ff_Objekt(*(int*) (store + 0x14), 1, 0, item);
	if (entry != 0) {
		free_room = cap - *(int*) (entry + 0xe);
		return free_room > limit ? limit : free_room;
	}
	n = 0;
	for (entry = (char*) gm_ff_Objekt(*(int*) (store + 0x14), 1, 5); entry != 0; entry = (char*) gm_NextEntityQueryMatch()) {
		n++;
	}
	if (n >= (unsigned char) store[0x1c]) {
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetStoreRoom(): index out of range", 1);
		return 0;
	}
	return cap < limit ? cap : limit;
}

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

/* Client-only guild, wealth-ranking and relationship helpers (discarded). */

char* __cdecl gm_GetGuildHall(int guild)
{
	char* hall;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetGuildHall(): enter", 1);
	hall = 0;
	switch (guild) {
	case 1:
		hall = (char*) gm_StartFilteredEntitySearch(1, 5, 0xf);
		break;
	case 6:
	case 7:
		hall = 0;
		break;
	case 2:
		hall = (char*) gm_StartFilteredEntitySearch(1, 5, 0x17);
		break;
	case 3:
		hall = (char*) gm_StartFilteredEntitySearch(1, 5, 0x18);
		break;
	case 4:
		hall = (char*) gm_StartFilteredEntitySearch(1, 5, 0x19);
		break;
	case 5:
		hall = (char*) gm_StartFilteredEntitySearch(1, 5, 0x1a);
		break;
	}
	return hall;
}

int __cdecl gm_GetTypeGuild(int type_index, int* guild)
{
	int found;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetTypeGuild(): enter", 1);
	found = 1;
	switch ((unsigned char) g_entity_type_table[type_index * 0x24d]) {
	case 15:
		*guild = 1;
		break;
	case 23:
		*guild = 2;
		break;
	case 24:
		*guild = 3;
		break;
	case 25:
		*guild = 4;
		break;
	case 26:
		*guild = 5;
		break;
	case 7:
		*guild = 6;
		found = 0;
		break;
	case 4:
		*guild = 7;
		found = 0;
		break;
	case 16:
		*guild = 7;
	default:
		found = 0;
		break;
	}
	return found;
}

int __cdecl gm_GetWealthRank(int slot, int extra)
{
	unsigned char* e;
	int rank;
	int wealth;
	int j;

	rank = 1;
	if (slot < 0 || slot >= 0x300) {
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetWealthRank(): slot out of range", 1);
		return 0;
	}
	wealth = *(int*) (g_slot_table + 0x1ac + slot * 0x21c) + extra;
	for (j = 0, e = g_slot_table; j < 0x300; j++, e += 0x21c) {
		if (wealth <= *(int*) (e + 0x1ac) && *(unsigned short*) e != 0xffff && e[2] < 10 && j != slot) {
			rank++;
		}
	}
	return rank;
}

void __cdecl gm_GetRichestFive(int* ids, int* wealth)
{
	unsigned char* e;
	int i;
	int j;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetRichestFive(): enter", 1);
	for (i = 0; i < 5; i++) {
		ids[i] = 0xffff;
		wealth[i] = 0;
	}
	for (i = 0, e = g_slot_table; i < 0x300; i++, e += 0x21c) {
		if (*(int*) (e + 4) != -1 && e[2] < 10 && *(int*) (e + 0x1ac) > wealth[4]) {
			wealth[4] = *(int*) (e + 0x1ac);
			ids[4] = *(unsigned short*) e;
			for (j = 3; j > -1; j--) {
				if (*(int*) (e + 0x1ac) <= wealth[j] || e[2] >= 10) {
					break;
				}
				wealth[j + 1] = wealth[j];
				ids[j + 1] = ids[j];
				wealth[j] = *(int*) (e + 0x1ac);
				ids[j] = *(unsigned short*) e;
			}
		}
	}
}

int __cdecl gm_GetRelationship(int a, int b)
{
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_GetRelationship(): enter", 1);
	if (a == b) {
		return 0x7f;
	}
	return (signed char) g_relationship_matrix_primary[a * 0x300 + b];
}

int __cdecl gm_HasNoGuildHouse(char* entity)
{
	unsigned char* e;
	int i;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_HasNoGuildHouse(): enter", 1);
	if (entity[0x1b1] == 0) {
		return 0;
	}
	e = g_entity_ptr;
	for (i = 0; i < 0x100; i++, e += 0xa9) {
		if (*e != 0 && g_entity_type_table[*e * 0x24d] == 4 && *(int*) (e + 0x65) == *(int*) (entity + 4)) {
			return 0;
		}
	}
	return 1;
}

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

/* Client-only building-upgrade counts (discarded). */

int __cdecl gm_CountHouseUpgradesA(char* house)
{
	int n;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_CountHouseUpgradesA(): enter", 1);
	n = 1;
	if (gm_ff_Objekt(*(int*) (house + 0x5d), 2, 6, 0, 0x27a) != 0) {
		n = 2;
	}
	if (gm_ff_Objekt(*(int*) (house + 0x5d), 2, 6, 0, 0x27b) != 0) {
		n++;
	}
	if (gm_ff_Objekt(*(int*) (house + 0x5d), 2, 6, 0, 0x292) != 0) {
		n++;
	}
	return n;
}

int __cdecl gm_CountHouseUpgradesB(char* house)
{
	int n;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_CountHouseUpgradesB(): enter", 1);
	n = 2;
	if (gm_ff_Objekt(*(int*) (house + 0x5d), 2, 6, 0, 0x274) != 0) {
		n = 3;
	}
	if (gm_ff_Objekt(*(int*) (house + 0x5d), 2, 6, 0, 0x27e) != 0) {
		n++;
	}
	if (gm_ff_Objekt(*(int*) (house + 0x5d), 2, 6, 0, 0x28e) != 0) {
		n++;
	}
	if (gm_ff_Objekt(*(int*) (house + 0x5d), 2, 6, 0, 0x291) != 0) {
		n++;
	}
	return n;
}

int __cdecl gm_CountHouseUpgradesC(char* house)
{
	int n;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_CountHouseUpgradesC(): enter", 1);
	n = 1;
	if (gm_ff_Objekt(*(int*) (house + 0x5d), 2, 6, 0, 0x285)) {
		n = 2;
	}
	if (gm_ff_Objekt(*(int*) (house + 0x5d), 2, 6, 0, 0x288)) {
		n++;
	}
	return n;
}

int __cdecl gm_CountHouseUpgradesD(char* house)
{
	int n;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", __LINE__, "gm_CountHouseUpgradesD(): enter", 1);
	n = 4;
	if (gm_ff_Objekt(*(int*) (house + 0x5d), 2, 6, 0, 0x284)) {
		n = 7;
	}
	if (gm_ff_Objekt(*(int*) (house + 0x5d), 2, 6, 0, 0x289)) {
		n += 3;
	}
	return n;
}
