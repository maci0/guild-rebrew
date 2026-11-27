extern char g_7f4ca4[];
#include "Develop/DieGildeAddOn/game/game_player.h"



int __cdecl cm_RequestSysMessage(int, void*);

void __cdecl cm_SendQuitGameCommand(void)
{
	char buf[0x7c];
	*(int*) buf = *(int*) (g_7f4ca4 + (unsigned int) (unsigned short) *(unsigned short*) ((char*)&g_774970) * 135 * 4);
	cm_RequestSysMessage(0x13, &buf);
}
