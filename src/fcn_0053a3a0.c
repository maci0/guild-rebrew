extern char* g_1015ea0;
// FUNCTION: GOLDTL 0x53a3a0
// SIZE: 86

int __cdecl fcn_00468df0(int, int, int, int, int);
void __cdecl fcn_00469110(int, int);

int __cdecl fcn_0053a3a0(int a1, int a2, int a3)
{
	int r;

	r = fcn_00468df0(0x20, a1 * 0x2b + 0xa, 0xbf, a2, a3);
	*(int*) ((char*) g_1015ea0 + r * 0x2f4 + 0x6c) = 1;
	fcn_00469110(r, 0x12c);
	return r;
}
