extern char gm_EntityIdField[];
#include "Develop/DieGildeAddOn/game/game_player.h"



int __cdecl cm_RequestSysMessage(int, void*);

void __cdecl cm_SendQuitGameCommand(void)
{
	char buf[0x7c];
	*(int*) buf = *(int*) (gm_EntityIdField + (unsigned int) (unsigned short) *(unsigned short*) ((char*)&gm_LocalPlayerSlot) * 135 * 4);
	cm_RequestSysMessage(0x13, &buf);
}
