#include "entity_record.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"









unsigned short __cdecl gm_RandomMod(int n);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
void __cdecl cm_AppendPacketFieldDelta(int a, int b, int c, int* flags);
void __cdecl cm_RequestChangeAttribute(void);

/* ADDRESS: GOLDTL 0x00495890 */
void __cdecl ai_RollNpcActionFlags(void)
{
	int flags;
	int i;

	flags = 1;
	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_type != 3) {
			continue;
		}
		flags |= gm_RandomMod(2) ? 2 : 0;
		flags |= gm_RandomMod(3) ? 4 : 0;
		flags |= gm_RandomMod(3) ? 8 : 0;
		flags |= gm_RandomMod(2) ? 0x10 : 0;
		cm_BeginPacketFieldDelta((char*) ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]), ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_id);
		cm_AppendPacketFieldDelta(4, 1, 0x1e8, &flags);
		cm_RequestChangeAttribute();
	}
}
