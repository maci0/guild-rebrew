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

// FUNCTION: GOLDTL 0x490b20
// SIZE: 129
int __cdecl fcn_00490b20(Ent* e, int a2, int* out)
{
	Stat st;
	int t;
	int v;
	int r;

	t = (int) ((3.0f - e->mood) * 5.0f);
	if (t < 4) {
		v = t;
	} else {
		v = 4;
	}
	r = fcn_00507b00(e->job);
	if ((r == 8 || r == 9) && v > 1) {
		v = 1;
	}
	fcn_004f4830(5, &st);
	if (v != st.v[6]) {
		*out = v;
		return 1;
	}
	return 0;
}
