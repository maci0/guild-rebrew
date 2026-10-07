typedef unsigned int (__stdcall* g_662324_f)(void*, unsigned int);
typedef unsigned int (__stdcall* g_662320_f)(unsigned int);
typedef int (__stdcall* g_66231c_f)(unsigned int, unsigned int, void*, unsigned long, unsigned int);
typedef unsigned int (__stdcall* g_662318_f)(void);
// GLOBAL: GOLDTL 0x1052c48
extern unsigned int g_1052c48[2];
// GLOBAL: GOLD 0xfe7a80
extern unsigned int g_1052c48[2];
// GLOBAL: GOLDTL 0x1052c50
extern unsigned int g_1052c50;
// GLOBAL: GOLD 0xfe7a88
extern unsigned int g_1052c50;
// GLOBAL: GOLDTL 0x6b7fc4
extern int g_6b7fc4;
// GLOBAL: GOLD 0x6333e4
extern int g_6b7fc4;
// GLOBAL: GOLDTL 0x6b7fa8
extern int g_6b7fa8;
// GLOBAL: GOLD 0x6333c8
extern int g_6b7fa8;
// GLOBAL: GOLDTL 0x662324
extern g_662324_f g_662324;
// GLOBAL: GOLD 0x5eb278
extern g_662324_f g_662324;
// GLOBAL: GOLDTL 0x662320
extern g_662320_f g_662320;
// GLOBAL: GOLD 0x5eb27c
extern g_662320_f g_662320;
// GLOBAL: GOLDTL 0x66231c
extern g_66231c_f g_66231c;
// GLOBAL: GOLD 0x5eb280
extern g_66231c_f g_66231c;
// GLOBAL: GOLDTL 0x662318
extern g_662318_f g_662318;
// GLOBAL: GOLD 0x5eb284
extern g_662318_f g_662318;
// FUNCTION: GOLD 0x0042e8c0
// FUNCTION: GOLDTL 0x42dde0

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
