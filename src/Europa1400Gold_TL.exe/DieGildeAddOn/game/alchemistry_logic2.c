#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <string.h>
#include "entity.h"

typedef int(__cdecl* dispatch_fn)(unsigned char*);

int __cdecl gm_RandomMod(int range);
void __cdecl gm_AddObjekt(int p1, int p2, int p3);
int __cdecl gm_ObjectsAvailble(int season);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_KillSpieler(unsigned int index, int param);
void* __cdecl gm_NextEntityQueryMatch(void);
extern float g_color_scale;
extern int g_next_object_id;
extern unsigned char g_current_season;
extern float g_const_0_0;

// FUNCTION: GOLDTL 0x4193f0
// SIZE: 144


int __cdecl ahm_AllocateEntitySlot(int obj, int tgt, int src)
{
	int i;
	unsigned short* query;

	for (i = 0; i < 6; i++) {
		if (*(int*) (tgt + 0xc + i * 8) == 0) {
			query = gm_ff_Objekt(*(int*) (src + 0x5d), 2, 6, 0, 0xff);
			*(int*) (obj + 0x14) = g_next_object_id;
			*(int*) (tgt + 0xc + i * 8) = *(int*) (obj + 8);
			*(int*) (tgt + 0x10 + i * 8) = *(int*) (obj + 0x10);
			if (query != 0)
				gm_AddObjekt(*(int*) ((char*) query + 2), *(int*) (obj + 8), 2);
			gm_ObjectsAvailble(g_current_season);
			return 1;
		}
	}
	return 0;
}


/* Clears a slot if it matches a target value. Used during
 * alchemy cleanup to remove specific entity references. */
