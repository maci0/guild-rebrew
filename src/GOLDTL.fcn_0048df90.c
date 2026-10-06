typedef struct Ent {
	unsigned short id;
	char pad2[0x178 - 2];
	int stock;
} Ent;
// SIZE 0x17c

extern unsigned char g_773d75;

int __cdecl fcn_0050dac0(unsigned short id);
int __cdecl fcn_0050b810(int a, unsigned char b);

// FUNCTION: GOLD 0x0048e9e0
// FUNCTION: GOLDTL 0x48df90
int __cdecl fcn_0048df90(Ent* e, char* a2, char* a3)
{
	int t;
	int thr[3];
	int m;
	int v;
	int i;

	t = fcn_0050dac0(e->id);
	m = fcn_0050b810(e->stock, g_773d75);
	v = (int) (m * 0.25f);
	thr[0] = (int) (t * 0.01f);
	thr[1] = (int) (t * 0.015f);
	thr[2] = (int) (t * 0.02f);
	if (v > thr[2]) {
		i = 2;
	} else if (v > thr[1]) {
		i = 1;
	} else if (v > thr[0]) {
		i = 0;
	} else {
		return 0;
	}
	*(int*) (a2 + 0x10) = 3;
	*(int*) (a3 + 0x10) = i;
	*(int*) (a3 + 8) = thr[i];
	return 1;
}
