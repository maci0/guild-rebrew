// FUNCTION: GOLDTL 0x42dde0
// SIZE: 119

extern unsigned int g_1052c48[2];
extern unsigned int g_1052c50;
extern int g_6b7fc4;
extern int g_6b7fa8;

void __stdcall fcn_0042dcd0(unsigned int, unsigned int, unsigned long, unsigned long, unsigned long);
void __cdecl fcn_0064d3eb(unsigned int);
typedef unsigned int (__stdcall* fcn_0042dde0_caps)(void*, unsigned int);
typedef unsigned int (__stdcall* fcn_0042dde0_period)(unsigned int);
typedef int (__stdcall* fcn_0042dde0_event)(unsigned int, unsigned int, void*, unsigned long, unsigned int);
typedef unsigned int (__stdcall* fcn_0042dde0_time)(void);

int __cdecl fcn_0042dde0(unsigned int delay, int oneshot)
{
	(*(fcn_0042dde0_caps*) 0x662324)(g_1052c48, 8);
	(*(fcn_0042dde0_period*) 0x662320)(g_1052c48[0] + 5);
	if (delay < g_1052c48[0]) {
		return 0;
	}
	g_1052c50 = delay;
	g_6b7fc4 = oneshot;
	if (oneshot) {
		g_6b7fa8 = (*(fcn_0042dde0_event*) 0x66231c)(delay, g_1052c48[0] + 5, fcn_0042dcd0, 0, 0);
	} else {
		g_6b7fa8 = (*(fcn_0042dde0_event*) 0x66231c)(delay, g_1052c48[0] + 5, fcn_0042dcd0, 0, 1);
	}
	if (g_6b7fa8 == 0) {
		return 0;
	}
	fcn_0064d3eb((*(fcn_0042dde0_time*) 0x662318)());
	return 1;
}
