typedef struct Blk24 {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Blk24;

typedef struct F8 {
	int mask;
	int b;
} F8;
/* SIZE 0x8 */

int __cdecl ai_FindEntityInFavorRange(char* p, int kind, F8 f, int c, float r, int* out);
int __cdecl ai_FindMissingBuildingUpgrade(int* a, int* b, char* q, int c);
int __cdecl ai_SelectBestMethod(int kind, int id, int n, Blk24* b1, Blk24* b2);
void __cdecl gm_ResolveEntityById(void** out, int, int, int id);

extern float g_66417c;

/* ADDRESS: GOLDTL 0x00498e20 */
/* ADDRESS: GOLDDE 0x00487870 */
int __cdecl ai_StartBetriebUpgraden(int actionKind, char* actor, int busy, Blk24* out1, Blk24* out2)
{
	Blk24 b2;
	Blk24 b1;
	int v0;
	int v1;
	int found;
	char* building;
	int one;
	int r;
	F8 f;

	if (actionKind != 0 || actor[2] == 3) {
		return 0;
	}
	if (busy == 0) {
		if (out1->kind != 0) {
			return 0;
		}
	} else {
		if (out1->kind != 0) {
			return 0;
		}
	}
	one = 1;
	f.mask = 0xa07d7bb0;
	f.b = one;
	if (ai_FindEntityInFavorRange(actor, 4, f, 0, 100.0f, &found) == 0) {
		return 0;
	}
	gm_ResolveEntityById((void**) (&building), 0, 0, found);
	if (ai_FindMissingBuildingUpgrade(&v0, &v1, building, 0) == 0) {
		return 0;
	}
	b1.kind = 2;
	b1.a = v0;
	b1.b = one;
	b1.f = g_66417c;
	if (v1 != -1) {
		b2.kind = one;
		b2.a = v1;
	} else {
		b2.kind = 4;
		b2.a = *(int*) (building + 1);
	}
	b2.b = one;
	b2.f = b1.f;
	r = ai_SelectBestMethod(0x15, *(unsigned short*) actor, one, &b1, &b2);
	if (r == 0) {
		return 0;
	}
	*out1 = b1;
	*out2 = b2;
	return r;
}
