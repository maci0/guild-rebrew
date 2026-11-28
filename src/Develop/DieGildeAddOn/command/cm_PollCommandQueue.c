


#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* g_14cbca4;
extern int g_772e80;
extern char g_1005780;

void __cdecl nt_Recv(void);
int __cdecl cm_EnqueueCommand(char*);

/* ADDRESS: GOLDDE 0x004b2350 */
int __cdecl cm_PollCommandQueue(void)
{
	if (nt_ClientSocket == -1) {
		return 0;
	}
	if (g_14cbca4 != 0) {
		nt_Recv();
		if (g_14cbca4 != 0) {
			return 0;
		}
	}
	do {
		g_772e80++;
		if (cm_EnqueueCommand(((char*)&g_1005780)) != 0) {
			return 1;
		}
		g_14cbca4 = ((char*)&g_1005780);
		nt_Recv();
	} while (g_14cbca4 == 0);
	return 0;
}
