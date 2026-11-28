#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/game_player.h"

#pragma pack(2)
// SIZE 0xe






#pragma pack()


extern pos14_7f4c00 gm_GameTime;

// SIZE 0xf8
struct ACTION_MSG {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad3[0xc1];
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"










#include <string.h>

int __cdecl he_StartHandlungSearch(int, int, int);
void __cdecl cm_SendCopyEntityData(struct ACTION_MSG*);

void __cdecl he_EnsureAction0x6d(void)
{
	struct ACTION_MSG m;

	if (he_StartHandlungSearch(1, 0, 0x6d) == 0) {
		memset(&m, 0, sizeof(m));
		m.b4 = 0x6d;
		m.fc = -1;
		m.b36 = 2;
		m.f8 = ((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id;
		m.pos = (*(pos14_7f4c00*)&gm_GameTime);
		cm_SendCopyEntityData(&m);
	}
}
