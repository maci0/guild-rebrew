// FUNCTION: GOLDTL 0x005a30c0
// SIZE: 236

extern int g_772514;
extern char* g_1015ea0;

int __cdecl fcn_0046f740(int, int, int, int);
float __cdecl fcn_0050bb50(int, int);
void __cdecl fcn_0050bc10(int, int, char*);
int __cdecl fcn_0046fac0(int, int, char*, int);

int __cdecl fcn_005a30c0(int x, int y, int layer, int a4, int a5)
{
	char text[0x40];
	int r;
	int w;
	float f;

	fcn_0046f740(x, y, 0x525, layer);
	r = fcn_0046f740(x + 2, y + 2, a4 + 0xdf, layer);
	fcn_0046f740(x + 3, y + 0x35, 0x746, layer);
	*(int*) (g_1015ea0 + r * 756 + 0x5c) = 1;
	f = fcn_0050bb50(a4, a5);
	fcn_0050bc10((int) f, a5, text);
	w = fcn_0046fac0(x + 7, y + 0x3a, text, g_772514);
	*(int*) (g_1015ea0 + w * 756 + 0x18) = 0x24;
	*(int*) (g_1015ea0 + w * 756 + 0x84) = 0x54;
	*(int*) (g_1015ea0 + w * 756 + 0x70) = 1;
	return r;
}
