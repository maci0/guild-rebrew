typedef struct Stat {
	int v[9];
} Stat;
// SIZE 0x24

typedef struct Ent {
	char pad0[0xac];
	float mood;
	char padb0[0x164 - 0xb0];
	unsigned char job;
} Ent;
// SIZE 0x165

void __cdecl gm_GetLawEntry(int a, Stat* st);
#include "Develop/DieGildeAddOn/game/spiel.h"

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x004910e0 */
int __cdecl ai_EvaluateLaw0x0c(Ent* entity, int unused, int* out)
{
	Stat st;
	int range;
	int difference;

	range = gm_MapEntityStatRange(entity->job);
	if ((*(int*)&gm_GameTime) < 4) {
		return 0;
	}
	gm_GetLawEntry(0xc, &st);
	difference = st.v[2] - st.v[1];
	if (range == 8) {
		if (st.v[6] > (int) (difference * 0.33f + st.v[1])) {
			*out = st.v[1] + gm_RandomMod(3);
			return 1;
		}
	} else {
		if (st.v[6] < (int) (difference * 0.66f + st.v[1])) {
			*out = st.v[2] - gm_RandomMod(3);
			return 1;
		}
	}
	return 0;
}
