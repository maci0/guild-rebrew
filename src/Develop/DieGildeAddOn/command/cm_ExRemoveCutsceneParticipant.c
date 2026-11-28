

int __cdecl cut_FindCutsceneById(int);
#include "Develop/DieGildeAddOn/game/cutscene.h"

/* ADDRESS: GOLDDE 0x004b7780 */
int __cdecl cm_ExRemoveCutsceneParticipant(char* request, char* output)
{
	if (cut_FindCutsceneById(*(int*) (request + 0x10)) == 0) {
		return 1;
	}
	if (cut_RemoveParticipant(*(int*) (request + 0x10), *(int*) (request + 0x14)) == 0) {
		return 1;
	}
	if (output != 0) {
		*output = 1;
	}
	return 0;
}
