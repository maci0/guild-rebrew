#ifndef ENTITY_H
#define ENTITY_H

#include "../../game_common.h"
#include "../../game_structs.h"

/* Shared entity/slot globals — majority types across TUs (Round-558). */
extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern unsigned char g_slot_table[];
extern char g_entity_state_base[];
extern unsigned char g_entity_type_bytes[];

// SIZE 0x21c — 768 entries at g_slot_table (0x100358a0).
//
// Field map merged from two independently gathered sources, then each claim
// checked against the reference rather than trusted:
//   - the offset sweep over the tree (every `slot + 0xNN` in use), and
//   - the map written out in spiel62.c's header, derived from EXE cross-reference.
// The two agree on every offset they share; the sweep supplies the scalar fields
// the map omits, the map supplies the large blocks the sweep cannot see.
//
// WIDTH CORRECTIONS against the previous stub, each measured on the reference:
//   +0x28 was `unsigned short`; it is a 4-byte int.  Disassembly at 0x10016978 is
//   `mov edx,[0x10035880]` (g_current_year) / `dec edx` / `mov [esi+0x28],edx`,
//   and [r+0x28] appears with 66 dword encodings against 2 word encodings.  The old
//   width shifted every later field by 2, so anything using the struct past 0x28
//   would have addressed the wrong bytes.
//   +0x2C.. the old `pad9[0x28-9]` is replaced by the real fields at 0x10-0x24.
//
// NOT a field of this record: `+0x27`.  It is read as a 2-byte slot index in
// cm_ChkJoinLeaveElection / cm_ExSellObjekt and scaled by 0x21c, but the base there is
// the record gm_StartFilteredEntitySearch returns, which walks with stride 0xa9
// (spiel_dumpD.c: `list_head += 0xa9`, reading +0x25 and +0x27).  A word at 0x27 cannot
// coexist with the 4-byte season_born at 0x28, and disassembly puts them on different
// bases.  Do not add +0x27 here.
//
// Pads are real: either fields no surviving code touches, or alignment.  A guessed name
// is worse than a gap.  sizeof == 0x21c is load-bearing -- it IS the array stride.
typedef struct EntityStruct {
    unsigned short entity_index;  /* +0x000  self-index; 0xffff = free slot */
    unsigned char entity_state;  /* +0x002  0xf dead/free; 3/0x10/0x13 type tests */
    char pad_003[1];
    int entity_id;  /* +0x004  from g_next_object_id */
    char health;  /* +0x008  init 100 (0x64) */
    char gender;  /* +0x009   */
    unsigned short profession_type;  /* +0x00a   */
    char pad_00c[1];
    char is_active;  /* +0x00d  init 1; 2 for types 3/0x10/0x13 */
    char pad_00e[2];
    float pos_x;  /* +0x010   */
    float pos_y;  /* +0x014   */
    float pos_z;  /* +0x018   */
    float scale;  /* +0x01c  init 1000.0f */
    float rotation;  /* +0x020   */
    int field_24;  /* +0x024  init -1 alongside 0x20 (gm_AllocObjekt 0x1001696b) */
    int season_born;  /* +0x028  4-byte: mov [esi+0x28],edx after dec of g_current_year (0x10016978) */
    char pad_02c[36];
    unsigned short max_hp;  /* +0x050  init 0x7fff */
    char pad_052[10];
    int ref_table[8];  /* +0x05c  reference ids, init -1 */
    char pad_07c[4];
    char slot_name[5];  /* +0x080  random chars on alloc */
    char pad_085[3];
    char stats_block[168];  /* +0x088  skills/attributes */
    char pad_130[52];
    unsigned char age;  /* +0x164   */
    char pad_165[7];
    void* home_building;  /* +0x16c   */
    void* current_building;  /* +0x170   */
    char pad_174[4];
    char linked_list_head;  /* +0x178  free list for gm_FreeObjectListRecursive */
    char pad_179[19];
    int target_id;  /* +0x18c  init -1 */
    int ai_state;  /* +0x190  init 4 */
    char pad_194[56];
    int entity_flags;  /* +0x1cc  bitfield */
    char pad_1d0[20];
    float move_speed;  /* +0x1e4  init 1.0f (0x3f800000) */
    char pad_1e8[8];
    int quest_state;  /* +0x1f0   */
    char pad_1f4[24];
    int cutscene_id;  /* +0x20c  init -1 */
    int patrol_target;  /* +0x210  init -1 */
    char pad_214[8];  /* tail padding to the 0x21c stride */
} EntityStruct;

/* ID and Pointer Resolution */
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);

/* State Reset */
extern void __cdecl gm_ResetAllEntities(void);

#endif /* ENTITY_H */
