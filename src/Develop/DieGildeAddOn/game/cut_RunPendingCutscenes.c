


extern char gm_EntityIdField[];
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"

int* __cdecl cut_FindLowestIdFlaggedCutscene(void);
#include "Develop/DieGildeAddOn/game/event_callbacks.h"
#include "Develop/DieGildeAddOn/game/cutscene.h"

int __cdecl cm_AppendCommandSyncField(unsigned char, unsigned char, short, void*);
void __cdecl cm_SendSetAttribute(void);

/* ADDRESS: GOLDDE 0x004d3160 */
char __cdecl cut_RunPendingCutscenes(int idx)
{
	char ok;
	int* p;
	int saved;

	ok = 0;
	saved = *(int*) (gm_EntityIdField + idx * 0x21c + 0x208);
	p = cut_FindLowestIdFlaggedCutscene();
	while (p != 0) {
		if (cut_IsParticipant(*(int*) (gm_EntityIdField + idx * 0x21c), (unsigned char*) p) != 0) {
			*(int*) (gm_EntityIdField + idx * 0x21c + 0x208) = *p;
			cut_ExecuteCutscene(p);
			*(int*) (gm_EntityIdField + idx * 0x21c + 0x208) = -1;
			ok = 1;
		}
		cut_FreeCutscene(*p);
		p = cut_FindLowestIdFlaggedCutscene();
	}
	cm_BeginPacketFieldDelta(gm_EntityIdField + idx * 0x21c - 4, *(int*) (gm_EntityIdField + idx * 0x21c));
	cm_AppendCommandSyncField(4, 1, (short) (gm_EntityIdField + idx * 0x21c + 0x208 - cm_PacketDeltaBase), &saved);
	cm_SendSetAttribute();
	return ok;
}
