extern int g_100f1a8;
extern unsigned char g_100f1b8;
extern unsigned char g_100f1b9;
extern unsigned char g_100f1ba;

int __cdecl fcn_0041bac0(unsigned char r, unsigned char g, unsigned char b);

// FUNCTION: GOLDTL 0x479e00
// SIZE: 64
void __cdecl fcn_00479e00(unsigned char r, unsigned char g, unsigned char b)
{
	int c;

	c = fcn_0041bac0(r, g, b);
	g_100f1a8 = (c << 16) | c;
	g_100f1b8 = r;
	g_100f1b9 = g;
	g_100f1ba = b;
}
