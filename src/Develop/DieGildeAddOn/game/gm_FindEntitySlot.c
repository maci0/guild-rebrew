


typedef struct
{
	int id;
	char pad[0x28];
} Slot2c;
// SIZE 0x2c

typedef struct
{
	char head[0x94];
	Slot2c slots[16];
	char tail[8];
} Player35c;
// SIZE 0x35c

#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDDE 0x004bc2e0 */
Slot2c* __cdecl gm_FindEntitySlot(char* entity)
{
	int n;
	int i;
	int j;
	Player35c* p;

	n = *(unsigned char*) (g_772eb4 + 0x30);
	for (i = 0; i < n; i++) {
		p = &((Player35c*)cut_ParticipantSlots)[i];
		for (j = 0; j < 16; j++) {
			if (p->slots[j].id == *(int*) (entity + 4)) {
				return &p->slots[j];
			}
		}
	}
	return 0;
}
