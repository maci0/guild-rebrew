#include "Develop/DieGildeAddOn/game/game_data.h"



#include <string.h>

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6820(int a1, void* payload)
{
	char buf[0x9c];

	buf[0] = 0x51;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x40) = cut_ActiveCutscene != 0 ? *cut_ActiveCutscene : -1;
	memcpy(buf + 0x14, payload, 0x2c);
	fcn_004c4330(buf);
}
