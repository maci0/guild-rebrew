// FUNCTION: GOLDTL 0x005e2590
// SIZE: 184

#define RED(c) ((unsigned char) (c))
#define GREEN(c) ((unsigned char) (((unsigned short) (c)) >> 8))
#define BLUE(c) ((unsigned char) ((c) >> 16))
#define ALPHA(c) ((unsigned char) ((c) >> 24))

extern unsigned long g_7766a0;
extern unsigned long g_7766a4;
extern float g_681750;
extern float g_6819b0;

void __cdecl fcn_004238d0(int);
void __cdecl fcn_0041fc80(int);
void __cdecl fcn_0041fd30(int);

void __cdecl fcn_005e2590(void)
{
	float s;

	s = RED(g_7766a0) * (1.0f / 127.0f);
	fcn_004238d0((int) (GREEN(g_7766a0) * s));
	fcn_0041fc80((int) (BLUE(g_7766a0) * s));
	fcn_0041fd30((int) (GREEN(g_7766a0) * s));
	g_681750 = ALPHA(g_7766a0) * (1.0f / 127.0f);
	g_6819b0 = RED(g_7766a4) * 0.25f;
}
