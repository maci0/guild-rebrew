#include "Develop/DieGildeAddOn/game/game_data.h"



void __cdecl cm_RequestSysMessage(int, void*);

void __cdecl cm_RequestIncreaseGameSpeed(void)
{
	char buf[0x7c];

	if (*(unsigned*) g_68a9cc < 4) {
		*(int*) buf = *(unsigned*) g_68a9cc + 1;
		cm_RequestSysMessage(0x12, buf);
	}
}
