// FUNCTION: GOLD 0x0048e720
// SIZE: 246
// FUNCTION: GOLDTL 0x48dcd0
// SIZE: 246

typedef struct Ent {
	char pad0[4];
	int x4;
	char pad8[0x166 - 8];
	unsigned char x166;
	char pad167[0x21c - 0x167];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];
extern float g_662da8;

unsigned short __cdecl fcn_0042e410(int n);
int __cdecl fcn_004a5340(char* e, int a, int* b, int c, float r, int* out);
int __cdecl fcn_004e99c0(int k);

int __cdecl fcn_0048dcd0(char* e, char* a2, char* a3)
{
	int mask;
	int idx;
	int thr[3];
	Ent* t;
	int n;
	int k;

	mask = 0xf00500;
	if (fcn_004a5340(e, 1, &mask, 0, fcn_0042e410(0x20) + g_662da8, &idx) == 0) {
		return 0;
	}
	t = &((Ent*)g_7f4ca0)[(unsigned short) idx];
	n = fcn_004e99c0(t->x166) / 3 + 2;
	thr[0] = n + 3;
	thr[1] = n + 5;
	thr[2] = n + 8;
	if (*(int*) (e + 0x194) >= thr[2]) {
		k = 2;
	} else if (*(int*) (e + 0x194) >= thr[1]) {
		k = 1;
	} else if (*(int*) (e + 0x194) >= thr[0]) {
		k = 0;
	} else {
		return 0;
	}
	*(int*) (a2 + 8) = thr[k];
	*(int*) (a3 + 0xc) = t->x4;
	*(int*) (a3 + 0x10) = k;
	*(int*) (a2 + 0x10) = 1;
	return 1;
}
