


#include "Develop/DieGildeAddOn/game/entity_record.h"






#include "Develop/DieGildeAddOn/game/game_player.h"


char* __cdecl fcn_00502cd0(int, int, int, int);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
void __cdecl d2_RunStammtischDialog(char*, char*);
void __cdecl fcn_005a2080(char*, char*);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005a2500(char* a, char* b)
{
	char* e;

	e = fcn_00502cd0(*(int*) (b + 0x14), 1, 0, 0x12d);
	if (e != 0 && he_StartHandlungSearch(2, 0, 0x2a, 3, *(int*) (a + 1)) != 0) {
		if (((ENTITY_RECORD*)g_7f4ca0)[g_774970].entity_index == *(unsigned short*) (a + 0x27)) {
			d2_RunStammtischDialog(a, e);
		}
		else {
			fcn_005a2080(a, e);
		}
	}
	fcn_00532ef0();
}
