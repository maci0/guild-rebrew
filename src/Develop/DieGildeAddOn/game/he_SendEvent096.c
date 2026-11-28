#include "Develop/client_types.h"



void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

// SIZE 0xf8
typedef struct {
	int h0;
	unsigned char kind;
	char p5[3];
	int owner;
	int entity;
	char p10[0x18];
	pos14_7f4c00 timestamp;



	unsigned char flag;
	char p37[0x21];
	int v58;
	int v5c;
	char p60[8];
	int v68;
	char p6c[0x8c];
} Msg;

#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;

int __cdecl he_GetActionProgress(char*, int*, int*, int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_SendCopyEntityData(Msg*);

int __cdecl he_SendEvent096(char* e, int* list, int idx)
{
	int x;
	int y;
	Msg msg;

	if (he_GetActionProgress(e, &x, &y, 0) != 0) {
		return 0;
	}
	memset(&msg, 0, sizeof(msg));
	msg.kind = 0x96;
	msg.owner = ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (e + 0x27)].entity_id;
	msg.entity = *(int*) (e + 1);
	msg.timestamp.a = (*(int*)&gm_GameTime);
	msg.timestamp.b = (*(int*)&gm_GameTimeHour);
	msg.timestamp.c = gm_GameTimeSliceDword;
	msg.timestamp.d = gm_GameTimeTailWord;
	msg.flag = 1;
	msg.v5c = list[idx * 2 + 3];
	msg.v58 = list[0];
	msg.v68 = gm_RandomMod(0x5a0) + 1000;
	cm_SendCopyEntityData(&msg);
	return 1;
}
