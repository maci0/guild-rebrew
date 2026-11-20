#include "Develop/DieGildeAddOn/game/entity_record.h"








void __cdecl fcn_004c3540(ENTITY_RECORD*);


/* ADDRESS: GOLD 0x004c2ce0 */
/* ADDRESS: GOLDTL 0x004c35b0 */
void __cdecl fcn_004c35b0(void)
{
	int i;

	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].selected != 0) {
			fcn_004c3540(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]));
			return;
		}
	}
}
