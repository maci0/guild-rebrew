// FUNCTION: GOLDTL 0x537210
// SIZE: 257

extern int g_7766a8;
extern int g_7e46ac;
extern char g_774660;
extern float g_675308;
extern char g_14cf950;
extern int g_14ce8cc;
extern int g_14ce8e0;
extern int g_774654;
extern float g_665e40;
extern double g_662ad8;
extern char g_6a33b4[];

int __cdecl fcn_0057ec20(int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00519190(int);
int __cdecl fcn_005373e0(void (__cdecl*)(void), int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_00537210(void)
{
	int saved;
	int flags;
	int h;

	saved = g_7766a8;
	flags = g_7e46ac;
	if (fcn_0057ec20(8) != 0) {
		fcn_0057e880(0xb, 0, 0, 0);
		flags = (flags & 0xffffc3e7) | 0xc0;
		g_774660 = 1;
		g_7766a8 = 0x2ee;
		g_675308 = 4.9375f;
		h = fcn_00470820(0, 0, g_6a33b4);
		fcn_00471b60(h);
		fcn_00519190(0x82);
		while (fcn_005373e0(fcn_00537210, flags) != 0) {
			if (g_14cf950 != 0 || g_14ce8cc != 0 || g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		}
		g_7766a8 = saved;
		g_774660 = 0;
		g_675308 = (float) (saved * g_665e40 + g_662ad8);
		fcn_00471e30(h);
		fcn_0057e880(0xb, 0, 1, 0);
	}
}
