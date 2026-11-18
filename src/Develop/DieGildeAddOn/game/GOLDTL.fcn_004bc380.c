


#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"









extern char g_681414[];
extern char g_68140c[];

char* __cdecl fcn_004bca30(char*);
void __cdecl fcn_00455350(char*, char*, float*);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl fcn_0040c120(char*, int, int);

void __cdecl fcn_004bc380(AMBIENT_ANIMAL_SLOT* s)
{
	float v[4];
	char* o;

	o = fcn_004bca30(g_681414);
	if (o == 0)
		return;
	fcn_00455350(o, o + 0x4c, v);
	s->objekt = ch_CreateAtPosition(g_68140c, v);
	if (s->objekt == 0)
		return;
	*(float*) (s->objekt + 0x1a0) = 1.5f;
	s->pos[0] = v[0];
	s->pos[1] = v[1];
	s->pos[2] = v[2];
	s->kind = 3;
	*(int*) (s->objekt + 4) = 2;
	*(int*) (*(char**) (s->objekt + 0x34) + 0x224) = 0;
	fcn_0040c120(s->objekt, 0x38, 1);
}
