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

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x00491270 */
int __cdecl ai_EvaluateLaw0x0e(Ent* entity, int unused, int* out)
{
	Stat st;
	int r;
	int d;

	r = gm_MapEntityStatRange(entity->job);
	if ((*(int*)&gm_GameTime) < 4) {
		return 0;
	}
	gm_GetLawEntry(0xe, &st);
	d = st.v[2] - st.v[1];
	if (r == 9) {
		if (st.v[6] < (int) (d * 0.55f + st.v[1])) {
			*out = st.v[2] - gm_RandomMod(6);
			return 1;
		}
	} else {
		if (st.v[6] > (int) (d * 0.45f + st.v[1])) {
			*out = st.v[1] + gm_RandomMod(6);
			return 1;
		}
	}
	return 0;
}
