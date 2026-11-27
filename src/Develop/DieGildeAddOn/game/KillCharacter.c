#include "Develop/DieGildeAddOn/game/ch_script.h"


int __cdecl ch_DestroyCharacter(char* e);

int __cdecl KillCharacter(char** a)
{
	return ch_DestroyCharacter(*a);
}
