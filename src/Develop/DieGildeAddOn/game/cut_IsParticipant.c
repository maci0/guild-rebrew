#include "Develop/DieGildeAddOn/game/event_callbacks.h"



void* __cdecl gm_LookupEntityRecordById(int);

/* ADDRESS: GOLDDE 0x004d2a50 */
int __cdecl cut_IsParticipant(int id, unsigned char* cutscene)
{
	int i;

	for (i = 0; i < cutscene[0x30]; i++) {
		if (*(int*) (cutscene + 0x34 + i * 4) == id) {
			if (gm_LookupEntityRecordById(id) != 0) {
				return 1;
			}
			break;
		}
	}
	return 0;
}
