#include <string.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_77261c;

int __cdecl gm_RandomMod(int);
int __cdecl fcn_005cf720(unsigned short, unsigned short, void*, int);
float __cdecl gm_CalcEntityFavor(unsigned short, unsigned short, int);

/* ADDRESS: GOLDTL 0x004a55c0 */
unsigned int __cdecl gm_FindEntityCandidatesInRange(unsigned short* actor, unsigned int requestedCount, unsigned int* queryFlags,
				  float minimumScore, float maximumScore, unsigned short* outIds)
{
	unsigned int query[20];
	int step;
	int pos;
	unsigned int idx;
	int tries;
	int hit;
	unsigned short id;
	float favor;
	int hasFavorRange;



	step = gm_RandomSearchSteps[gm_RandomMod(0x10) & 0xffff]; idx = 0;
	memset(query, 0, 0x50);
	memset((char*) query + 0x1c, 0xff, 0x20);
	*(int*) ((char*) query + 0x14) = 2; hasFavorRange = 0;
	if (g_77261c != 0) {
		query[1] = *queryFlags;
		if (fcn_005cf720(*actor, *(unsigned short*) g_77261c, query, 0) != 0) {
			idx = 1;
			*outIds = *(unsigned short*) g_77261c;
		}
	}
	if ((minimumScore > 0.0 || maximumScore < 100.0) && minimumScore < maximumScore) {
		hasFavorRange = 1;
	}
	if (idx >= requestedCount) {
		return 1;
	}
	do {
		query[1] = queryFlags[idx];
		if (idx != 0) {
			*(unsigned short*) ((char*) query + 0x1c + idx * 2) = outIds[idx - 1];
		} else {
			*(unsigned short*) ((char*) query + 0x1c) = *actor;
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
			id = *actor;
			if (fcn_005cf720(id, (unsigned short) pos, query, 0) != 0) {
				if (hasFavorRange == 0 ||
				    (favor = gm_CalcEntityFavor((unsigned short) pos, *actor, 1), !(favor < minimumScore) && !(favor > maximumScore))) {
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
