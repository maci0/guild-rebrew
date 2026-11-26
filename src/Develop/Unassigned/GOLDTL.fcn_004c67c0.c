#include "Develop/DieGildeAddOn/game/game_data.h"



#include <string.h>

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendUpdateCutsceneEntitySlot(int slotId, void* payload)
{
	char buf[0x9c];

	buf[0] = 0x50;
	*(int*) (buf + 0x10) = slotId;
	*(int*) (buf + 0x40) = cut_ActiveCutscene != 0 ? *cut_ActiveCutscene : -1;
	memcpy(buf + 0x14, payload, 0x2c);
	cm_EnqueueClientPacket(buf);
}
