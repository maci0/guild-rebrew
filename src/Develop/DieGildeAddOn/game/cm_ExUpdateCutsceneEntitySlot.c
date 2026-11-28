


#include <string.h>

#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntityIdField[];
#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
char* __cdecl gm_LookupEntityRecordById(int);
int* __cdecl gm_FindOrCreateEntitySlot(char*, char*);

/* ADDRESS: GOLDDE 0x004ba510 */
int __cdecl cm_ExUpdateCutsceneEntitySlot(char* x, char* out)
{
	int i;
	char* e;
	int* d;
	char* rec;
	int* src;

	if (*(int*) (x + 0x40) != *(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c + 0x208))
		return 1;
	for (i = 0; i < 16; i++) {
		if (*(int*) (cut_ParticipantSlots + i * 0x35c + 0x10) == *(int*) (x + 0x10)) {
			rec = cut_ParticipantSlots + i * 0x35c;
			src = (int*) (x + 0x14);
			e = gm_LookupEntityRecordIn32SlotTable(*src);
			if (e == 0) {
				e = gm_LookupEntityRecordById(*src);
				if (e == 0)
					break;
			}
			d = gm_FindOrCreateEntitySlot(rec, e);
			memcpy(d, src, 0x2c);
			if (d[1] == 0)
				d[0] = -1;
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
