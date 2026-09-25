// FUNCTION: GOLDTL 0x4aa6a0
// SIZE: 280

typedef struct Ent {
	char pad0[4];
	int x4;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern Ent g_7f4ca0[768];

unsigned short __cdecl fcn_0042e410(int n);
int __cdecl fcn_004a5340(char* e, int a, int* b, float c, float r, int* out);
int __cdecl fcn_0055c140(char* e, Ent* t, int* cnt);
int __cdecl fcn_00579640(Ent* t, char* e);
double __cdecl gm_RandomFloat01(void);

int __cdecl fcn_004aa6a0(char* e, char* a2, char* out)
{
	int cnt;
	int mask;
	int idx;

	cnt = 0;
	if (*(int*) (e + 0x194) < 1) {
		return 0;
	}
	mask = 0xf00500;
	if (fcn_004a5340(e, 1, &mask, 0, fcn_0042e410(0x40), &idx) == 0) {
		return 0;
	}
	if (fcn_0055c140(e, &g_7f4ca0[(unsigned short) idx], &cnt) == 0) {
		return 0;
	}
	if (fcn_00579640(&g_7f4ca0[(unsigned short) idx], e) == 0) {
		return 0;
	}
	if (cnt > 3) {
		return 0;
	}
	if (gm_RandomFloat01() < cnt * 0.25f) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = g_7f4ca0[(unsigned short) idx].x4;
	return 1;
}
