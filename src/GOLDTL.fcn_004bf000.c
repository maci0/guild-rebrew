extern char* g_1015ea0;
extern char* g_14a79c0[];

int __cdecl fcn_0050dfd0(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_00466ee0(int, int, int, int, int);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_0064d41a(char*, char*, ...);

// FUNCTION: GOLDTL 0x4bf000
// SIZE: 326

int __cdecl fcn_004bf000(unsigned short* a1, int a2, int a3, int col, int x, int y, int layer, int* out)
{
	int tbl[3][3] = { { 0x51, 0, 0 }, { 0x30, 0x71, 0 }, { 0x11, 0x52, 0x93 } };
	int k;
	int r;
	int id;
	int px;
	int py;

	k = fcn_0050dfd0(a2, a3);
	px = tbl[*a1 - 0x134][col] + x + 0x6e;
	py = y + 0x22;
	r = fcn_004677e0(px - 8, py - 5, 0x2f, 0, k, 0x6a, 0x2d, layer);
	id = fcn_00466ee0(px, py, a3 + 0xdf, 0x8a, layer);
	fcn_00472900(id, 0x54);
	out[0] = -1;
	out[1] = id;
	out[2] = r;
	*(int*) (g_1015ea0 + id * 756 + 0x1d0) = 0x22;
	*(int*) (g_1015ea0 + id * 756 + 0x1dc) = 4;
	*(int*) (g_1015ea0 + id * 756 + 0x1e0) = 0xf;
	fcn_0064d41a(g_1015ea0 + id * 756 + 0xcc, "%s", g_14a79c0[a3 * 2]);
	return id;
}
