typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

extern char* g_77261c;

int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
int __cdecl he_StartHandlungSearch(int a, int b, int c, int d, int e);
unsigned short __cdecl gm_RandomMod(int n);
int __cdecl ai_FindEntityInFavorRange(char* p, int kind, F8 f, int c, float r, int* out);

/* ADDRESS: GOLDTL 0x0048f710 */
int __cdecl ai_PlanGraveyardAction0x90(char* actor, char* building, char* req, char* out)
{
	int w;
	int h;
	int found;
	F8 f;

	w = gm_RandomMod(3);
	h = gm_RandomMod(3);
	*(int*) (req + 0x10) = 1;
	*(int*) (req + 0xc) = *(int*) (building + 1);
	if ((unsigned int) ((h + 2) * (w + 2)) > *(unsigned int*) (actor + 0x194)) {
		return 0;
	}
	if (!fcn_00502cd0(*(int*) (building + 0x5d), 2, 0, 0x211, 6)) {
		return 0;
	}
	if (he_StartHandlungSearch(2, 0, 0x90, 3, *(int*) (building + 1))) {
		return 0;
	}
	found = -1;
	f.mask = 0xa07c43b4;
	f.b = 1;
	if (g_77261c == 0 || (ai_FindEntityInFavorRange(g_77261c, 4, f, 0, 100.0f, &found), found == -1)) {
		if (!ai_FindEntityInFavorRange(actor, 6, f, 0, (float) gm_RandomMod(0x20) + 19.0f, &found)) {
			return 0;
		}
	}
	*(int*) (out + 8) = h;
	*(int*) (out + 4) = w;
	*(int*) (out + 0xc) = found;
	return 1;
}
