


extern unsigned char g_7747b0;
extern int g_6b5c94;
extern char g_68a9cc[];
extern int g_7766a8;
extern float g_675308;
extern int g_7766b0;
extern int g_7766ac;
extern int g_6a256c;

void __cdecl fcn_00410610(int);

void __cdecl fcn_005e2510(void)
{
	g_6b5c94 = 0;
	if (g_7747b0 & 4) {
		g_675308 = (float) (((*(unsigned int*)g_68a9cc) * 0.25 + 0.5) * 0.8);
	}
	else {
		g_675308 = (float) (g_7766a8 * 0.00625f + 0.25);
	}
	fcn_00410610(g_7766b0 - 0x40);
	g_6a256c = 100 - (g_7766ac & 0xff);
}
