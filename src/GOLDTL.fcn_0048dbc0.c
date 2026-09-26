// FUNCTION: GOLD 0x0048e610
// SIZE: 267
// FUNCTION: GOLDTL 0x48dbc0
// SIZE: 267

typedef struct Ent {
	unsigned short id;
	char pad2[2];
	int x4;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];
extern unsigned char g_773d75;
extern float g_662da8;
extern float g_6628bc;
extern float g_6628ac;

unsigned short __cdecl fcn_0042e410(int n);
int __cdecl fcn_004a5340(char* e, int a, int* b, int c, float r, int* out);
int __cdecl fcn_0050b810(int a, char b);
int __cdecl fcn_0050dac0(unsigned short id);

int __cdecl fcn_0048dbc0(char* e, char* a2, char* a3)
{
	int mask;
	int idx;
	Ent* t;
	int have;
	int need;

	if (*(int*) (e + 0x194) < 16) {
		return 0;
	}
	mask = 0xf00500;
	if (fcn_004a5340(e, 1, &mask, 0, fcn_0042e410(0x20) + g_662da8, &idx) == 0) {
		return 0;
	}
	t = &((Ent*)g_7f4ca0)[(unsigned short) idx];
	have = (int) (fcn_0050b810(*(int*) (e + 0x178), (*(char*)&g_773d75)) * g_6628bc);
	need = fcn_0050dac0(*(unsigned short*) e);
	need = (int) ((fcn_0050dac0(t->id) + need) * g_6628ac);
	if (have < need) {
		return 0;
	}
	*(int*) (a3 + 8) = need;
	*(int*) (a2 + 8) = 0;
	*(int*) (a3 + 0xc) = t->x4;
	*(int*) (a3 + 0x10) = 0;
	*(int*) (a2 + 0x10) = 0;
	return 1;
}
