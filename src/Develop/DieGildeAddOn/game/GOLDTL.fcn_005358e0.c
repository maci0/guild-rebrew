#include "Develop/DieGildeAddOn/game/game_data.h"




#include <string.h>

int __cdecl cm_RequestSysMessage(int, char*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl fcn_00533a40(char*);
void __cdecl main_RunFrameLoop(int, int);

void __cdecl cm_WaitNetworkSyncBanner(char* name)
{
	char buf[0x7c];
	int s;

	memset(buf, 0, sizeof(buf));
	strcpy(buf, name);
	s = cm_RequestSysMessage(0xe, buf);
	while (cm_GetCommandStatus(s) == 0) {
		fcn_00533a40(name);
		main_RunFrameLoop(0, cut_EventLoopFlags | 0x210000);
	}
}
