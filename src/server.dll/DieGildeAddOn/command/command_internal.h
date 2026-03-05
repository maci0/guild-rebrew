#ifndef COMMAND_INTERNAL_H
#define COMMAND_INTERNAL_H

#include "../../game_common.h"
#include "../../game_structs.h"

/*
 * Common extern declarations shared by command handler .c files.
 * Only includes functions/globals with IDENTICAL signatures across all usage.
 * Functions with per-file signature variations (LogMessageInternal,
 * gm_AllocObjekt, gm_StartEntityQuery, etc.) must remain declared locally.
 *
 * NOTE: game_structs.h provides PlayerSlot with data at offset 8.
 * Files that define local player_slot/TradePlayerSlot structs with custom
 * field layouts (e.g. data at 0x264200) must keep those local definitions.
 */

/* Entity resolution and lookup */
extern int __cdecl gm_GetFieldByType(char*, int);
extern int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
extern int __cdecl gm_LookupEntityRecordById(int);
extern int __cdecl gm_QueryEntitySum(int, int);
extern unsigned short* __cdecl gm_NextEntityQueryMatch(void);
extern char* __cdecl gm_FindSlotById(unsigned int, unsigned int);

/* Entity management */
extern int __cdecl gm_SubObjekt(void*, unsigned int, int);
extern int __cdecl gm_CleanupBuildingEntity(unsigned char*);
extern void __cdecl gm_RemoveEntityLink(int);
extern void __cdecl gm_DeallocEntity(unsigned int, int);
extern int __cdecl gm_CheckInventoryCapacity(char*, unsigned int, int);
extern int __cdecl gm_KannObjektHergestellt(char*, unsigned int, int);
extern int __cdecl gm_GetMsgField(int, int);
extern short* __cdecl gm_GetEntityTableEntry(char*);
extern void* __cdecl gm_FindRecordById(int);

/* CRT / thread */
extern int __cdecl rand(void);
extern void __cdecl crt_thread_set_alt(int);

/* Common globals */
extern int g_timestamp_0b6c;
extern char g_static_entity_table_358a0[];

/* __FILE__ string for LogMessageInternal calls in command.c */
extern char s_D__Develop_DieGildeAddOn_command_1002c748[];


/* Entity query and search (correct signatures from spiel.c definitions) */
extern unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
extern unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
extern char* __cdecl gm_AllocObjekt(int, int, int);
extern int __cdecl gm_RemoveObjectByType(void**, unsigned int);
#endif /* COMMAND_INTERNAL_H */
