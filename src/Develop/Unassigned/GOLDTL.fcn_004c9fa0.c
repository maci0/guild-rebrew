

int __cdecl cut_FindCutsceneById(int);
#include "Develop/DieGildeAddOn/game/cutscene.h"

int __cdecl fcn_004c9fa0(char* request, char* output)
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
