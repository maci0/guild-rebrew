


#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl cut_FindFreeCutscene(void)
{
	int a;
	int i;

	i = 0;
	for (a = (int) cut_Cutscenes; a < (int) cut_Cutscenes + 0x6780; a += 0x114) {
		if (*(int*) a == -1) {
			return (char*) ((int) cut_Cutscenes + i * 0x114);
		}
		i++;
	}
	return 0;
}
