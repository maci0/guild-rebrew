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

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLD 0x00491b10 */
/* ADDRESS: GOLDTL 0x004910e0 */
int __cdecl fcn_004910e0(Ent* e, int a2, int* out)
{
	Stat st;
	int r;
	int d;

	r = gm_MapEntityStatRange(e->job);
	if ((*(int*)&g_7f4c00) < 4) {
		return 0;
	}
	fcn_004f4830(0xc, &st);
	d = st.v[2] - st.v[1];
	if (r == 8) {
		if (st.v[6] > (int) (d * 0.33f + st.v[1])) {
			*out = st.v[1] + gm_RandomMod(3);
			return 1;
		}
	} else {
		if (st.v[6] < (int) (d * 0.66f + st.v[1])) {
			*out = st.v[2] - gm_RandomMod(3);
			return 1;
		}
	}
	return 0;
}
