#include "Develop/DieGildeAddOn/game/game_data.h"



#include <string.h>

void __cdecl cm_EnqueueClientPacket(void*);

int __cdecl fcn_0064d3f8(void);

void __cdecl cm_SendAddStraftat(void* crimeRecord)
{
	char buf[0x9c];

	buf[0] = 0x22;
	memcpy(buf + 0x10, crimeRecord, 0x2d);
	*(int*) (buf + 0x10) = cm_LastCrimeId;
	*(int*) (buf + 0x35) = 1;
	*(int*) (buf + 0x39) = fcn_0064d3f8();
	cm_EnqueueClientPacket(buf);
}
