#include "Develop/DieGildeAddOn/game/game_data.h"




#include <string.h>

int __cdecl cm_RequestSysMessage(int, char*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl d2_ShowStatusBanner(char*);
void __cdecl main_RunFrameLoop(int, int);

/* ADDRESS: GOLDDE 0x0051e140 */
void __cdecl cm_WaitNetworkSyncBanner(char* name)
{
	char buf[0x7c];
	int s;

	memset(buf, 0, sizeof(buf));
	strcpy(buf, name);
	s = cm_RequestSysMessage(0xe, buf);
	while (cm_GetCommandStatus(s) == 0) {
		d2_ShowStatusBanner(name);
		main_RunFrameLoop(0, cut_EventLoopFlags | 0x210000);
	}
}
