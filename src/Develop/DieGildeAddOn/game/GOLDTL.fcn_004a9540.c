#include "entity_record.h"









unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_004a5340(char* e, int n, int* lim, float a4, float r, unsigned short* ids);
int __cdecl fcn_0055c0f0(char* e, ENTITY_RECORD* t);

/* ADDRESS: GOLDTL 0x004a9540 */
int __cdecl fcn_004a9540(int a1, char* e, int a3, int a4, char* out)
{
	int lim;
	unsigned short id;

	if (*(int*) (e + 0x194) < 2) {
		return 0;
	}
	lim = 0xf00500;
	if (!fcn_004a5340(e, 1, &lim, 0.0f, (float) gm_RandomMod(0x20) + 40.0f, &id)) {
		return 0;
	}
	if (!fcn_0055c0f0(e, &((ENTITY_RECORD*)g_7f4ca0)[id])) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = ((ENTITY_RECORD*)g_7f4ca0)[id].entity_id;
	return 1;
}
