

int __cdecl cut_FindCutsceneById(int);
#include "Develop/DieGildeAddOn/game/cutscene.h"

int __cdecl fcn_004c9fa0(char* a1, char* a2)
{
	if (cut_FindCutsceneById(*(int*) (a1 + 0x10)) == 0) {
		return 1;
	}
	if (cut_RemoveParticipant(*(int*) (a1 + 0x10), *(int*) (a1 + 0x14)) == 0) {
		return 1;
	}
	if (a2 != 0) {
		*a2 = 1;
	}
	return 0;
}
