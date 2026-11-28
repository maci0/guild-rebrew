#pragma pack(push, 1)
struct CMD_FREE_NODE {
	char used;
	char data[0x90];
	struct CMD_FREE_NODE* prev;
	struct CMD_FREE_NODE* next;
};
// SIZE 0x99

struct CMD_STATUS_SLOT_VIEW {
	char free;
	char pad1;
	int owner;
	char pad6[4];
};
// SIZE 0xa
#pragma pack(pop)

extern char g_9bade0[];
#include "Develop/client_types.h"
extern COMMAND_STATUS_SLOT cm_CommandStatusQueue[0x8000];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_1005780;


/* ADDRESS: GOLDTL 0x004c3e30 */
void __cdecl cm_InitCommandQueue(void)
{
	int i;

	for (i = 0; i < 0x2000; i++) {
		((struct CMD_FREE_NODE*)g_9bade0)[i].used = 0;
		if (i == 0)
			((struct CMD_FREE_NODE*)g_9bade0)[0].prev = 0;
		else
			((struct CMD_FREE_NODE*)g_9bade0)[i].prev = &((struct CMD_FREE_NODE*)g_9bade0)[i - 1];
		if (i < 0x1fff)
			((struct CMD_FREE_NODE*)g_9bade0)[i].next = &((struct CMD_FREE_NODE*)g_9bade0)[i + 1];
		else
			((struct CMD_FREE_NODE*)g_9bade0)[i].next = 0;
	}
	(*(struct CMD_FREE_NODE**)&g_aed200) = ((struct CMD_FREE_NODE*)g_9bade0);
	(*(int*)&cm_CommandQueueHead) = 0;
	g_1005780 = 0;
	g_1005768 = 0;
	g_1005760 = 0;
	for (i = 0; i < 0x8000; i++) {
		((struct CMD_STATUS_SLOT_VIEW*)cm_CommandStatusQueue)[i].owner = -1;
		((struct CMD_STATUS_SLOT_VIEW*)cm_CommandStatusQueue)[i].free = 1;
	}
}
