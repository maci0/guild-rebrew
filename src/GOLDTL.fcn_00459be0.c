// FUNCTION: GOLDTL 0x459be0
// SIZE: 136

// SIZE 0x70
typedef struct Item {
	char pad[0x54];
	unsigned char flags;
	char pad2[0x1b];
} Item;

extern char* g_1042c38;
extern char g_1042d00[];
extern char* g_1042320;
extern char g_1052a40[];
extern char* g_104049c;
extern unsigned int g_10404a0;

void __cdecl fcn_00459be0(unsigned int flags)
{
	char* p;
	Item* it;
	unsigned int i;

	if ((flags & 4) == 0) {
		for (p = g_1042c38; p != g_1042d00; p = *(char**) (p + 0x1f8)) {
			p[0x2a1] &= 0xfe;
		}
	}
	i = 0;
	if ((flags & 0x10) == 0) {
		for (p = g_1042320; p != g_1052a40; p = *(char**) (p + 0x160)) {
			p[0x16a] = 0;
		}
	}
	if ((flags & 0x100) == 0) {
		it = ((Item*)g_104049c);
		for (; i < g_10404a0; i++) {
			it[i].flags &= 0xbf;
		}
	}
}
