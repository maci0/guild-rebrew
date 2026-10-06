
typedef struct Ent {
	unsigned short id;
	unsigned char x2;
	char pad3;
	int x4;
	char pad8[0x16c - 8];
	char* owner;
	char pad170[0x21c - 0x170];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];
extern char* g_77261c;
extern float g_664154;

unsigned short __cdecl fcn_0042e410(int n);
typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);
char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int id);


// FUNCTION: GOLD 0x4a8db0
// FUNCTION: GOLDTL 0x4a8ed0
int __cdecl fcn_004a8ed0(char* a1, char* e, char* a3, char* a4, char* out)
{
	int found;
	char* q;
	Ent* t;
	int i;
	int n;
	F8 f;

	f.mask = 0x807d4190;
	f.b = 1;
	if (g_77261c != 0) {
		fcn_004a5e60(g_77261c, 4, f, 0, 100.0f, &found);
	}
	if (found == -1 && fcn_004a5e60(e, 6, f, 0, fcn_0042e410(0x20) + g_664154, &found) == 0) {
		return 0;
	}
	q = gm_StartFilteredEntitySearch(1, 1, found);
	if (q == 0) {
		return 0;
	}
	t = 0;
	i = fcn_0042e410(0x300);
	for (n = 0x300; n != 0;) {
		if (((Ent*)g_7f4ca0)[i].id != 0xffff && ((Ent*)g_7f4ca0)[i].owner == q && ((Ent*)g_7f4ca0)[i].x2 == 0) {
			t = &((Ent*)g_7f4ca0)[i];
			break;
		}
		n--;
		i = (i + 1) % 0x300;
	}
	if (t == 0) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = t->x4;
	*(int*) (out + 8) = *(int*) (q + 1);
	return 1;
}
