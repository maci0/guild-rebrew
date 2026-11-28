extern char gm_EntityIdField[];
extern char g_85a0a4[];
#include "Develop/DieGildeAddOn/game/game_timestamp.h"
#include <string.h>

#include "Develop/client_types.h"

#pragma pack(2)







#pragma pack()
// SIZE 0xe

extern pos14_7f4c00 gm_GameTime;
extern short gm_GameTimeTailWord;

int __cdecl gm_IsSlotPlayerPerson(int);
void __cdecl cm_SendCopyEntityData(void*);

/* ADDRESS: GOLDTL 0x004b1a90 */
/* ADDRESS: GOLDDE 0x0049fdb0 */
int __cdecl gm_SendPlayerMorningEvents(void)
{
	char msg[0xf8];
	GAME_TIMESTAMP stamp;
	char* rec;
	int n;
	int sent;
	int id;

	stamp = *(GAME_TIMESTAMP*) &gm_GameTime;
	stamp.hour = 0xa;
	stamp.minute = 0;
	sent = 0;
	n = 0;
	rec = (char*) &gm_EntityIdField;
	do {
		if (sent >= 8) {
			break;
		}
		if (gm_IsSlotPlayerPerson(n) != 0) {
			memset(msg, 0, sizeof(msg));
			id = *(int*) rec;
			*(int*) (msg + 8) = id;
			*(int*) (msg + 0xc) = id;
			msg[4] = 0x55;
			msg[0x36] = 9;
			*(GAME_TIMESTAMP*) (msg + 0x28) = stamp;
			cm_SendCopyEntityData(msg);
			sent++;
		}
		n++;
		rec += 0x21c;
	} while ((int) rec < (int) &g_85a0a4);
	return 1;
}
