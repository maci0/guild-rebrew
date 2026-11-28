





// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl he_StartHandlungSearch(int, int, int, ...);

/* ADDRESS: GOLDDE 0x0054b440 */
void __cdecl he_InitMeisterpruefungPassed(char* action)
{
	char* found;

	gm_LookupEntityRecordById(*(int*) (action + 0xac));
	found = he_StartHandlungSearch(2, 2, *(unsigned short*) (action + 8), 0, 0x25);
	if (found != 0) {
		*(int*) (found + 0x70) = -1;
	}
	*(pos14_7f4c00*) (action + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
}
