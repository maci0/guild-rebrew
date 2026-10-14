#include <stdlib.h>

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

#define MAXF(a, b) (((a) > (b)) ? (a) : (b))
#define MINF(a, b) (((a) < (b)) ? (a) : (b))

/* ADDRESS: GOLD 0x00491be0 */
/* ADDRESS: GOLDTL 0x004911b0 */
int __cdecl fcn_004911b0(Ent* e, int a2, int* out)
{
	Stat st;
	float v;
	int d;
	int x;

	v = MAXF(MINF((3.0f - e->mood) * (*(float*) ((char*) e + 0x1c) * (1.0f / 700.0f)), 1.0f), 0.0f);
	fcn_004f4830(0xd, &st);
	d = st.v[2] - st.v[1];
	x = (int) (d * v + st.v[1]);
	if (abs(x - st.v[6]) > 3) {
		*out = x;
		return 1;
	}
	return 0;
}
