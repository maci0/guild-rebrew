#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_664330;
extern unsigned char gm_ActiveTownIndex;

int __cdecl gm_SumQueryEntryValues(int, unsigned char);

/* ADDRESS: GOLDTL 0x004f0ff0 */
int __cdecl gm_CanFireCannonShot(char* obj, int a1, int a2, int a3, int* out1, int* out2)
{
	int c1;
	int c2;
	int c3;

	c1 = a1;
	c2 = a2;
	c3 = a3;
	if (c1 < 4) {
		if (c1 > 0) {
			c1 = c1;
		} else {
			c1 = 0;
		}
	} else {
		c1 = 4;
	}
	if (c2 < 0x64) {
		if (c2 > 0) {
			c2 = c2;
		} else {
			c2 = 0;
		}
	} else {
		c2 = 0x64;
	}
	if (c3 < 3) {
		if (c3 > 1) {
			c3 = c3;
		} else {
			c3 = 1;
		}
	} else {
		c3 = 3;
	}
	*out1 = c1 + 2;
	*out2 = (int) (((float) c2 * 2.0f + 500.0f) * ((float) c1 * 0.25f + 1.0f)
		* c3 * 32.0f);
	if (*(int*) (obj + 0x194) < *out1) {
		goto fail_0;
	}
	if (gm_SumQueryEntryValues(*(int*) (obj + 0x178), gm_ActiveTownIndex) < *out2) {
		goto fail_0;
	}
	return 1;
fail_0:
	return 0;
}
