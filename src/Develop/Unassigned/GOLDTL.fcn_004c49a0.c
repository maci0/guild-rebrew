


extern volatile int g_6b7fac;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl cm_FlushCommandQueue(void);
int __cdecl cm_PollCommandQueue(void);

char* __cdecl cm_WaitForQueuedCommand(char kind, int timeout)
{
	unsigned int end;
	char* p;

	end = (unsigned int)g_6b7fac + timeout;
	while ((unsigned int)g_6b7fac < end) {
		cm_FlushCommandQueue();
		cm_PollCommandQueue();
		for (p = cm_CommandQueueHead; p != 0; p = *(char**) (p + 0x95)) {
			if (*p == kind) {
				return p;
			}
		}
	}
	return 0;
}
