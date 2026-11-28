#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"

// The second scan indexes g_7f4ca0[i] directly and decrements cnt inside each
// call arm; an entity pointer or a shared decrement moves the strength-reduced
// anchor field and reorders the tail.

#include <string.h>

typedef struct WORKER_RECOVERY_AUX {
	char pad0[0x2c];
	int id;
} WORKER_RECOVERY_AUX;

typedef struct WORKER_RECOVERY_ENTITY {
	unsigned short id;
	unsigned char kind;
	char pad3;
	int seed;
	char pad8[0x81 - 8];
	char pad81[0x82 - 0x81];
	unsigned char b82;
	unsigned char b83;
	char pad84[0x165 - 0x84];
	char active;
	char pad166[0x16c - 0x166];
	char* owner;
	char pad170[0x17c - 0x170];
	char* job;
	int pad180;
	WORKER_RECOVERY_AUX* aux;
	char pad188[0x1b4 - 0x188];
	int flags;
	char pad1b8[0x1c8 - 0x1b8];
	int flags2;
	char pad1cc[0x21c - 0x1cc];
} WORKER_RECOVERY_ENTITY;
// SIZE 0x21c

#pragma pack(push, 2)







typedef struct WORKER_RECOVERY_MSG {
	int pad0;
	unsigned char type;
	char pad5[3];
	int seed;
	int id;
	char pad10[0x28 - 0x10];
	pos14_7f4c00 pos;
	unsigned char flag;
	char pad37[0x58 - 0x37];
	unsigned char mode;
	char pad59[3];
	int target;
	int from;
	char pad64[0xf8 - 0x64];
} WORKER_RECOVERY_MSG;
#pragma pack(pop)

typedef struct WORKER_RECOVERY_UNIT {
	char pad0[0x16c];
	char* info;
} WORKER_RECOVERY_UNIT;

extern char gm_EntitySlotTable[];

extern pos14_7f4c00 gm_GameTime;
#pragma pack(push, 1)
typedef struct WORKER_RECOVERY_RACE {
	char kind;
	char pad1[0x24d - 1];
} WORKER_RECOVERY_RACE;
#pragma pack(pop)

extern unsigned char* lpGebaeudePROT;

char* __cdecl gm_QueryEntities(int a, int b, int c, int d, int e);
void __cdecl cm_SendCopyEntityData(WORKER_RECOVERY_MSG* msg);

void __cdecl ai_DispatchWorkerRecovery(WORKER_RECOVERY_UNIT* meister)
{
	WORKER_RECOVERY_MSG msg;
	char* res;
	int cnt;
	int i;
	BUILDING_PROTOTYPE* race;

	cnt = 2;
	for (i = 0; i < 768; i++) {
		if (((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].id != 0xffff && ((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].owner == meister->info &&
			((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].active
		    && ((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].job != 0 && *((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].job == 0x16) {
			cnt--;
		}
	}
	if (cnt <= 0) {
		return;
	}
	race = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*)meister->info];
	if (((char)race->category) == 4) {
		res = gm_QueryEntities(*(int*)(meister->info + 0x5d), 2, 6, 0, 0x60);
	} else if (((char)race->category) == 0x13) {
		res = gm_QueryEntities(*(int*)(meister->info + 0x5d), 2, 6, 0, 0x145);
	} else {
		res = 0;
	}
	memset(&msg, 0, sizeof(msg));
	msg.type = 0x16;
	msg.seed = ((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[*(unsigned short*)(meister->info + 0x27)].seed;
	msg.id = *(int*)(meister->info + 1);
	msg.pos = (*(pos14_7f4c00*)&gm_GameTime);
	msg.flag = 1;
	if (res != 0) {
		msg.from = *(int*)(res + 2);
	} else {
		msg.from = -1;
	}
	i = 0;
	do {
		if (i >= 768) {
			return;
		}
		if (((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].id != 0xffff
			&& ((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].owner == meister->info
			&& ((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].active
			&& (((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].flags & 0x10)) {
			if (((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].job != 0) {
				if (*((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].job == 0x16) {
					((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].flags &= ~0x10;
				}
			} else if (((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].aux != 0 &&
				((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].aux->id == *(int*)(((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].owner + 1)) {
				if (((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].b83 < ((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].b82) {
					msg.target = ((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].seed;
					msg.mode = 3;
					cm_SendCopyEntityData(&msg);
					cnt--;
				} else {
					msg.target = ((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].seed;
					msg.mode = 2;
					cm_SendCopyEntityData(&msg);
					cnt--;
				}
				((WORKER_RECOVERY_ENTITY*)gm_EntitySlotTable)[i].flags2 |= 4;
			}
		}
		i++;
	} while (cnt > 0);
}
