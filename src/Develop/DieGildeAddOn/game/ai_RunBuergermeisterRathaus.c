#include <string.h>

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl gm_FindPublicTreasury(int k);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
int __cdecl gm_GetTypeProductValue(int k);
void __cdecl cm_RequestMoveCredits(int a, int b, char c, int n);
void __cdecl cm_SendCopyEntityData(char* msg);

/* Client dialog record setup: allocates the dialog object (fcn_00507ab0(1)),
 * accepts only type 0xf records on channel 4, clears a 0x3e-dword stack record,
 * fills it with the entity position block (g_7f4c00..g_7f4c0c), the object id
 * and the open flag, then runs the fcn_004c4eb0/fcn_004c5150/fcn_004c5530 chain
 * and returns 0x31. */
/* ADDRESS: GOLDTL 0x0049dc70 */
int __cdecl ai_RunBuergermeisterRathaus(unsigned char* rec, unsigned char* obj, unsigned char* out)
{
	char msg[0xf8];
	char* dialog;

	dialog = gm_FindPublicTreasury(1);
	if (dialog == 0) {
		return 0;
	}
	if (rec[0x166] != 0xf) {
		return 0;
	}
	if (out[0] != 4 && *(int*) (obj + 0x10) != 0) {
		return 0;
	}
	memset(msg, 0, sizeof(msg));
	*(int*) (msg + 8) = *(int*) (rec + 4);
	msg[4] = 0x1e;
	*(int*) (msg + 0xc) = *(int*) (out + 4);
	msg[0x36] = 1;
	*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
	*(int*) (msg + 0x2c) = (*(int*)&gm_GameTimeHour);
	*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
	*(short*) (msg + 0x34) = gm_GameTimeTailWord;
	*(int*) (msg + 0x58) = *(int*) (out + 4);
	cm_SendLogAction((char*) 0x67eb10);
	cm_RequestMoveCredits(-1, *(int*) (dialog + 2), (*(char*)&gm_ActiveTownIndex), (int) (gm_GetTypeProductValue(*(int*) (obj + 4)) * 0.3f));
	cm_SendCopyEntityData(msg);
	cm_SendTraceEnd((char*) 0x67eb10);
	return 0x31;
}
