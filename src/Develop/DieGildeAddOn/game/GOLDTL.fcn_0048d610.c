#include "Develop/DieGildeAddOn/game/entity_record.h"









extern int g_67e964;
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_772624;

int __cdecl gm_StartFilteredEntitySearch(int a, int b, int c, int d, int id);

/* ADDRESS: GOLDTL 0x0048d610 */
int __cdecl fcn_0048d610(ENTITY_RECORD* e, int* out)
{
	int i;
	int r;

	if (g_67e964 < (*(int*)&gm_GameTime)) {
		g_772624 = 0;
		for (i = 0; i < 768; i++) {
			if (((ENTITY_RECORD*)g_7f4ca0)[i].entity_state == 6 || ((ENTITY_RECORD*)g_7f4ca0)[i].entity_state == 7 || ((ENTITY_RECORD*)g_7f4ca0)[i].entity_state == 5) {
				g_772624++;
			}
		}
		g_67e964 = (*(int*)&gm_GameTime);
	}
	if (e->entity_state == 3) {
		return 0;
	}
	r = gm_StartFilteredEntitySearch(2, 5, 0x1e, 4, e->entity_index);
	if (out) {
		*out = r;
	}
	if (r) {
		return 2;
	}
	if (e->entity_state == 5) {
		return 1;
	}
	if ((e->entity_state == 2 || e->entity_state == 4) && e->unk_00d > 6) {
		return 1;
	}
	return 0;
}
