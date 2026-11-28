


// SIZE 0x10
struct step {
	int when;
	short dur;
	short pad;
	int arg;
	int msg;
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char g_77e0a0[];
extern char g_776709;
#include "Develop/DieGildeAddOn/game/game_player.h"

extern char* txt_TextEntries[];

int __cdecl he_PostEntityMessage(int, int, char*, unsigned char, int, char*);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDDE 0x00556090 */
void __cdecl he_RunEvent0x83TextQueue(char* u)
{
	int t;

	switch (*(int*) (u + 0x70)) {
	case -2:
	case -1:
		he_FreeAction(u);
		break;
	case 0:
		t = ((struct step*)g_77e0a0)[*(int*) (u + 0xac)].msg;
		if (t != 0 && t != -1 && g_776709 != 0) {
			he_PostEntityMessage(((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, -1, txt_TextEntries[t], 0x40, 0x5f9, 0);
		}
		(*(int*) (u + 0xac))++;
		if (((struct step*)g_77e0a0)[*(int*) (u + 0xac)].msg == 0) {
			*(int*) (u + 0x70) = 1;
			return;
		}
		*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
		*(int*) (u + 0x52) = ((struct step*)g_77e0a0)[*(int*) (u + 0xac)].when;
		*(short*) (u + 0x56) = ((struct step*)g_77e0a0)[*(int*) (u + 0xac)].dur;
		*(int*) (u + 0x58) = ((struct step*)g_77e0a0)[*(int*) (u + 0xac)].arg;
		break;
	}
}
