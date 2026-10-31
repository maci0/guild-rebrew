/* Float block handed to fcn_005d3d90 and filled by fcn_004fc460. */
typedef struct Gfx {
	float f[10];
} Gfx;
// SIZE 0x28

/* Draw entity: 0x2f4 bytes in the g_1015ea0 table. */
typedef struct Ent {
	char pad0[0x58];
	int x58;             /* 0x058 */
	int x5c;             /* 0x05c */
	char pad60[0x294];
} Ent;
// SIZE 0x2f4

extern char* g_1015ea0;
extern char g_1015f40[];
extern int g_772514;
extern unsigned char g_773d75;
extern float g_773d4c;
extern unsigned short g_775340;
extern int g_774654;
extern int g_14ce8e0;
extern int g_100f1dc;
extern double dbl_1_0;
extern double g_662cc0;
extern float g_662a98;
extern float g_662cf8;
extern double g_662950;
extern double g_662c38;

int __cdecl fcn_0057ec20(int a);
void __cdecl fcn_0057e880(int a, int b, int c, int d);
char* __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00471b60(char* dlg);
void __cdecl d2_SetForm(char* dlg, int page);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl io_AppendText(int id, ...);
float __cdecl fcn_004fc460(Gfx* g);
void __cdecl fcn_005d3d90(unsigned short flags, Gfx g, int rec);
char* __cdecl fcn_0046f740(int x, int y, int id, int layer);
void __cdecl fcn_0046fac0(int a, int y, char* text, int rec);
int __cdecl fcn_00472380(int id, int mask);
void __cdecl fcn_00472c30(int x1, int y1, int x2, int y2, int r, int g, int b);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
int __cdecl fcn_00471f80(int id);
int __cdecl fcn_005373e0(void* fn, int id);
void __cdecl fcn_00471e30(char* dlg);

/* ADDRESS: GOLDTL 0x005d42e0 */
void __cdecl fcn_005d42e0(void)
{
	unsigned char colors[15];
	char* cp;
	char* dlg;
	int r;
	int g;
	int b;
	Gfx gfx;
	int items[5];
	char buf[256];
	int row;
	int i;
	int n;
	int j;
	int mask;

	colors[0] = 0x33;
	colors[1] = 0x33;
	colors[2] = 0x33;
	colors[3] = 0x10;
	colors[4] = 0xee;
	colors[5] = 0x10;
	colors[6] = 0xee;
	colors[7] = 0x10;
	colors[8] = 0x10;
	colors[9] = 0xee;
	colors[10] = 0xee;
	colors[11] = 0x00;
	colors[12] = 0xee;
	colors[13] = 0x10;
	colors[14] = 0xee;
	if (g_775340 == 0) {
		g_775340 = 1;
	}
	if (!fcn_0057ec20(0x10)) {
		return;
	}
	fcn_0057e880(0xc, 0, 0, 0);
	dlg = fcn_00470820(0, 0, "panel\\statistik_stadt");
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1f0e, (int) g_773d75 * 0x2f4 + 0x868080, 0x7f4c00);
	fcn_004fc460(&gfx);
	d2_SetForm(dlg, 2);
	io_AppendText(0x1f14, (int) g_773d4c);
	n = (int) ((gfx.f[9] + dbl_1_0) * g_662cc0);
	if (n > 4) {
		n = 4;
	}
	io_AppendText(0x1f15, n + 0x1f16);
	n = (int) (gfx.f[2] * g_662a98);
	if (n > 4) {
		n = 4;
	}
	io_AppendText(0x1f1b, n + 0x1f1c);
	io_AppendText(0x1f21, (int) (gfx.f[1] * g_662cf8 > g_662950 ? gfx.f[1] * g_662cf8 : g_662950));
	n = (int) ((gfx.f[3] > g_662950 ? gfx.f[3] : g_662950) * g_662c38);
	io_AppendText(0x1f22, n);
	d2_SetForm(dlg, 3);
	fcn_005d3d90((unsigned short) g_775340, gfx, g_772514);
	d2_SetForm(dlg, 4);
	cp = (char*) &colors[1];
	row = 0;
	for (i = 4; i < 0x9a; i += 0x1e) {
		mask = (1 << row) & g_775340;
		mask = mask != 0;
		n = fcn_0046f740(5, i + 1, 2, g_772514);
		items[row] = n;
		io_FormatTextBuffer(buf, row + 0x1f25);
		fcn_0046fac0(0x19, i, buf, g_772514);
		((Ent*) g_1015ea0)[n].x5c = 1;
		((Ent*) g_1015ea0)[n].x58 = 1;
		fcn_00472380(n, mask);
		*(char*) &r = cp[-1];
		*(char*) &g = cp[0];
		*(char*) &b = cp[1];
		for (j = i + 5; j < i + 15; j++) {
			fcn_00472c30(*(int*) (g_1015f40 + g_772514 * 0x3cc + 0xc) - 1, j,
				*(int*) (g_1015f40 + g_772514 * 0x3cc + 0xc) - 0xb, j, r, g, b);
		}
		row++;
		cp += 3;
	}
	for (;;) {
		if (g_100f1dc != -1) {
			g_775340 = 0;
			for (i = 0; i < 5; i++) {
				g_775340 |= fcn_00471f80(items[i]) ? (1 << i) : 0;
			}
			d2_SetForm(dlg, 3);
			fcn_005d3d90(g_775340, gfx, g_772514);
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (!fcn_005373e0(fcn_005d42e0, 0x657c7)) {
			break;
		}
	}
	fcn_00471e30(dlg);
	fcn_0057e880(0xc, 0, 1, 0);
}
