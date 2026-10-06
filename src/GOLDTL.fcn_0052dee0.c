extern int g_772514;
extern char* g_1015ea0;
// FUNCTION: GOLDTL 0x0052dee0

int __cdecl fcn_00468df0(char*, int, int, int, int);
void __cdecl fcn_00472900(int, int);
void __cdecl fcn_00469110(int, int);

int __cdecl fcn_0052dee0(char* a, int b, int c)
{
	int h;

	h = fcn_00468df0(a + 3, b, 0xc5, c, g_772514);
	fcn_00472900(h, 0x54);
	*(int*) (g_1015ea0 + h * 0x2f4 + 0x6c) = 1;
	fcn_00469110(h, 0x60);
	return h;
}
