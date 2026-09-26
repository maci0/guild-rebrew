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
int __cdecl fcn_00507b00(int job);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

unsigned short __cdecl fcn_0042e410(int n);

// FUNCTION: GOLD 0x00491b10
// SIZE: 202
// FUNCTION: GOLDTL 0x4910e0
// SIZE: 202
int __cdecl fcn_004910e0(Ent* e, int a2, int* out)
{
	Stat st;
	int r;
	int d;

	r = fcn_00507b00(e->job);
	if ((*(int*)&g_7f4c00) < 4) {
		return 0;
	}
	fcn_004f4830(0xc, &st);
	d = st.v[2] - st.v[1];
	if (r == 8) {
		if (st.v[6] > (int) (d * 0.33f + st.v[1])) {
			*out = st.v[1] + fcn_0042e410(3);
			return 1;
		}
	} else {
		if (st.v[6] < (int) (d * 0.66f + st.v[1])) {
			*out = st.v[2] - fcn_0042e410(3);
			return 1;
		}
	}
	return 0;
}
