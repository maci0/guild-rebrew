


#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDDE 0x004b24b0 */
void __cdecl cm_RecycleCommandQueueNode(char* node)
{
	char* prev;
	char* next;

	prev = *(char**) (node + 0x91);
	if (prev != 0) {
		*(char**) (prev + 0x95) = *(char**) (node + 0x95);
	} else {
		cm_CommandQueueHead = *(char**) (node + 0x95);
	}
	next = *(char**) (node + 0x95);
	if (next != 0) {
		*(char**) (next + 0x91) = *(char**) (node + 0x91);
	}
	*(char**) (node + 0x91) = 0;
	*(char**) (node + 0x95) = g_aed200;
	g_aed200 = node;
}
