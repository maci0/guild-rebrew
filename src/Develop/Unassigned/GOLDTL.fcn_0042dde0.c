typedef unsigned int (__stdcall* g_662324_f)(void*, unsigned int);
typedef unsigned int (__stdcall* g_662320_f)(unsigned int);
typedef int (__stdcall* g_66231c_f)(unsigned int, unsigned int, void*, unsigned long, unsigned int);
typedef unsigned int (__stdcall* g_662318_f)(void);
extern unsigned int g_1052c48[2];
extern unsigned int g_1052c48[2];
extern unsigned int g_1052c50;
extern unsigned int g_1052c50;
extern int g_6b7fc4;
extern int g_6b7fc4;
extern int g_6b7fa8;
extern int g_6b7fa8;
extern g_662324_f g_662324;
extern g_662324_f g_662324;
extern g_662320_f g_662320;
extern g_662320_f g_662320;
extern g_66231c_f g_66231c;
extern g_66231c_f g_66231c;
extern g_662318_f g_662318;
extern g_662318_f g_662318;



void __stdcall fcn_0042dcd0(unsigned int, unsigned int, unsigned long, unsigned long, unsigned long);
void __cdecl fcn_0064d3eb(unsigned int);

int __cdecl fcn_0042dde0(unsigned int delay, int oneshot)
{
	g_662324(g_1052c48, 8);
	g_662320(g_1052c48[0] + 5);
	if (delay < g_1052c48[0]) {
		return 0;
	}
	g_1052c50 = delay;
	g_6b7fc4 = oneshot;
	if (oneshot) {
		g_6b7fa8 = g_66231c(delay, g_1052c48[0] + 5, fcn_0042dcd0, 0, 0);
	} else {
		g_6b7fa8 = g_66231c(delay, g_1052c48[0] + 5, fcn_0042dcd0, 0, 1);
	}
	if (g_6b7fa8 == 0) {
		return 0;
	}
	fcn_0064d3eb(g_662318());
	return 1;
}
unsigned char _dpad_1052bd0[120];
