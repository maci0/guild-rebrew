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

#define MAXV(a, b) (((a) > (b)) ? (a) : (b))
#define MINV(a, b) (((a) < (b)) ? (a) : (b))

/* ADDRESS: GOLDTL 0x00491000 */
/* ADDRESS: GOLDDE 0x0047feb0 */
int __cdecl ai_EvaluateLaw0x0b(Ent* e, int unused, int* out)
{
	Stat st;
	int r;
	int d;
	int x;
	int c;

	r = gm_MapEntityStatRange(e->job);
	gm_GetLawEntry(0xb, &st);
	d = st.v[2] - st.v[1];
	if (r == 7) {
		x = (int) ((e->mood - 2.0) * d + st.v[1]);
		c = MINV(MAXV(st.v[1], x), st.v[2]);
		if (c > st.v[6]) {
			*out = c;
			return 1;
		}
	} else {
		x = (int) ((3.0f - e->mood) * d + st.v[1]);
		c = MINV(MAXV(st.v[1], x), st.v[2]);
		if (c < st.v[6]) {
			*out = c;
			return 1;
		}
	}
	return 0;
}
