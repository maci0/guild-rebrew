#include "Develop/DieGildeAddOn/game/game_data.h"

void* __cdecl fcn_0064f026(int, void*);
int __cdecl atoi(void*);

void __cdecl fcn_0044d580(int a1, char* out)
{
	void* p;

	p = fcn_0064f026(0, (void*) " ");
	*(int*) (out + 4) = atoi(p);
}
