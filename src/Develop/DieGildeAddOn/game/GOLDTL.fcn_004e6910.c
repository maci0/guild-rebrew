


extern char g_7f4ca4[];
#include "client_packet_builder.h"

int* __cdecl cut_FindLowestIdFlaggedCutscene(void);
#include "Develop/DieGildeAddOn/game/event_callbacks.h"
#include "Develop/DieGildeAddOn/game/cutscene.h"

int __cdecl fcn_004c4700(unsigned char, unsigned char, short, void*);
void __cdecl fcn_004c53a0(void);

char __cdecl cut_RunPendingCutscenes(int idx)
{
	char ok;
	int* p;
	int saved;

	ok = 0;
	saved = *(int*) (g_7f4ca4 + idx * 0x21c + 0x208);
	p = cut_FindLowestIdFlaggedCutscene();
	while (p != 0) {
		if (cut_IsParticipant(*(int*) (g_7f4ca4 + idx * 0x21c), (unsigned char*) p) != 0) {
			*(int*) (g_7f4ca4 + idx * 0x21c + 0x208) = *p;
			cut_ExecuteCutscene(p);
			*(int*) (g_7f4ca4 + idx * 0x21c + 0x208) = -1;
			ok = 1;
		}
		cut_FreeCutscene(*p);
		p = cut_FindLowestIdFlaggedCutscene();
	}
	cm_BeginPacketFieldDelta(g_7f4ca4 + idx * 0x21c - 4, *(int*) (g_7f4ca4 + idx * 0x21c));
	fcn_004c4700(4, 1, (short) (g_7f4ca4 + idx * 0x21c + 0x208 - g_aed32c), &saved);
	fcn_004c53a0();
	return ok;
}
