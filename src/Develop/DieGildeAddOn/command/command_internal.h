#ifndef COMMAND_INTERNAL_H
#define COMMAND_INTERNAL_H

#include "../../game_common.h"
#include "../../game_structs.h"
#include <stdlib.h>

/*
 * Preserved declaration context shared by command handlers.
 * Known signature exceptions remain, including gm_QueryEntitySum:
 * this header uses (int, int); server command.c uses (int, unsigned char).
 * Review compiler context before changing these declarations.
 *
 * NOTE: game_structs.h provides PlayerSlot with data at offset 8.
 * command/player_slot.h provides player_slot with data at 0x264204
 * (server command.c:1574 cm_ExAllocRaum, :4371 cm_ExCreateGeb). Other
 * layouts (historically cm_ExSysMessage, now server command.c:3615, flags at 0) keep
 * those local definitions.
 */

/* Entity resolution and lookup */
extern int __cdecl gm_GetFieldByType(char*, int);
extern int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
extern int __cdecl gm_LookupEntityRecordById(int);
/* NOTE (round 183): this declaration is WRONG and is kept deliberately.
 * The original's second parameter is a BYTE: all four reference call
 * sites push it bare with no zero-extend (0x1000cd8d
 * `mov dl,[esi+0x1e]` straight into `push edx`), whereas the
 * neighbouring gm_FindSlotById sites at 0x1000ddb8 do emit
 * `xor edx,edx; xor eax,eax` first -- a deliberate contrast.  The
 * callee cannot settle the width: it loads a dword and masks
 * (`and edx,0xff` at 0x100196df), and both formals compile
 * byte-identically.
 *
 * Declaring it `(int, unsigned char)` is semantically inert (no call
 * site passes >255, and the callee masks anyway) and makes both
 * cm_ExSellObjekt sites byte-exact -- but it costs +37 linked,
 * because dropping those 6 bytes displaces ~325B of otherwise
 * aligned tail in that function.  Measured round 183.  The two other
 * server callers were cm_ChkSellObjekt (now command.c:1158) via a
 * function-pointer cast, cm_ChkMoveCredits (now command.c:1124) via a narrow
 * declaration; both were RELOC in round 183. Recheck before changing
 * this declaration or cm_ExSellObjekt's tail alignment. */
extern int __cdecl gm_QueryEntitySum(int, int);
extern unsigned short* __cdecl gm_NextEntityQueryMatch(void);
extern char* __cdecl gm_FindSlotById(unsigned int, unsigned int);

/* Entity management */
extern int __cdecl gm_SubObjekt(void*, unsigned int, int);
extern int __cdecl gm_CleanupBuildingEntity(unsigned char*);
extern void __cdecl gm_RemoveEntityLink(int);
extern int __cdecl gm_CheckInventoryCapacity(char*, unsigned int, int);
extern int __cdecl gm_GetMsgField(int, int);
#include "../game/spiel.h"
extern void* __cdecl gm_FindRecordById(int);

/* CRT / thread */

/* Common globals */
extern int g_next_object_id;
extern unsigned char g_slot_table[2];

/* __FILE__ string for LogMessageInternal calls in command.c */


/* Entity query and search (correct signatures from spiel.c definitions) */
extern unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
extern char* __cdecl gm_AllocObjekt(int, int, int);
extern int __cdecl gm_RemoveObjectByType(void**, unsigned int);

/* game/zufall.c contains the reference's srand(seed) thunk at
 * 0x1001a150.  The command handlers call THIS, not the CRT `_srand`; calling
 * `srand` directly is relocation-masked by `rebrew test`, so the difference
 * hid behind six RELOC passes. */
extern void __cdecl srv_SeedRandom(unsigned int seed);
#endif /* COMMAND_INTERNAL_H */
