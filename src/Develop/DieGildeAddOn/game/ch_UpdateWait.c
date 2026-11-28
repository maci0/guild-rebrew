extern volatile int gm_GameTicks;



#include "Develop/DieGildeAddOn/game/ch_queue.h"

void __cdecl ch_UpdateWait(char* entry)
{
	if (*(int*) (entry + 0xc) == 0) {
		*(int*) (entry + 0x34) = *(int*) ((char*)&gm_GameTicks);
	}
	if (*(unsigned int*) ((char*)&gm_GameTicks) > (unsigned int) (*(int*) (entry + 0x34) + *(int*) (entry + 0x30)) ||
	    *(unsigned char*) (entry + 0x190) != 0) {
		ch_RemoveQueueEntry(entry);
	}
}
