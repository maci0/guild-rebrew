


#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl cm_RequestSysMessage(int, void*);

/* ADDRESS: GOLDDE 0x004b2270 */
void __cdecl cm_SetGameSpeedSetting(unsigned int speed)
{
	char buf[0x7c];

	if (speed >= 4) {
		speed = 4;
	}
	if (speed != (*(unsigned int*)g_68a9cc)) {
		*(unsigned int*) buf = speed;
		cm_RequestSysMessage(0x12, buf);
	}
}
