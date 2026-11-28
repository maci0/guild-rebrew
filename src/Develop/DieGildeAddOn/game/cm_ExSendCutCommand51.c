


#include <string.h>

#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntityIdField[];
#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
int* __cdecl gm_FindOrCreateEntitySlot(char*, char*);

/* ADDRESS: GOLDDE 0x004ba5d0 */
int __cdecl cm_ExSendCutCommand51(char* x, char* out)
{
	int i;
	int* d;

	if (*(int*) (x + 0x40) != *(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c + 0x208))
		return 1;
	for (i = 0; i < 16; i++) {
		if (*(int*) (cut_ParticipantSlots + i * 0x35c + 0x10) == *(int*) (x + 0x10)) {
			d = gm_FindOrCreateEntitySlot(cut_ParticipantSlots + i * 0x35c, gm_LookupEntityRecordIn32SlotTable(*(int*) (x + 0x14)));
			if (d[1] == *(int*) (x + 0x18) && (d[1] != 2 || d[4] == *(int*) (x + 0x24)))
				memcpy(d, x + 0x14, 0x2c);
			break;
		}
	}
	if (out != 0) {
		out[0] = 1;
		out[1] = 8;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
