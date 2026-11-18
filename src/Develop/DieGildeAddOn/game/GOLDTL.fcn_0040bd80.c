extern volatile int g_6b7fac;



#include "Develop/DieGildeAddOn/game/ch_queue.h"

void __cdecl fcn_0040bd80(char* entry)
{
	if (*(int*) (entry + 0xc) == 0) {
		*(int*) (entry + 0x34) = *(int*) ((char*)&g_6b7fac);
	}
	if (*(unsigned int*) ((char*)&g_6b7fac) > (unsigned int) (*(int*) (entry + 0x34) + *(int*) (entry + 0x30)) ||
	    *(unsigned char*) (entry + 0x190) != 0) {
		ch_RemoveQueueEntry(entry);
	}
}
