void __cdecl he_FreeAction(char*);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;




void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl cm_SendSetHE(int, char*);

void __cdecl he_RunCountdownAction(char* action)
{
	if (*(int*) (action + 0x70) < 0 || *(int*) (action + 0xac) <= 0) {
		he_FreeAction(action);
		return;
	}
	if ((action[0x78] & 4) == 0) {
		(*(int*) (action + 0xac))--;
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (action + 0x52), 0x18, 0, 0);
		*(int*) (action + 0x84) = cm_SendSetHE(0, action);
	}
}
