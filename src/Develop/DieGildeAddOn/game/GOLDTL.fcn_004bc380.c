


#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"









extern char g_681414[];
extern char g_68140c[];

char* __cdecl fcn_004bca30(char*);
void __cdecl d3_TransformPoint(char*, char*, float*);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl ch_CreateAction(char*, int, int);

void __cdecl ch_SpawnAmbientCow(AMBIENT_ANIMAL_SLOT* s)
{
	float v[4];
	char* o;

	o = fcn_004bca30(g_681414);
	if (o == 0)
		return;
	d3_TransformPoint(o, o + 0x4c, v);
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
	ch_CreateAction(s->objekt, 0x38, 1);
}
