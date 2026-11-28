#include "Develop/DieGildeAddOn/game/ch_script.h"


int __cdecl ch_DestroyCharacter(char* e);

/* ADDRESS: GOLDDE 0x0040b8e0 */
int __cdecl KillCharacter(char** a)
{
	return ch_DestroyCharacter(*a);
}
