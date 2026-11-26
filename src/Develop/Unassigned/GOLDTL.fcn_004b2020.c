typedef struct {
	int id;
	int b;
} HST_GROUP_PAIR;

typedef struct {
	int a;
	HST_GROUP_PAIR e[8];
} HST_GROUP_SLOT;
// SIZE 0x44

#include "Develop/DieGildeAddOn/game/game_data.h"


/* ADDRESS: GOLDTL 0x004b2020 */
int __cdecl hst_ResetHistoryGroup(unsigned short g)
{
	int i;

	if (g >= 4)
		return 0;
	((HST_GROUP_SLOT*)g_1007bc0)[g].a = 1;
	for (i = 0; i < 4; i++) {
		((HST_GROUP_SLOT*)g_1007bc0)[g].e[i].id = -1;
		((HST_GROUP_SLOT*)g_1007bc0)[g].e[i].b = 0xffff;
	}
	return 1;
}
