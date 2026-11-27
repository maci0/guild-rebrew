


#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"









extern char g_6813e8[];

int __cdecl gm_PickRandomBuildingPoint(float*);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl ch_CreateAction(char*, int, int);

void __cdecl ch_SpawnAmbientDog(AMBIENT_ANIMAL_SLOT* s)
{
	float v[4];

	if (gm_PickRandomBuildingPoint(v) == 0)
		return;
	s->objekt = ch_CreateAtPosition(g_6813e8, v);
	if (s->objekt == 0)
		return;
	*(float*) (s->objekt + 0x1a0) = 1.0f;
	s->pos[0] = v[0];
	s->pos[1] = v[1];
	s->pos[2] = v[2];
	s->kind = 0;
	*(int*) (s->objekt + 4) = 2;
	*(int*) (*(char**) (s->objekt + 0x34) + 0x224) = 0;
	ch_CreateAction(s->objekt, 0x38, 1);
}
