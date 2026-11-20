#include <string.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_77261c;

int __cdecl gm_RandomMod(int);
int __cdecl fcn_005cf720(unsigned short, unsigned short, void*, int);
float __cdecl fcn_0050f980(unsigned short, unsigned short, int);

/* ADDRESS: GOLDTL 0x004a55c0 */
unsigned int __cdecl fcn_004a55c0(unsigned short* a0, unsigned int requestedCount, unsigned int* a2,
				  float minimumScore, float maximumScore, unsigned short* outIds)
{
	unsigned int v12[20];
	int step;
	int pos;
	unsigned int idx;
	int tries;
	int hit;
	unsigned short id;
	float f;
	int flag;



	step = gm_RandomSearchSteps[gm_RandomMod(0x10) & 0xffff]; idx = 0;
	memset(v12, 0, 0x50);
	memset((char*) v12 + 0x1c, 0xff, 0x20);
	*(int*) ((char*) v12 + 0x14) = 2; flag = 0;
	if (g_77261c != 0) {
		v12[1] = *a2;
		if (fcn_005cf720(*a0, *(unsigned short*) g_77261c, v12, 0) != 0) {
			idx = 1;
			*outIds = *(unsigned short*) g_77261c;
		}
	}
	if ((minimumScore > 0.0 || maximumScore < 100.0) && minimumScore < maximumScore) {
		flag = 1;
	}
	if (idx >= requestedCount) {
		return 1;
	}
	do {
		v12[1] = a2[idx];
		if (idx != 0) {
			*(unsigned short*) ((char*) v12 + 0x1c + idx * 2) = outIds[idx - 1];
		} else {
			*(unsigned short*) ((char*) v12 + 0x1c) = *a0;
		}
		tries = 0x300;
		hit = 0;
		pos = gm_RandomMod(0x300) & 0xffff;
		do {
			if (tries == 0) {
				if (hit == 0) {
					return 0;
				}
				break;
			}
			id = *a0;
			if (fcn_005cf720(id, (unsigned short) pos, v12, 0) != 0) {
				if (flag == 0 ||
				    (f = fcn_0050f980((unsigned short) pos, *a0, 1), !(f < minimumScore) && !(f > maximumScore))) {
					hit = 1;
					outIds[idx] = (unsigned short) pos;
				}
			}
			tries--;
			pos = (pos + step) % 0x300;
		} while (hit == 0);
		idx++;
	} while (idx < requestedCount);
	return 1;
}
