


#include "Develop/client_types.h"

#pragma pack(push, 1)
typedef struct node99 {
	char f0;
	char pad[0x90];
	struct node99* prev;
	struct node99* next;
} node99;
#pragma pack(pop)
/* SIZE 0x99 */

typedef COMMAND_STATUS_SLOT cell10;
/* SIZE 0xa */

extern int g_68a9dc;
extern char g_9bade0[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_1005780;
extern COMMAND_STATUS_SLOT cm_CommandStatusQueue[0x8000];
extern char* g_14cbca4;
extern volatile int gm_GameTicks;
extern unsigned int g_aecde4;

void __cdecl cm_SendCommandQueueInit(void);
int __cdecl cm_RecvSceneInitPacket(void);
void __cdecl nt_CloseClientConnection(void);

/* ADDRESS: GOLDDE 0x004b1800 */
void __cdecl cm_ResetCommandQueue(void)
{
	int i;

	g_68a9dc = -1;
	for (i = 0; i < 0x2000; i++) {
		((node99*)g_9bade0)[i].f0 = 0;
		if (i == 0)
			((node99*)g_9bade0)[0].prev = 0;
		else
			((node99*)g_9bade0)[i].prev = &((node99*)g_9bade0)[i - 1];
		if (i < 0x1fff)
			((node99*)g_9bade0)[i].next = &((node99*)g_9bade0)[i + 1];
		else
			((node99*)g_9bade0)[i].next = 0;
	}
	(*(node99**)&g_aed200) = ((node99*)g_9bade0);
	(*(int*)&cm_CommandQueueHead) = 0;
	g_1005780 = 0;
	g_1005768 = 0;
	g_1005760 = 0;
	for (i = 0; i < 0x8000; i++) {
		cm_CommandStatusQueue[i].f2 = -1;
		cm_CommandStatusQueue[i].f0 = 1;
	}
	g_14cbca4 = &g_1005780;
	cm_SendCommandQueueInit();
	if (cm_RecvSceneInitPacket() != 0)
		nt_CloseClientConnection();
	(*(int *)&g_aecde4) = gm_GameTicks;
}
