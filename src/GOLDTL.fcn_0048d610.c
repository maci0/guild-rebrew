typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3[0xd - 3];
	unsigned char level;
	char pade[0x21c - 0xe];
} Ent;
// SIZE 0x21c

extern Ent g_7f4ca0[768];
extern int g_67e964;
extern int g_7f4c00;
extern int g_772624;

int __cdecl gm_StartFilteredEntitySearch(int a, int b, int c, int d, int id);

// FUNCTION: GOLDTL 0x48d610
// SIZE: 162
int __cdecl fcn_0048d610(Ent* e, int* out)
{
	int i;
	int r;

	if (g_67e964 < g_7f4c00) {
		g_772624 = 0;
		for (i = 0; i < 768; i++) {
			if (g_7f4ca0[i].kind == 6 || g_7f4ca0[i].kind == 7 || g_7f4ca0[i].kind == 5) {
				g_772624++;
			}
		}
		g_67e964 = g_7f4c00;
	}
	if (e->kind == 3) {
		return 0;
	}
	r = gm_StartFilteredEntitySearch(2, 5, 0x1e, 4, e->id);
	if (out) {
		*out = r;
	}
	if (r) {
		return 2;
	}
	if (e->kind == 5) {
		return 1;
	}
	if ((e->kind == 2 || e->kind == 4) && e->level > 6) {
		return 1;
	}
	return 0;
}
