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

void __cdecl fcn_004f4830(int a, Stat* st);
#include "Develop/DieGildeAddOn/game/spiel.h"

#define MAXV(a, b) (((a) > (b)) ? (a) : (b))
#define MINV(a, b) (((a) < (b)) ? (a) : (b))

// FUNCTION: GOLD 0x491a30
// FUNCTION: GOLDTL 0x491000
int __cdecl fcn_00491000(Ent* e, int a2, int* out)
{
	Stat st;
	int r;
	int d;
	int x;
	int c;

	r = gm_MapEntityStatRange(e->job);
	fcn_004f4830(0xb, &st);
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
