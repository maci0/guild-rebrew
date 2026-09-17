#ifndef ENTITY_H
#define ENTITY_H

#include "../../game_common.h"
#include "../../game_structs.h"

/* Shared entity/slot globals — majority types across TUs (Round-558). */
extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern unsigned char g_slot_table[];
extern char g_entity_state_base[];
extern unsigned char g_entity_type_bytes[];

// SIZE 0x21c — 768 entries at g_slot_table (0x100358a0). Pads match types.h.
typedef struct EntityStruct {
	unsigned short word0; /* +0x00 entity_index */
	unsigned char byte2;  /* +0x02 entity_state */
	unsigned char pad3;
	int id;     /* +0x04 entity_id */
	char byte8; /* +0x08 health */
	char pad9[0x28 - 9];
	unsigned short word28; /* +0x28 season_born */
	char pad2a[0x5c - 0x2a];
	int table5c[8]; /* +0x5C ref_table */
	char pad7c[0x178 - 0x7c];
	char field178; /* +0x178 linked_list_head */
	char pad179[0x21c - 0x179];
} EntityStruct;

/* ID and Pointer Resolution */
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);

/* State Reset */
extern int __cdecl gm_ResetAllEntities(void);

#endif /* ENTITY_H */
