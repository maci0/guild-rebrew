#include "Develop/DieGildeAddOn/game/spiel.h"
// FUNCTION: GOLDTL 0x0050d4f0



unsigned short __cdecl fcn_0050d4f0(short* entity)
{
	void* dynamic_ent;

	gm_ResolveEntityById((void**) (&dynamic_ent), (void**) 0, (void**) &entity, *(int*) (entity + 5));
	if (entity != (short*) 0) {
		return *entity;
	}
	if (dynamic_ent != (void*) 0) {
		return *(unsigned short*) ((int) dynamic_ent + 0x25);
	}
	return (short) 0xffff;
}
