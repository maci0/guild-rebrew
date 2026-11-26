#include "Develop/DieGildeAddOn/game/game_data.h"



#include <string.h>

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl fcn_004ce260(int a1)
{
	char buf[0x9c];

	memset(buf + 0x10, 0, 0x80);
	buf[0] = 0x5f;
	*(int*) (buf + 0x10) = 3;
	*(int*) (buf + 0x14) = g_9badd0;
	cm_EnqueueClientPacket(buf);
}
