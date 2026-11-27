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

extern int* g_665f08;
extern volatile int g_6b7fac;
extern unsigned char* lpGebaeudePROT;

int __cdecl d2_UpdateTutCh1Cat0aStep(int* ev)
{
	if (ev[0] == 0xd && ev[1] != 0 && ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) ev[1]].category == 0xa) {
		((struct fsm*)g_665f08)->state = 0xb;
		((struct fsm*)g_665f08)->next = 0xb;
		((struct fsm*)g_665f08)->since = g_6b7fac;
		return 1;
	}
	return 3;
}
