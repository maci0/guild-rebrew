#include <string.h>

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;

void __cdecl cm_SendCopyEntityData(char* msg);

/* ADDRESS: GOLDTL 0x0048f850 */
/* ADDRESS: GOLDDE 0x0047e720 */
int __cdecl ai_SendNecromancerFog(char* actor, char* home, int req, char* plan)
{
	char msg[0xf8];

	memset(msg, 0, sizeof(msg));
	msg[4] = (char) 0x90;
	msg[0x36] = 2;
	*(int*) (msg + 8) = *(int*) (actor + 4);
	*(int*) (msg + 0xc) = *(int*) (home + 1);
	*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
	*(int*) (msg + 0x2c) = (*(int*)&gm_GameTimeHour);
	*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
	*(short*) (msg + 0x34) = gm_GameTimeTailWord;
	*(int*) (msg + 0x5c) = *(int*) (plan + 4);
	*(int*) (msg + 0x60) = *(int*) (plan + 8);
	*(int*) (msg + 0x58) = *(int*) (plan + 0xc);
	cm_SendCopyEntityData(msg);
	return 0x3d;
}
