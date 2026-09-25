// FUNCTION: GOLDTL 0x45cb10
// SIZE: 194

// SIZE 0x4
typedef struct Col {
	unsigned char a;
	unsigned char b;
	unsigned char c0 : 1;
	unsigned char c1 : 1;
	unsigned char c2 : 6;
	unsigned char d;
} Col;

// SIZE 0x70
typedef struct Tex {
	char name[0x40];
	int refs;
	int pad44;
	int id;
	int pad4c[3];
	Col col;
	char x5c;
	char kind;
	char pad5e[0x12];
} Tex;

extern Tex* g_104049c;
extern unsigned int g_10404a0;

Tex* __cdecl fcn_0045cb10(int idx, char kind)
{
	Tex* p;
	int id;

	if (kind == 0) {
		return &g_104049c[idx];
	}
	id = g_104049c[idx].id;
	if (g_104049c[idx].col.a < 0xff || g_104049c[idx].col.c0) {
		for (p = &g_104049c[g_10404a0 - 1]; p >= g_104049c; p--) {
			if (p->refs > 0 && p->id == id && p->kind == kind) {
				return p;
			}
		}
		return 0;
	}
	for (p = g_104049c; p <= &g_104049c[g_10404a0 - 1]; p++) {
		if (p->refs > 0 && p->id == id && p->kind == kind) {
			return p;
		}
	}
	return 0;
}
