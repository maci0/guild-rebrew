#include "Develop/client_types.h"



void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

// SIZE 0x114
typedef struct {
	int h0;
	int h4;
	unsigned char kind;
	char p9[3];
	int owner;
	int h10;
	int target;
	pos14_7f4c00 timestamp;



	unsigned char flags;
	char p27[9];
	unsigned char count;
	char p31[3];
	int ids[56];
} Msg;

extern char gm_EntitySlotTable[];
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;

int __cdecl amt_ProcessOfficeElections(void);
void __cdecl cm_EnqueueStagedPacket(Msg*);

/* ADDRESS: GOLDDE 0x00565cc0 */
void __cdecl d2_SendTutorialTownMsgA0(int a)
{
	Msg msg;
	int i;
	unsigned int n;
	char t;

	if (a == 0 && amt_ProcessOfficeElections() != 0) {
		memset(&msg, 0, sizeof(msg));
		n = 0;
		for (i = 0; i < 768; i++) {
			t = gm_EntitySlotTable[i * 540 + 2];
			if (t == 6) {
				msg.owner = *(int*) (gm_EntitySlotTable + i * 540 + 4);
				msg.ids[n] = *(int*) (gm_EntitySlotTable + i * 540 + 4);
				n++;
			}
			else if (t == 7) {
				msg.ids[n] = *(int*) (gm_EntitySlotTable + i * 540 + 4);
				n++;
			}
		}
		msg.count = (unsigned char) n;
		msg.kind = 1;
		msg.flags = 0xa0;
		msg.target = -1;
		msg.timestamp.a = (*(int*)&gm_GameTime);
		msg.timestamp.b = (*(int*)&gm_GameTimeHour);
		msg.timestamp.c = gm_GameTimeSliceDword;
		msg.timestamp.d = gm_GameTimeTailWord;
		cm_EnqueueStagedPacket(&msg);
	}
}
