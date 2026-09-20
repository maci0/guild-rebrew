#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "game_common.h"

/* --- Core Game Structures --- */

/* Player Slot structure - handles player state and data */
typedef struct PlayerSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char data[0x26425C]; /* Total size 0x264264 */
} PlayerSlot;

/* --- Linked-list node (0x43 bytes, 1-byte packed) ---
 *
 * Two TUs spell this layout and four more reach it through the removal
 * helpers, so it leaves the .c files.  The two local copies disagreed ONLY on
 * naming; together the callers fix both words' evidence:
 *   +0x00 word is a TYPE: gm_RemoveObjectByType matches it against 16-bit
 *   object types (cm_ExClearLagerslot `cmd[0x14/2]`, cm_ExProdObjekt
 *   `*material_iter`, cm_ExSellObjekt `*(ushort*)(cmd + 0x18)`).
 *   +0x02 int is a unique entity ID: gm_RemoveLinkedNodeById matches it
 *   against `*(int*)(entity + 2)` (gm_RemoveObjectWrapper).
 * Removal clears the type word — that is the `active = 0` / `id = 0` store
 * both bodies end with.  Naming follows EntityQueryRecord's vocabulary. */
#pragma pack(push, 1)
// SIZE 0x43
typedef struct LinkedNode {
	unsigned short type;         /* 0x00  cleared by both remove helpers */
	int entity_id;               /* 0x02  */
	char pad0[0x0e];             /* 0x06  */
	struct LinkedNode* children; /* 0x14  */
	char pad1[0x27];             /* 0x18  */
	struct LinkedNode* next;     /* 0x3f  */
} LinkedNode;
#pragma pack(pop)

/* --- Office slot table entry (0x18 bytes) --- */
// SIZE 0x18
typedef struct {
	unsigned char id;        /* +0x00 */
	unsigned char pad1[3];
	int mplayerid;           /* +0x04 */
	unsigned char mamt;      /* +0x08 */
	unsigned char pad2[3];
	int pcount;              /* +0x0c */
	unsigned char status;    /* +0x10 */
	unsigned char pad3[3];
	int msetter;             /* +0x14 */
} OFFICE_SLOT;

/* --- Entity query record ---
 *
 * The 0x100-entry, 0xa9-stride table behind g_entity_ptr: 0x100 * 0xa9 == 0xa900,
 * which is the block gm_Open allocates and zero-fills, and the bound
 * gm_SearchStruct and gm_FindNextFilteredEntity walk against.
 *
 * Six translation units index it with the same stride
 * (spiel.c, spiel5.c, spiel6.c, gm_ChangePlayerIdentityImpl.c) and read its
 * filter words (spiel_dumpD.c), so this is a shared layout rather than a local
 * one -- the condition the round brief sets for lifting a type into a header.
 *
 * Verified against the reference, not inferred:
 *   0x10017210 gm_SearchStruct:  lea ecx,[eax + 0xa900]   ; total span
 *                                add eax, 0xa9           ; stride
 *                                cmp byte ptr [eax], 0   ; the +0x00 type byte
 *   0x1000fe86 mov cx, word ptr [eax + 0x27]              ; slot index, 2 bytes
 *   0x1000fea0 lea ecx, [ecx*4 + 0x100358a0]             ; ...scaled by 540
 *
 * ONLY the offsets surviving code touches are named.  The record is 0xa9 bytes
 * and this binary leaves most of it unused, so the middle is one pad rather than
 * invented fields.  sizeof is load-bearing: it IS the array stride.
 *
 * NOT to be confused with `EntityStruct` (game/entity.h), which is the
 * 0x21c-stride record at g_slot_table and a different type entirely.  The word
 * at +0x27 here is a slot index *into* that array.  Both records have a field
 * near 0x28, which is what made this look like one struct; see
 * measure-traps.md section 6. */
// SIZE 0xa9
/* Packed: the reference reads a word at +0x27, an ODD offset, so the original
 * compiled this record with 1-byte packing.  Without the pragma MSVC6 pads
 * `int entity_id` to offset 4 and every field after it moves. */
#pragma pack(push, 1)
typedef struct EntityQueryRecord {
    char type;                 /* +0x00  0 = free; category via gm_GetBuildingTypeCategory */
    int entity_id;             /* +0x01  matched against an id by spiel6 / spiel_dumpD */
    char pad_05[0x20];
    unsigned short filter_25;  /* +0x25  g_query_filter_extra2 compare */
    unsigned short slot_index; /* +0x27  index into g_slot_table, scaled by 0x21c */
    char pad_29[0x80];
} EntityQueryRecord;
#pragma pack(pop)

#endif /* GAME_STRUCTS_H */
