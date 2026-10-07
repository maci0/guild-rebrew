// FUNCTION: GOLD 0x005a0aa0
// FUNCTION: GOLDTL 0x005a9dd0

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x161];
	unsigned char kind;
	char pad16a[0xb2];
} House5a9d;

extern char g_7f4ca0[];
extern unsigned char* g_868050;
extern char g_868060[];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;
extern char g_6aae08[];

unsigned char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int a, char b);
int __cdecl gm_AccumulateTyped2(House5a9d* entity);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190();
void __cdecl fcn_005c9030(int, int, int, int*);
int __cdecl fcn_0050b710(int a, unsigned char b);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl fcn_00471f80(int slot);
int __cdecl fcn_0050b750(int a, unsigned char k);
int __cdecl fcn_00526010(House5a9d*, int, unsigned char);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005a9dd0(unsigned char* p)
{
	int h2;
	int n;
	int h1;
	unsigned char* obj;
	unsigned char* tbl;
	int acc;
	int ok;
	int d;
	int b;
	int v;

	h2 = -1;
	h1 = -1;
	b = 0;
	tbl = g_868050 + p[0] * 0x24d;
	obj = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x142);
	n = fcn_0050b810(*(int*) (obj + 0x14), g_773d75);
	acc = gm_AccumulateTyped2(&((House5a9d*)g_7f4ca0)[g_774970]);
	if (*tbl == 0x17 && ((House5a9d*)g_7f4ca0)[g_774970].kind == 0x1e) {
		ok = 1;
	}
	else if (*tbl == 0x18 && ((House5a9d*)g_7f4ca0)[g_774970].kind == 0x1f) {
		ok = 1;
	}
	else if (*tbl == 0x19 && ((House5a9d*)g_7f4ca0)[g_774970].kind == 0x20) {
		ok = 1;
	}
	else if (*tbl == 0x1a && ((House5a9d*)g_7f4ca0)[g_774970].kind == 0x21) {
		ok = 1;
	}
	else {
		ok = 0;
	}
	d = fcn_00470820(0, 0, g_6aae08);
	fcn_00471b60(d);
	fcn_00473a90(0, 0);
	fcn_004727a0(d, 1);
	fcn_00519190(0x1a1a, n);
	if (ok != 0) {
		int col;

		b = fcn_00519190(0x1a1b, *(unsigned short*) (((char(*)[0x2f4])g_868060)[g_773d75] + 0x54) * 2 + 0x9a8);
		fcn_005c9030(0x640, acc, 0x20, &col);
		fcn_00472380(fcn_00472250(d, 1, b), fcn_0050b710(0x640, g_773d75), fcn_0050b710(col, g_773d75), fcn_0050b710(0x640, g_773d75));
		h1 = fcn_00472250(d, 1, b + 1);
		h2 = fcn_00472250(d, 1, b + 2);
	}
	g_100f1dc = -1;
	while (fcn_005373e0(fcn_005a9dd0, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (ok != 0 && g_100f1dc != -1) {
			if (g_67d370 == h1) {
				v = fcn_00471f80(fcn_00472250(d, 1, b));
				v = fcn_0050b750(v, g_773d75);
				if (fcn_00526010(&((House5a9d*)g_7f4ca0)[g_774970], v, g_773d75) != 0) {
					fcn_004c5150(*(int*) (obj + 2), ((House5a9d*)g_7f4ca0)[g_774970].handle, g_773d75, v);
					g_774654 = 1;
				}
			}
			else if (g_67d370 == h2) {
				g_774654 = 1;
			}
		}
	}
	fcn_00532ef0();
	fcn_00471e30(d);
}
