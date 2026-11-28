#include "Develop/DieGildeAddOn/game/building_prototype.h"


// SIZE 0x10
struct fsm {
	int state;
	int next;
	int pad8;
	int since;
};

#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad[0x24c];
};
#pragma pack()

extern int* d2_TutorialState;
extern volatile int gm_GameTicks;
extern unsigned char* lpGebaeudePROT;

/* ADDRESS: GOLDDE 0x00564e00 */
int __cdecl d2_UpdateTutCh1Cat0aStep(int* ev)
{
	if (ev[0] == 0xd && ev[1] != 0 && ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) ev[1]].category == 0xa) {
		((struct fsm*)d2_TutorialState)->state = 0xb;
		((struct fsm*)d2_TutorialState)->next = 0xb;
		((struct fsm*)d2_TutorialState)->since = gm_GameTicks;
		return 1;
	}
	return 3;
}
