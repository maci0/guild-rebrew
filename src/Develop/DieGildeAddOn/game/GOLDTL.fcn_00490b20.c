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

/* ADDRESS: GOLDTL 0x00490b20 */
int __cdecl ai_EvaluateLaw0x05(Ent* entity, int unused, int* out)
{
	Stat st;
	int target;
	int clamped;
	int jobCategory;

	target = (int) ((3.0f - entity->mood) * 5.0f);
	if (target < 4) {
		clamped = target;
	} else {
		clamped = 4;
	}
	jobCategory = gm_MapEntityStatRange(entity->job);
	if ((jobCategory == 8 || jobCategory == 9) && clamped > 1) {
		clamped = 1;
	}
	gm_GetLawEntry(5, &st);
	if (clamped != st.v[6]) {
		*out = clamped;
		return 1;
	}
	return 0;
}
