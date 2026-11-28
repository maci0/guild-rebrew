#include "Develop/DieGildeAddOn/game/game_data.h"



#include <string.h>

void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b4020 */
void __cdecl cm_SendCutCommand51(int cutscene_id, void* payload)
{
	char buf[0x9c];

	buf[0] = 0x51;
	*(int*) (buf + 0x10) = cutscene_id;
	*(int*) (buf + 0x40) = cut_ActiveCutscene != 0 ? *cut_ActiveCutscene : -1;
	memcpy(buf + 0x14, payload, 0x2c);
	cm_EnqueueClientPacket(buf);
}
