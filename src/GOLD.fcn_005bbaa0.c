// FUNCTION: GOLD 0x005bbaa0
// SIZE: 171

extern char* g_f8f080;
extern short g_f8f39c[];

int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046f100(int, int, int, int, int, int);

int __cdecl fcn_005bbaa0(int row, int id, int* out, int layer)
{
	out[1] = fcn_0046f740(0, row * 120, 0x74c, layer);
	out[0] = fcn_0046f740(0xd, row * 120 + 5, id, layer);
	*(int*) (g_f8f080 + out[0] * 748 + 0x4c) = 1;
	*(int*) (g_f8f080 + out[0] * 748 + 0x1c0) = 3;
	out[2] = fcn_0046f100(0x40, row * 120, 0xcd, 0x57, 0x10, layer);
	g_f8f39c[out[2] * 482] = 0x54;
	return out[1];
}
