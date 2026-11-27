#include <string.h>

#include "client_types.h"
#include "client_actions.h"

extern pos14_7f4c00 gm_GameTime;

void* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl he_StartHandlungSearch(int, ...);
void* __cdecl ahm_GetWorkshopOwner(unsigned char*);

#pragma pack(push, 2)
typedef struct {
	int pad0;
	unsigned char type;
	char pad5[3];
	int seed;
	int id;
	char pad10[0x28 - 0x10];
	pos14_7f4c00 pos;
	unsigned char flag;
	char pad37[0xf8 - 0x37];
} AHM_ACTION_0X98_MSG;
#pragma pack(pop)

void __cdecl cm_SendCopyEntityData(AHM_ACTION_0X98_MSG*);

/* ADDRESS: GOLDTL 0x005473a0 */
void __cdecl he_EnsureAhmAction0x98(void)
{
	AHM_ACTION_0X98_MSG msg;
	char* slot;
	unsigned short* h;

	h = gm_StartFilteredEntitySearch(1, 5, 0x1e);
	if (h == 0) {
		return;
	}
	do {
		if (he_StartHandlungSearch(2, 0, 0x98, 3, *(int*) ((char*) h + 1)) == 0 && (slot = ahm_GetWorkshopOwner((unsigned char*) h)) != 0) {
			memset(&msg, 0, sizeof(msg));
			msg.type = 0x98;
			msg.seed = *(int*) (slot + 4);
			msg.id = *(int*) ((char*) h + 1);
			msg.flag = 2;
			msg.pos = *(pos14_7f4c00*) &gm_GameTime;
			cm_SendCopyEntityData(&msg);
		}
		h = gm_FindNextFilteredEntity();
	} while (h != 0);
}
