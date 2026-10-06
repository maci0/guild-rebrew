extern char* g_f8f080;
extern char* g_143c860[];

int __cdecl fcn_0050dfd0(int, int);
int __cdecl fcn_0046a950(int, int, int, int, int, int, int, int);
int __cdecl fcn_00469ed0(int, int, int, int, int);
void __cdecl fcn_004760a0(int, int);
int __cdecl fcn_005de7a2(char*, char*, ...);

// FUNCTION: GOLD 0x004be790

int __cdecl fcn_004be790(unsigned short* a1, int a2, int a3, int col, int x, int y, int layer, int* out)
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
	r = fcn_0046a950(px - 8, py - 5, 0x2f, 0, k, 0x6a, 0x2d, layer);
	id = fcn_00469ed0(px, py, a3 + 0xdf, 0x8a, layer);
	fcn_004760a0(id, 0x54);
	out[0] = -1;
	out[1] = id;
	out[2] = r;
	*(int*) (g_f8f080 + id * 748 + 0x1c0) = 0x22;
	*(int*) (g_f8f080 + id * 748 + 0x1cc) = 4;
	*(int*) (g_f8f080 + id * 748 + 0x1d0) = 0xf;
	fcn_005de7a2(g_f8f080 + id * 748 + 0xbc, "%s", g_143c860[a3 * 2]);
	return id;
}
