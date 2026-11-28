#include "Develop/DieGildeAddOn/game/game_data.h"


/* ADDRESS: GOLD 0x004e50a0 */
/* ADDRESS: GOLDTL 0x004e6a30 */
/* ADDRESS: GOLDDE 0x004d3280 */
char* __cdecl cut_FindCutsceneById(int a1)
{
	int i;
	int a;

	for (i = 0, a = (int) cut_Cutscenes; a < (int) cut_Cutscenes + 0x6780; a += 0x114, i++) {
		if (*(char*) (a + 0x30) != 0 && *(int*) a == a1) {
			return (char*) ((int) cut_Cutscenes + i * 276);
		}
	}
	return 0;
}
