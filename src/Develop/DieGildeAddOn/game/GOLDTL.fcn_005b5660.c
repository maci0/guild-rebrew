#include "g_6abb08.h"

extern Offer g_6abb08[];
extern int g_6ac240;

unsigned short __cdecl gm_RandomMod(unsigned short);

/* ADDRESS: GOLDTL 0x005b5660 */
unsigned short __cdecl fcn_005b5660(int count, unsigned short* ids)
{
	int idx;
	int i;
	int tries;
	Offer* o;

	idx = gm_RandomMod(g_6ac240);
	for (tries = g_6ac240; tries != 0; tries--) {
		o = &g_6abb08[idx];
		i = 0;
		while (i < count && ids[i] != o->id) {
			i++;
		}
		if (i >= count) {
			return (unsigned short) o->id;
		}
		idx = (idx + 1) % g_6ac240;
	}
	return 0;
}
