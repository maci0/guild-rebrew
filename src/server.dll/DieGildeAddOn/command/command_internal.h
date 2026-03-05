#ifndef COMMAND_INTERNAL_H
#define COMMAND_INTERNAL_H

#include "../../game_common.h"
#include "../../game_structs.h"

/*
 * Common extern declarations shared by command handler .c files.
 * Only includes functions/globals with IDENTICAL signatures across all usage.
 * Functions with per-file signature variations (LogMessageInternal,
 * AllocGameObject, StartEntityQuery, etc.) must remain declared locally.
 *
 * NOTE: game_structs.h provides PlayerSlot with data at offset 8.
 * Files that define local player_slot/TradePlayerSlot structs with custom
 * field layouts (e.g. data at 0x264200) must keep those local definitions.
 */

/* Entity resolution and lookup */
extern int __cdecl get_field_by_type(char*, int);
extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern int __cdecl LookupEntityRecordById(int);
extern int __cdecl QueryEntitySum(int, int);

/* CRT / thread */
extern int __cdecl rand(void);
extern void __cdecl crt_thread_set_alt(int);

/* Common globals */
extern int g_timestamp_0b6c;
extern char g_static_entity_table_358a0[];

/* __FILE__ string for LogMessageInternal calls in command.c */
extern char s_D__Develop_DieGildeAddOn_command_1002c748[];

#endif /* COMMAND_INTERNAL_H */
