#include <string.h>

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;

void __cdecl cm_SendCopyEntityData(char* msg);

/* ADDRESS: GOLDTL 0x0048fa60 */
int __cdecl ai_SendHauchDesVerfalls(char* a1, char* a2, int a3, char* p)
{
	char msg[0xf8];

	memset(msg, 0, sizeof(msg));
	msg[4] = (char) 0x89;
	msg[0x36] = 1;
	*(int*) (msg + 8) = *(int*) (a1 + 4);
	*(int*) (msg + 0xc) = *(int*) (a2 + 1);
	*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
	*(int*) (msg + 0x2c) = (*(int*)&gm_GameTimeHour);
	*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
	*(short*) (msg + 0x34) = gm_GameTimeTailWord;
	*(int*) (msg + 0x5c) = *(int*) (p + 0xc);
	*(int*) (msg + 0x60) = *(int*) (p + 4);
	*(int*) (msg + 0x64) = *(int*) (p + 0x10);
	*(int*) (msg + 0x58) = *(int*) (p + 8);
	*(int*) (msg + 0x38) = *(int*) (p + 4);
	cm_SendCopyEntityData(msg);
	return 0x3d;
}
