#include "Develop/DieGildeAddOn/game/ch_script.h"



extern char* evt_CurrentScript;
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

char* __cdecl CreateCharacter(char** a, float* b, float* c, float* d)
{
	float v[4];
	char* o;

	v[0] = *b;
	v[1] = *c;
	v[2] = *d;
	o = ch_CreateAtPosition(*a, v);
	if (o == 0) {
		fcn_00425bf0(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "object not created");
	} else {
		*(int*) (o + 0x30) = *(int*) (evt_CurrentScript + 0x104);
	}
	return o;
}
