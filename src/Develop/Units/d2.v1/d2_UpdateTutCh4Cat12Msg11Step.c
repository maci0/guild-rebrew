#include "Develop/DieGildeAddOn/game/building_prototype.h"


// SIZE 0x3c
struct fsm {
	int state;
	int next;
	int pad8;
	int since;
	char pad10[0x28];
	int flag;
};

#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad[0x24c];
};

// SIZE 0x29
struct item {
	unsigned char good;
	char pad1[0x26];
	unsigned short owner;
};
#pragma pack()

extern int* d2_TutorialState;
extern volatile int gm_GameTicks;
extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"

int __cdecl d2_UpdateTutCh4Cat12Msg11Step(int* ev)
{
	struct item* p;

	if (ev[0] == 0x2b && (p = (struct item*) ev[1]) != 0) {
		if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[p->good].category == 0x12 && p->owner == gm_LocalPlayerSlot && (*(struct fsm**)&d2_TutorialState)->flag == 0
		    && (ev[3] == 0x79 || ev[3] == 0x7a || ev[3] == 0x78)) {
			(*(struct fsm**)&d2_TutorialState)->flag = 1;
			(*(struct fsm**)&d2_TutorialState)->next = 0xa;
			(*(struct fsm**)&d2_TutorialState)->state = (*(struct fsm**)&d2_TutorialState)->next;
			(*(struct fsm**)&d2_TutorialState)->since = gm_GameTicks;
		}
	} else if (ev[0] == 0x11 && (p = (struct item*) ev[1]) != 0) {
		if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[p->good].category == 0x12 && p->owner == gm_LocalPlayerSlot) {
			if (ev[2] == 0 && (*(struct fsm**)&d2_TutorialState)->flag == 0) {
				(*(struct fsm**)&d2_TutorialState)->next = 9;
			}
			if (ev[2] == 1) {
				if ((*(struct fsm**)&d2_TutorialState)->flag == 1) {
					(*(struct fsm**)&d2_TutorialState)->next = 0xb;
				} else {
					(*(struct fsm**)&d2_TutorialState)->next = 4;
				}
			}
			(*(struct fsm**)&d2_TutorialState)->state = (*(struct fsm**)&d2_TutorialState)->next;
			(*(struct fsm**)&d2_TutorialState)->since = gm_GameTicks;
			return 1;
		}
	}
	return 3;
}
