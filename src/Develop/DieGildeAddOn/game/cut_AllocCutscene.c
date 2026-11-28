extern int g_699368;
extern int g_699368;



#include <string.h>

#pragma intrinsic(memcpy, memset)

char* __cdecl cut_FindFreeCutscene(void);

#include "client_packet_queue.h"

char* __cdecl cut_AllocCutscene(void* src)
{
	char* p;

	p = cut_FindFreeCutscene();
	if (p != 0) {
		memcpy(p, src, 0x114);
		*(int*) p = g_699368;
		if (*(char*) (p + 0x31) == 0) {
			*(char*) (p + 0x31) = 8;
		}
	}
	return p;
}
