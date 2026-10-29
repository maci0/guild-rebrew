#include "Develop/DieGildeAddOn/game/ch_motion.h"



void* __cdecl ch_Create(void);
void __cdecl fcn_004030e0(void*);

char* __cdecl fcn_00403b90(char* a1, float* a2)
{
	char* p;

	p = ch_Create();
	if (ch_CreateMesh(p, a1, a2) == 0) {
		fcn_004030e0(p);
		return 0;
	}
	return p;
}
