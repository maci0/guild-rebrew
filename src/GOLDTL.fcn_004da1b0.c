extern volatile unsigned int g_6b7fac;
extern unsigned int g_772f54;
extern int g_77250c;
extern char g_68bfd0[];

void __cdecl fcn_00472880(int c);
int __cdecl fcn_0064d41a(char*, const char*, ...);
void __cdecl fcn_0046bd20(int, int, int, int, int, char*, int);

// FUNCTION: GOLDTL 0x004da1b0
// SIZE: 206
void __cdecl fcn_004da1b0(void)
{
	char buf[0x80];

	fcn_00472880(0x54);
	fcn_0064d41a(buf, g_68bfd0, (g_6b7fac - g_772f54) * 14 / 60000, (g_6b7fac - g_772f54) * 14 / 1000 % 60, (g_6b7fac - g_772f54) * 14 % 1000);
	fcn_0046bd20(0, 10, 200, 0x18, g_77250c, buf, 0x30);
}
