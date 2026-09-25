typedef struct TexDesc {
	int pad0;
	int w;
	int h;
	int rest[0x14];
} TexDesc;
// SIZE 0x5c

typedef struct TexSlot {
	int a;
	int b;
	void* tex;
} TexSlot;
// SIZE 0xc

typedef struct Tag {
	int id;
	int val;
	int pad;
} Tag;
// SIZE 0xc

extern void* g_100f8a0;
extern TexSlot g_100f860[3];
extern TexSlot g_100f840;

void __cdecl fcn_00475f80(void* p);

// FUNCTION: GOLD 0x00477410
// SIZE: 115
// FUNCTION: GOLDTL 0x473ed0
// SIZE: 115
void __cdecl fcn_00473ed0(void)
{
	int i;

	if (g_100f8a0) {
		fcn_00475f80(g_100f8a0);
		g_100f8a0 = 0;
	}
	for (i = 0; i < 3; i++) {
		if (g_100f860[i].tex) {
			fcn_00475f80(g_100f860[i].tex);
			g_100f860[i].tex = 0;
			g_100f860[i].a = -1;
			g_100f860[i].b = -1;
		}
	}
	fcn_00475f80(g_100f840.tex);
	g_100f840.a = -1;
	g_100f840.b = -1;
	g_100f840.tex = 0;
}
