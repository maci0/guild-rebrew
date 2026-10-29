typedef struct Sprite {
	int a7;
	char pad4[0x44 - 4];
	int a1;
	int a2;
	int a3;
	int a4;
	int a6;
	int t0;
	int t1;
	void* tex;
} Sprite;
// SIZE 0x64

extern char* g_1015ec0[];
extern int g_6b7fb8;
extern char s_67d8b0[];

void* __cdecl m_alloc(int size, const char* tag);
void* __cdecl fcn_0047ce00(int name, int a2);

/* ADDRESS: GOLDTL 0x004730c0 */
Sprite* __cdecl fcn_004730c0(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
	int i;
	Sprite* p;

	for (i = 0; i < 0x20; i++) {
		if (((Sprite**)g_1015ec0)[i] == 0) {
			break;
		}
	}
	if (i >= 0x20) {
		return 0;
	}
	p = (Sprite*) m_alloc(100, s_67d8b0);
	p->a1 = a1;
	p->a2 = a2;
	p->a3 = a3;
	p->a4 = a4;
	p->a7 = a7;
	p->a6 = a6;
	p->tex = fcn_0047ce00(a5, 0);
	p->t0 = g_6b7fb8;
	p->t1 = g_6b7fb8;
	((Sprite**)g_1015ec0)[i] = p;
	return p;
}
unsigned char _dpad_f8f0a0[94104];
