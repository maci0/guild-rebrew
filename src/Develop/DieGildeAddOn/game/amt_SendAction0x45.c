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
	char p64[0x94];
} Msg;

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;

void __cdecl cm_SendCopyEntityData(Msg*);

/* ADDRESS: GOLDDE 0x005bc970 */
void __cdecl amt_SendAction0x45(char* owner, char* target, int mode)
{
	Msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.kind = 0x45;
	msg.owner = *(int*) (owner + 4);
	msg.entity = -1;
	msg.timestamp.a = (*(int*)&gm_GameTime);
	msg.timestamp.b = (*(int*)&gm_GameTimeHour);
	msg.timestamp.c = gm_GameTimeSliceDword;
	msg.timestamp.d = gm_GameTimeTailWord;
	msg.flag = 2;
	msg.v58 = *(int*) (owner + 4);
	msg.v5c = *(int*) (target + 4);
	msg.v60 = mode;
	cm_SendCopyEntityData(&msg);
}
