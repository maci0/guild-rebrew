typedef struct {
	char p0[0x18];
	float a;
	float b;
	float c;
	float d;
	float e;
	char p2c[0xc];
} Slot;

typedef struct {
	char p0[0x1e8];
	Slot* slots;
	char p1ec[0x2c];
	int kind;
} Obj;

extern char g_1041d6c;
extern int g_67a370;

char __cdecl fcn_004462b0(void* p, int arg);
void __cdecl fcn_004379a0(int list, int a, int mask, char(__cdecl* fn)(void*, int), int arg);

/* ADDRESS: GOLDTL 0x004462b0 */
char __cdecl fcn_004462b0(Obj* o, int i)
{
	Slot* s;

	switch (o->kind) {
	case 5:
	case 6:
		s = o->slots;
		if (s[i].a > 0.0f || s[i].b != 0.0f || s[i].c != 0.0f) {
			if (s[i].d > 0.0f || s[i].e > 0.0f) {
				g_1041d6c = 1;
				return 0;
			}
		}
		break;
	case 7:
		s = o->slots;
		if (s[i].a > 0.0f || s[i].b != 0.0f || s[i].c != 0.0f) {
			if (s[i].d > 0.0f) {
				g_1041d6c = 1;
				return 0;
			}
		}
		break;
	case 8:
		return 1;
	}
	return 1;
}

/* ADDRESS: GOLDTL 0x004463b0 */
char __cdecl fcn_004463b0(unsigned int n)
{
	g_1041d6c = 0;
	if (n < 7) {
		fcn_004379a0(g_67a370, 0, 0x1e, fcn_004462b0, n);
		return g_1041d6c;
	}
	return 0;
}
