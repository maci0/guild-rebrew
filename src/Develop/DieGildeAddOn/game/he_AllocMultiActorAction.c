int __cdecl cm_SendSetHE(int, char*);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;




void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

/* ADDRESS: GOLDDE 0x0053a480 */
void __cdecl he_AllocMultiActorAction(char* action)
{
	if ((action[0x78] & 4) == 0) {
		*(int*) (action + 0xd4) = -1;
		action[0xdc] = 0;
		*(pos14_7f4c00*) (action + 0x44) = gm_GameTime;
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (action + 0x52), 0, 1, 0);
		*(int*) (action + 0x84) = cm_SendSetHE(0, action);
	}
}
