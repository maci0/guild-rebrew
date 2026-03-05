#ifndef ENTITY_H
#define ENTITY_H

#include "../../game_common.h"
#include "../../game_structs.h"

/* Slot Management */
extern int __cdecl ahm_AllocateEntitySlot(void);
extern void __cdecl gm_InitEntitySlots(void);
extern int __cdecl gv_CheckSlotActive(int slot_id);

/* ID and Pointer Resolution */
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl cm_AssignEntityId(void* entity_ptr);
extern void* __cdecl gm_LookupEntityInTable(int id);

/* Entity Lifecycle */
extern void __cdecl ahm_InitRandomEntity(void* entity);
extern int __cdecl gm_InitEntityIfValid(void* entity);
extern void __cdecl gm_DeallocEntity(unsigned int index, int param_2);
extern void __cdecl vfs_DestroyEntity(void* entity);

/* Chain and Link Processing */
extern void __cdecl gm_ProcessEntityChain(void);
extern int __cdecl gm_WalkEntityChain(int raw_idx);
extern void __cdecl amt_ClearEntityLinks(void* entity);
extern void __cdecl amt_UpdateEntityLinks(void* entity);

/* State Reset */
extern int __cdecl gm_ResetAllEntities(void);
extern void __cdecl gm_CleanupAllEntities(void);

#endif /* ENTITY_H */
