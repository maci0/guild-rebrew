#include "Develop/DieGildeAddOn/game/game_data.h"



#include <string.h>

void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004bba00 */
void __cdecl lb_RequestLeaveLobby(int unused)
{
	char buf[0x9c];

	memset(buf + 0x10, 0, 0x80);
	buf[0] = 0x5f;
	*(int*) (buf + 0x10) = 3;
	*(int*) (buf + 0x14) = lb_LocalClientId;
	cm_EnqueueClientPacket(buf);
}
