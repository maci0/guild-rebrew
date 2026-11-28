#include "Develop/DieGildeAddOn/game/entity_record.h"








void __cdecl d3snd_PlayObjectClickSound(ENTITY_RECORD*);


/* ADDRESS: GOLD 0x004c2ce0 */
/* ADDRESS: GOLDTL 0x004c35b0 */
void __cdecl d3snd_PlaySelectedObjectClickSound(void)
{
	int i;

	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].selected != 0) {
			d3snd_PlayObjectClickSound(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]));
			return;
		}
	}
}
