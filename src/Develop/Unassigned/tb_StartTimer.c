typedef unsigned int (__stdcall* g_662324_f)(void*, unsigned int);
typedef unsigned int (__stdcall* g_662320_f)(unsigned int);
typedef int (__stdcall* g_66231c_f)(unsigned int, unsigned int, void*, unsigned long, unsigned int);
typedef unsigned int (__stdcall* g_662318_f)(void);
extern unsigned int tb_TimeCaps[2];
extern unsigned int tb_TimeCaps[2];
extern unsigned int tb_TimerDelay;
extern unsigned int tb_TimerDelay;
extern volatile int tb_TimerOneshot;
extern volatile int tb_TimerOneshot;
extern int tb_TimerId;
extern int tb_TimerId;
extern g_662324_f imp_timeGetDevCaps;
extern g_662324_f imp_timeGetDevCaps;
extern g_662320_f imp_timeBeginPeriod;
extern g_662320_f imp_timeBeginPeriod;
extern g_66231c_f imp_timeSetEvent;
extern g_66231c_f imp_timeSetEvent;
extern g_662318_f imp_timeGetTime;
extern g_662318_f imp_timeGetTime;



void __stdcall tb_TimerCallback(unsigned int, unsigned int, unsigned long, unsigned long, unsigned long);
void __cdecl fcn_0064d3eb(unsigned int);

/* ADDRESS: GOLDDE 0x00427bb0 */
int __cdecl tb_StartTimer(unsigned int delay, int oneshot)
{
	imp_timeGetDevCaps(tb_TimeCaps, 8);
	imp_timeBeginPeriod(tb_TimeCaps[0] + 5);
	if (delay < tb_TimeCaps[0]) {
		return 0;
	}
	tb_TimerDelay = delay;
	tb_TimerOneshot = oneshot;
	if (oneshot) {
		tb_TimerId = imp_timeSetEvent(delay, tb_TimeCaps[0] + 5, tb_TimerCallback, 0, 0);
	} else {
		tb_TimerId = imp_timeSetEvent(delay, tb_TimeCaps[0] + 5, tb_TimerCallback, 0, 1);
	}
	if (tb_TimerId == 0) {
		return 0;
	}
	fcn_0064d3eb(imp_timeGetTime());
	return 1;
}
unsigned char _dpad_1052bd0[120];
