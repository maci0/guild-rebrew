


extern volatile int g_6b7fac;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_004c3ff0(void);
int __cdecl fcn_004c4940(void);

char* __cdecl fcn_004c49a0(char kind, int timeout)
{
	unsigned int end;
	char* p;

	end = (unsigned int)g_6b7fac + timeout;
	while ((unsigned int)g_6b7fac < end) {
		fcn_004c3ff0();
		fcn_004c4940();
		for (p = cm_CommandQueueHead; p != 0; p = *(char**) (p + 0x95)) {
			if (*p == kind) {
				return p;
			}
		}
	}
	return 0;
}
