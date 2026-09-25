typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3;
	unsigned int seed;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern Ent g_7f4ca0[];
extern int g_14cbca0;
extern unsigned int g_14cbcb4;
extern unsigned char g_6a375c;

// FUNCTION: GOLD 0x47e8a0
// SIZE: 137
// FUNCTION: GOLDTL 0x47dd60
// SIZE: 137
int __cdecl fcn_0047dd60(char* e)
{
	char* p;
	unsigned short idx;

	if (e[2] != 1 && e[2] != 2) {
		return 0;
	}
	if (!e[0x164]) {
		return 0;
	}
	p = *(char**) (e + 0x16c);
	if (!p) {
		return 0;
	}
	idx = *(unsigned short*) (p + 0x27);
	if (idx == 0xffff) {
		return 0;
	}
	if (g_7f4ca0[idx].kind == 7) {
		return 0;
	}
	if (g_14cbca0 != -1 && g_7f4ca0[idx].kind != 6 && g_7f4ca0[idx].seed % g_6a375c != g_14cbcb4) {
		return 0;
	}
	return 1;
}
