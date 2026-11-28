#include "Develop/DieGildeAddOn/game/game_data.h"



extern int* d2_TutorialState;

void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(void*);

/* ADDRESS: GOLDDE 0x00565e80 */
int __cdecl d2_ClearTutorialText(void)
{
	char* p;

	p = *(char**) ((int) d2_TutorialState + 0x1c);
	if (p == 0) {
		return -4;
	}
	p = *(char**) (p + 0x74);
	if (p == 0) {
		return -4;
	}
	d2_SetForm(*(int*) (p + 8), 1);
	io_AppendText((void*) str_dollar_C);
	d2_SetForm(*(int*) (*(int*) (*(int*) ((int) d2_TutorialState + 0x1c) + 0x74) + 8), 2);
	io_AppendText((void*) str_dollar_C);
	return 0;
}
