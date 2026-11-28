extern int cut_NextCutsceneId;
extern int cut_NextCutsceneId;



#include <string.h>

#pragma intrinsic(memcpy, memset)

char* __cdecl cut_FindFreeCutscene(void);

#include "Develop/DieGildeAddOn/command/client_packet_queue.h"

/* ADDRESS: GOLDDE 0x004d3330 */
char* __cdecl cut_AllocCutscene(void* src)
{
	char* p;

	p = cut_FindFreeCutscene();
	if (p != 0) {
		memcpy(p, src, 0x114);
		*(int*) p = cut_NextCutsceneId;
		if (*(char*) (p + 0x31) == 0) {
			*(char*) (p + 0x31) = 8;
		}
	}
	return p;
}
