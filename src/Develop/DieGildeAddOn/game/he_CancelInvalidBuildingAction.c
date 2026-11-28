


// SIZE 0x14c
#include "Develop/client_types.h"
struct unit {
	unsigned char kind;
	char pad1[7];
	unsigned short house;
	char pada[2];
	int owner;
	char pad10[0x42];
	pos14_7f4c00 dest;
	char pad60[0x10];
	int state;
	char pad74[0xd8];
};

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	unsigned char active;
	char pad9[0x213];
};

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl he_CancelInvalidBuildingAction(struct unit* u)
{
	if (u->house == 0xffff) {
		return;
	}
	if ((*(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[u->house].entity_id) == u->owner && (*(unsigned char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[u->house].entity_type) != 0xf) {
		if ((*(unsigned char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[u->house].health) > 0) {
			return;
		}
		switch (u->kind) {
		case 0x16:
		case 0x18:
		case 0x19:
		case 0x1a:
		case 0x2d:
		case 0x2e:
		case 0x2f:
		case 0x35:
		case 0x36:
		case 0x37:
		case 0x38:
		case 0x41:
		case 0x45:
		case 0x46:
		case 0x47:
		case 0x4a:
		case 0x4b:
		case 0x5e:
		case 0x5f:
		case 0x60:
		case 0x69:
		case 0x6a:
		case 0x6f:
		case 0x7e:
			break;
		default:
			return;
		}
	}
	u->state = -2;
	u->dest = gm_GameTime;
}
