#include <string.h>

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;

void __cdecl gm_ModifyHealth(int id, int amount);
void __cdecl cm_SendCopyEntityData(char* msg);

/* ADDRESS: GOLDTL 0x004abd80 */
/* ADDRESS: GOLDDE 0x0049a0c0 */
int __cdecl ai_RunTheater(char* actor, char* x)
{
	char msg[0xf8];

	gm_ModifyHealth(*(int*) (actor + 4), -*(int*) (x + 0x10));
	memset(msg, 0, sizeof(msg));
	msg[4] = (char) 0xa0;
	*(int*) (msg + 8) = *(int*) (actor + 4);
	*(int*) (msg + 0xc) = *(int*) (x + 4);
	*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
	*(int*) (msg + 0x2c) = (*(int*)&gm_GameTimeHour);
	*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
	*(short*) (msg + 0x34) = gm_GameTimeTailWord;
	msg[0x36] = 2;
	*(int*) (msg + 0x58) = *(int*) (x + 0xc);
	cm_SendCopyEntityData(msg);
	return 0x46;
}
