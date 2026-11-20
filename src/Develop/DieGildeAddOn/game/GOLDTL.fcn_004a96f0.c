#include "entity_record.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"








unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_004a5340(char* e, int n, int* lim, float a4, float r, unsigned short* ids);

/* ADDRESS: GOLDTL 0x004a96f0 */
int __cdecl fcn_004a96f0(int a1, char* e, int a3, int a4, char* out)
{
	int lim;
	unsigned short id;

	if (*(int*) (e + 0x1cc) & 0x80000) {
		return 0;
	}
	lim = 0xf00d00;
	if (!fcn_004a5340(e, 1, &lim, 20.0f, (float) gm_RandomMod(0x20) + 32.0f, &id)) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[id].entity_id;
	return 1;
}
