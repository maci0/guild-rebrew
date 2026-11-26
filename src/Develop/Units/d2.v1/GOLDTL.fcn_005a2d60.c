


#include "Develop/DieGildeAddOn/game/game_player.h"

char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_005a2580(char*, char*, char*);
void __cdecl d2_ShowDunkleEcke(char*, char*);
void __cdecl fcn_00532ef0(void);

void __cdecl d2_OpenDunkleEcke(char* building, char* context)
{
	char* entry;

	entry = fcn_00502cd0(*(int*) (context + 0x14), 1, 0, 0x12c);
	if (entry != 0) {
		if (*(unsigned short*) (building + 0x27) == g_774970) {
			fcn_005a2580(building, context, entry);
		}
		else {
			d2_ShowDunkleEcke(building, entry);
		}
	}
	fcn_00532ef0();
}
