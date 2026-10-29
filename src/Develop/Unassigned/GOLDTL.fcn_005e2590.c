


#define RED(c) ((unsigned char) (c))
#define GREEN(c) ((unsigned char) (((unsigned short) (c)) >> 8))
#define BLUE(c) ((unsigned char) ((c) >> 16))
#define ALPHA(c) ((unsigned char) ((c) >> 24))

extern unsigned char g_7766a0[4];
extern unsigned char g_7766a4[4];
extern float g_681750;
extern float g_6819b0;

void __cdecl fcn_00427370(int);
void __cdecl fcn_0041fc80(int);
void __cdecl fcn_004c3140(int);

void __cdecl fcn_005e2590(void)
{
	float s;

	s = RED((*(unsigned long*)g_7766a0)) * (1.0f / 127.0f);
	fcn_00427370((int) (GREEN((*(unsigned long*)g_7766a0)) * s));
	fcn_0041fc80((int) (BLUE((*(unsigned long*)g_7766a0)) * s));
	fcn_004c3140((int) (GREEN((*(unsigned long*)g_7766a0)) * s));
	g_681750 = ALPHA((*(unsigned long*)g_7766a0)) * (1.0f / 127.0f);
	g_6819b0 = RED((*(unsigned long*)g_7766a4)) * 0.25f;
}
