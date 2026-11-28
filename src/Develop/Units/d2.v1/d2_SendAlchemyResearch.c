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
	int v60;
	int v64;
	int v68;
	char p6c[0x8c];
} Msg;

extern char gm_EntitySlotTable[];
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;

int __cdecl he_GetActionProgress(char*, int*, int*, int);
void __cdecl cm_SendCopyEntityData(Msg*);

int __cdecl d2_SendAlchemyResearch(char* e, int* list)
{
	int x;
	int y;
	Msg msg;

	if (he_GetActionProgress(e, &x, &y, 0) != 0) {
		return 0;
	}
	memset(&msg, 0, sizeof(msg));
	msg.kind = 0x95;
	msg.owner = *(int*) (gm_EntitySlotTable + *(unsigned short*) (e + 0x27) * 540 + 4);
	msg.entity = *(int*) (e + 1);
	msg.timestamp.a = (*(int*)&gm_GameTime);
	msg.timestamp.b = (*(int*)&gm_GameTimeHour);
	msg.timestamp.c = gm_GameTimeSliceDword;
	msg.timestamp.d = gm_GameTimeTailWord;
	msg.flag = 1;
	msg.v58 = *list;
	msg.v64 = *list;
	cm_SendCopyEntityData(&msg);
	return 1;
}
