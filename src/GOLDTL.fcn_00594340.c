// FUNCTION: GOLDTL 0x00594340
// SIZE: 393

typedef struct
{
	int x0;
	int x4;
	int x8;
	int xc;
	int x10;
} Pair;
// SIZE 0x14

typedef struct
{
	int x0;
	int a[4];
	int b[4];
	int x24;
	int x28;
	int c[4];
	int d[4];
	int x4c;
	int x50;
	int x54;
} Panel;
// SIZE 0x58

typedef struct
{
	int x0;
	int x4;
	int x8;
	int xc;
	int x10;
	int x14;
	int x18;
	int x1c;
	int x20;
	int x24;
	int x28;
	int x2c;
	int x30;
	int x34;
} Slot;
// SIZE 0x38

extern Pair g_778d48[4];
extern Pair g_779128[2];
extern Panel g_779160[16];
extern int g_7798a0;
extern Slot g_7798c0[16];
extern Slot g_778da0[16];
extern Slot g_7796e0[16];

void __cdecl fcn_00594340(void)
{
	int i;
	int j;

	for (i = 0; i < 4; i++) {
		g_778d48[i].x0 = -1;
		g_778d48[i].x8 = -1;
	}
	for (i = 0; i < 2; i++) {
		g_779128[i].x0 = 0;
		g_779128[i].x8 = -1;
	}
	for (i = 0; i < 16; i++) {
		g_779160[i].x0 = 0;
		for (j = 0; j < 4; j++) {
			g_779160[i].a[j] = 0;
			g_779160[i].b[j] = -1;
		}
		g_779160[i].x24 = 16;
		g_779160[i].x28 = i * 120 + 8;
		g_779160[i].c[0] = -1;
		g_779160[i].c[1] = -1;
		g_779160[i].c[2] = -1;
		g_779160[i].c[3] = -1;
		for (j = 0; j < 4; j++) {
			g_779160[i].d[j] = -1;
		}
		g_779160[i].x4c = -1;
	}
	g_7798a0 = 0;
	for (i = 0; i < 16; i++) {
		g_7798c0[i].x0 = 0;
		g_7798c0[i].x4 = -1;
		g_7798c0[i].x8 = 26;
		g_7798c0[i].xc = i * 69 + 16;
		g_7798c0[i].x10 = -1;
		g_7798c0[i].x14 = -1;
		g_7798c0[i].x18 = -1;
		g_7798c0[i].x1c = -1;
		g_7798c0[i].x28 = -1;
		g_7798c0[i].x20 = -1;
		g_7798c0[i].x24 = -1;
		g_7798c0[i].x34 = -1;
	}
	for (i = 0; i < 16; i++) {
		g_778da0[i].x0 = 0;
		g_778da0[i].x4 = -1;
		g_778da0[i].x8 = i % 4 * 64 + 16;
		g_778da0[i].xc = i / 4 * 64 + 16;
		g_778da0[i].x10 = -1;
		g_778da0[i].x14 = -1;
		g_778da0[i].x18 = -1;
		g_778da0[i].x1c = -1;
		g_778da0[i].x28 = -1;
		g_778da0[i].x20 = -1;
		g_778da0[i].x24 = -1;
		g_778da0[i].x34 = -1;
	}
	for (i = 0; i < 16; i++) {
		g_7796e0[i].x0 = 0;
		g_7796e0[i].x4 = -1;
		g_7796e0[i].x8 = i % 4 * 64 + 16;
		g_7796e0[i].xc = i / 4 * 64 + 208;
		g_7796e0[i].x10 = -1;
		g_7796e0[i].x14 = -1;
		g_7796e0[i].x18 = -1;
		g_7796e0[i].x1c = -1;
		g_7796e0[i].x28 = -1;
		g_7796e0[i].x20 = -1;
		g_7796e0[i].x24 = -1;
		g_7796e0[i].x34 = -1;
	}
}
