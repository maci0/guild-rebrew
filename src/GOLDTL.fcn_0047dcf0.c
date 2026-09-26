typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3;
	unsigned int seed;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];
extern int g_14cbca0;
extern unsigned int g_14cbcb4;
extern unsigned char g_6a375c;

// FUNCTION: GOLD 0x47e830
// SIZE: 112
// FUNCTION: GOLDTL 0x47dcf0
// SIZE: 106
int __cdecl fcn_0047dcf0(char* e)
{
	char* o;
	char* p;

	if (e[2] != 0 && e[2] != 1) {
		return 0;
	}
	o = e;
	p = *(char**) (e + 0x16c);
	if (p && *(unsigned short*) (p + 0x27) != 0xffff) {
		o = (char*) &((Ent*)g_7f4ca0)[*(unsigned short*) (p + 0x27)];
	}
	if (g_14cbca0 != -1 && *(unsigned int*) (o + 4) % g_6a375c != g_14cbcb4) {
		return 0;
	}
	return 1;
}
