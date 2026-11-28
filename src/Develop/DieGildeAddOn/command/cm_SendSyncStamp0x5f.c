#include "Develop/DieGildeAddOn/game/game_data.h"



#include <string.h>

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendSyncStamp0x5f(void* payload)
{
	char buf[0x9c];

	memset(buf + 0x10, 0, 0x80);
	buf[0] = 0x5f;
	*(int*) payload = lb_LocalClientId;
	*(int*) (buf + 0x10) = 2;
	memcpy(buf + 0x14, payload, 0x57);
	cm_EnqueueClientPacket(buf);
}
