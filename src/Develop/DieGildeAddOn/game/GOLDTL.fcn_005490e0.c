

#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntityIdField[];

void __cdecl cm_SendCopyEntityData(char*);

void __cdecl he_PostSimPersonal(void)
{
	char msg[0xf8];

	msg[4] = 0x3a;
	*(int*) (msg + 0xc) = -1;
	msg[0x36] = 1;
	*(int*) (msg + 8) = *(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c);
	cm_SendCopyEntityData(msg);
}
