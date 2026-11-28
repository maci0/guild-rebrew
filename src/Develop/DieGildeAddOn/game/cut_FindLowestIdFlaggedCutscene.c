


typedef struct
{
	int id;
	char pad4[4];
	unsigned char type;
	char pad9[0xb];
	int key;
	char pad18[0xe];
	unsigned char flags;
	char pad27[9];
	char active;
	char pad31[3];
	int list[16];
	char tail[0xa0];
} Ent114;
// SIZE 0x114

#include "Develop/DieGildeAddOn/game/game_data.h"

void* __cdecl cut_FindCutsceneById(unsigned int);

/* ADDRESS: GOLDDE 0x004d3120 */
void* __cdecl cut_FindLowestIdFlaggedCutscene(void)
{
	unsigned int best;
	int i;

	best = (unsigned int) -1;
	for (i = 0; i < 96; i++) {
		if (((Ent114*)cut_Cutscenes)[i].active != 0 && ((Ent114*)cut_Cutscenes)[i].id != -1 && (((Ent114*)cut_Cutscenes)[i].flags & 1) != 0 &&
		    best >= (unsigned int) ((Ent114*)cut_Cutscenes)[i].id) {
			best = ((Ent114*)cut_Cutscenes)[i].id;
		}
	}
	if (best != (unsigned int) -1) {
		return cut_FindCutsceneById(best);
	}
	return 0;
}
