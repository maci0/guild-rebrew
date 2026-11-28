typedef struct {
	int id;
	int b;
} HST_GROUP_SLOT_PAIR;

typedef struct {
	int a;
	HST_GROUP_SLOT_PAIR e[8];
} HST_GROUP_SLOT_DESC;
// SIZE 0x44

#include "Develop/DieGildeAddOn/game/game_data.h"


/* ADDRESS: GOLDTL 0x004ae0f0 */
int __cdecl hst_IsCandidateUnlisted(int id)
{
	int j;
	int i;

	for (j = 0; j < 4; j++) {
		for (i = 0; i < 8; i++) {
			if (((HST_GROUP_SLOT_DESC*)hst_HistoryGroups)[j].e[i].id == id)
				return 0;
		}
	}
	return 1;
}
