// FUNCTION: GOLDTL 0x45c290
// SIZE: 128

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
	char pad[0x2c];
} Tex;

extern Tex* g_104049c;
extern unsigned int g_10404a0;
extern unsigned int g_10405c4;

Tex* __cdecl fcn_0045c290(Col c, int* out)
{
	Tex* t;
	int i;

	if (g_10405c4 == g_10404a0) {
		if (out != 0) {
			*out = -1;
		}
		return 0;
	}
	if (c.a >= 0xff && !c.c0) {
		for (i = 0, t = g_104049c; t->refs > 0; i++, t++) {
		}
	} else {
		for (i = g_10404a0 - 1, t = &g_104049c[i]; t->refs > 0; i--, t--) {
		}
	}
	if (out != 0) {
		*out = i;
	}
	return t;
}
