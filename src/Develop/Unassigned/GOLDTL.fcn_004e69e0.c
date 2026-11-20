


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

Ent114* __cdecl cut_FindCutscene(int type, int key)
{
	int i;

	for (i = 0; i < 96; i++) {
		if (((Ent114*)cut_Cutscenes)[i].active != 0 && ((Ent114*)cut_Cutscenes)[i].type == type && ((Ent114*)cut_Cutscenes)[i].key == key) {
			return &((Ent114*)cut_Cutscenes)[i];
		}
	}
	return 0;
}
