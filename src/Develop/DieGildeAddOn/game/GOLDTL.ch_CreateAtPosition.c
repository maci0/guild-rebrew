#include "Develop/DieGildeAddOn/game/ch_motion.h"



void* __cdecl ch_Create(void);
void __cdecl ch_DestroyCharacter(void*);

char* __cdecl ch_CreateAtPosition(char* resource, float* position)
{
	char* p;

	p = ch_Create();
	if (ch_CreateMesh(p, resource, position) == 0) {
		ch_DestroyCharacter(p);
		return 0;
	}
	return p;
}
