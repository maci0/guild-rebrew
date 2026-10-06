// FUNCTION: GOLDTL 0x005c78f0

extern char* g_1015ea0;
extern int g_10161cc[];

int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046f100(int, int, int, int, int, int);

int __cdecl fcn_005c78f0(int row, int id, int* out, int layer)
{
	out[1] = fcn_0046f740(0, row * 120, 0x74c, layer);
	out[0] = fcn_0046f740(0xd, row * 120 + 5, id, layer);
	*(int*) (g_1015ea0 + out[0] * 756 + 0x5c) = 1;
	*(int*) (g_1015ea0 + out[0] * 756 + 0x1d0) = 3;
	out[2] = fcn_0046f100(0x40, row * 120, 0xcd, 0x57, 0x10, layer);
	g_10161cc[out[2] * 243] = 0x54;
	return out[1];
}
