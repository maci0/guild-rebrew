typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} Col4e4b60;

extern int g_772f3c;
extern int g_772f68;
extern int g_6b89c0;
extern int g_772f64;

int __cdecl fcn_00459ae0(float a, float b, float c);
int __cdecl fcn_00459870(int h, int a, int b, Col4e4b60 c, float d, int e, float f, float g);
void __cdecl fcn_00459940(int h, int s, int a);
void __cdecl fcn_00459980(int h, int s, int a, float b);

// FUNCTION: GOLDTL 0x004e4b60
// SIZE: 145
void __cdecl fcn_004e4b60(int a1)
{
	Col4e4b60 c;

	if (g_772f3c == 0) {
		g_772f68 = g_6b89c0 = fcn_00459ae0(-2.25f, -0.2f, 600.0f);
		*(int*) &c = 0;
		c.b = 0;
		g_772f64 = fcn_00459870(g_772f68, 0, a1, c, 3.0f, 0, 0.8f, -0.25f);
		fcn_00459940(g_772f68, g_772f64, 0);
		fcn_00459980(g_772f68, g_772f64, 0xff, 10.0f);
	}
}
