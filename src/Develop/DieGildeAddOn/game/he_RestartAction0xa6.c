#include "Develop/DieGildeAddOn/game/game_player.h"

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"










char* __cdecl he_StartHandlungSearch(int, int, int, ...);
void __cdecl he_FreeAction(char*);
void __cdecl cm_SendCopyEntityData(struct msg*);

/* ADDRESS: GOLDDE 0x0052f790 */
void __cdecl he_RestartAction0xa6(void)
{
	struct msg req_msg;
	char* existing;

	existing = he_StartHandlungSearch(1, 0, 0xa6);
	if (existing != 0) {
		he_FreeAction(existing);
	}
	req_msg.b4 = (char) 0xa6;
	req_msg.fc = -1;
	req_msg.b36 = 1;
	req_msg.f8 = ((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot])->entity_id;
	req_msg.pos = gm_GameTime;
	cm_SendCopyEntityData(&req_msg);
}
