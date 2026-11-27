#include <string.h>

typedef struct {

	int tag;
	int obj;
	int id;
	int xc;
	float f;
	int x14;
} Msg18F;

extern float g_6628a8;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl ahm_CheckFlag(void* p);
int __cdecl ahm_FindRecipeSlot(void* p, int id);
int __cdecl cm_RequestAhmCommand(void* m);

/* ADDRESS: GOLDTL 0x004eea30 */
int __cdecl ahm_RequestSetMatchingSlotValue(void* obj, int id, float fraction)
{
	Msg18F m;

	if (ahm_CheckFlag(obj) == 0) {
		return -1;
	}
	if (ahm_FindRecipeSlot(obj, id) == 0) {
		return -1;
	}
	memset(&m, 0, sizeof(m));
	m.tag = 0x61535263;
	m.obj = *(int*) ((char*) obj + 4);
	m.id = id;
	if (fraction > 0.0f) {
		if (fraction < 1.0f) {
			m.f = fraction;
			return cm_RequestAhmCommand(&m);
		}
	} else {
		m.f = 0.0f;
		return cm_RequestAhmCommand(&m);
	}
	m.f = 1.0f;
	return cm_RequestAhmCommand(&m);
}
