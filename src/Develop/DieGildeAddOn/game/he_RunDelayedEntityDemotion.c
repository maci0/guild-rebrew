


#include <string.h>

// SIZE 0xf8
#include "Develop/client_types.h"
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	pos14_7f4c00 when;
	unsigned char code;
	char pad37[0x21];
	int who;
	char pad5c[0x9c];
};

extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_SendCopyEntityData(struct msg*);
void __cdecl cm_RequestSetEntityLevel(int, int);
void __cdecl he_FreeAction(char*);

void __cdecl he_RunMeisterpruefungFinish(char* action)
{
	struct msg msg;
	char* entity;

	switch (*(int*) (action + 0x70)) {
	case -2:
	case -1:
		he_FreeAction(action);
		break;
	case 0:
		(*(int*) (action + 0xb8))--;
		entity = gm_LookupEntityRecordById(*(int*) (action + 0xac));
		if (*(int*) (action + 0xb8) < 0 && entity != 0) {
			if (entity[2] == 6 || entity[2] == 7) {
				memset(&msg, 0, sizeof(msg));
				msg.kind = 0x26;
				msg.target = -1;
				msg.code = 9;
				msg.owner = *(int*) (action + 0xac);
				msg.when = gm_GameTime;
				msg.who = *(int*) (action + 0xac);
				cm_SendCopyEntityData(&msg);
			}
			cm_RequestSetEntityLevel(*(int*) (entity + 4), *(unsigned char*) (entity + 0x164) - 1);
			he_FreeAction(action);
		}
		break;
	}
}
