


#include "Develop/DieGildeAddOn/game/game_data.h"

// SIZE 0x1c
typedef struct {
	int id;
	int pad[6];
} Slot;

int __cdecl d2_FindSelectedListRow(Slot* tbl)
{
	int i;

	if (g_14ce8d8 != 0) {
		for (i = 0; i < 16; i++) {
			if (tbl[i].id != -1 && d2_CurrentElementId == tbl[i].id) {
				return i;
			}
		}
	}
	return -1;
}
