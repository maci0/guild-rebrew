


extern char* sv_HoveredCharacter;
extern int g_14ce8cc;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char g_6a9834[];

void __cdecl he_SetEntityScriptFlag(char*, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
char* __cdecl ch_AttachEntityGfxScript(char*, char*);

/* ADDRESS: GOLDDE 0x00574ce0 */
void __cdecl he_DispatchEntityInteractReturn(void)
{
	char* r;

	if (sv_HoveredCharacter != 0 && (sv_HoveredCharacter[0x1b4] & 1) && g_14ce8cc != 0) {
		he_SetEntityScriptFlag(sv_HoveredCharacter, 0);
		cm_RequestCopyEntityData(((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, *(int*) (sv_HoveredCharacter + 4), -5, 0);
		r = ch_AttachEntityGfxScript(sv_HoveredCharacter, g_6a9834);
		if (r != 0) {
			*(int*) (r + 0xc8c) = 1;
		}
	}
}
