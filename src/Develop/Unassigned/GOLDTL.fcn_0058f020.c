


extern char* g_7746b4;
extern int g_14ce8cc;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char g_6a9834[];

void __cdecl fcn_005904a0(char*, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
char* __cdecl ch_AttachEntityGfxScript(char*, char*);

void __cdecl fcn_0058f020(void)
{
	char* r;

	if (g_7746b4 != 0 && (g_7746b4[0x1b4] & 1) && g_14ce8cc != 0) {
		fcn_005904a0(g_7746b4, 0);
		cm_RequestCopyEntityData(((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id, *(int*) (g_7746b4 + 4), -5, 0);
		r = ch_AttachEntityGfxScript(g_7746b4, g_6a9834);
		if (r != 0) {
			*(int*) (r + 0xc8c) = 1;
		}
	}
}
