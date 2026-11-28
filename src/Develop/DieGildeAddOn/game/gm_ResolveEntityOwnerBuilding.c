#include "Develop/DieGildeAddOn/game/spiel.h"



extern char gm_EntitySlotTable[];



/* ADDRESS: GOLDDE 0x004f81c0 */
short* __cdecl gm_ResolveEntityOwnerBuilding(short* entity)
{
	void* dynamic_ent;

	gm_ResolveEntityById((void**) (&dynamic_ent), (void**) 0, (void**) &entity, *(int*) (entity + 5));
	if (entity == (short*) 0) {
		if (dynamic_ent != (void*) 0 && *(unsigned short*) ((int) dynamic_ent + 0x25) != 0xffff) {
			return (short*) ((char*) gm_EntitySlotTable +
			    (unsigned int) *(unsigned short*) ((int) dynamic_ent + 0x25) * 0x21c);
		}
		entity = (short*) 0;
	}
	return entity;
}
