extern volatile int g_6b7fbc;

#include "Develop/DieGildeAddOn/game/client_timer.h"

extern volatile int tb_TimerTicks;
extern volatile int tb_TimerPaused;
extern volatile int gm_GameTicks;
extern volatile int g_6b7fb0;
extern volatile int g_6b7fb4;
extern volatile char g_6b7fc8;
extern volatile int g_6b7fcc;
extern volatile int tb_TimerOneshot;
extern unsigned int tb_TimeCaps[2];
extern unsigned int tb_TimerDelay;
extern int tb_TimerId;

typedef void (__stdcall* MM_TIMER_CALLBACK)(unsigned int, unsigned int, unsigned long, unsigned long, unsigned long);

__declspec(dllimport) unsigned int __stdcall timeSetEvent(unsigned int, unsigned int, MM_TIMER_CALLBACK, unsigned long, unsigned int);


/* Multimedia timer tick: runs the periodic callbacks and re-arms the
 * one-shot timer. */
/* ADDRESS: GOLDTL 0x0042dcd0 */
/* ADDRESS: GOLDDE 0x00427aa0 */
void __stdcall tb_TimerCallback(unsigned int id, unsigned int msg, unsigned long user, unsigned long dw1, unsigned long dw2)
{
	int i;
	int tick;

	if (g_6b7fbc != 0) {
		return;
	}
	tick = tb_TimerTicks;
	g_6b7fbc = 1;
	tb_TimerTicks = tick + 1;
	if (tb_TimerPaused == 0) {
		for (i = 0; i < 32; i++) {
			if (tb_TimerCallbacks[i].funktion != 0 && (unsigned int) gm_GameTicks % tb_TimerCallbacks[i].periode == 0
			    && tb_TimerCallbacks[i].pausiert == 0) {
				tb_TimerCallbacks[i].funktion();
			}
		}
		if ((unsigned int) gm_GameTicks % 3 == 0) {
			g_6b7fb0++;
		}
		if ((unsigned int) gm_GameTicks & 1) {
			g_6b7fb4++;
		}
		if (g_6b7fc8 != 0) {
			tick = g_6b7fcc;
		g_6b7fcc = ++tick;
		if (tick % 20 == 0) {
				gm_GameTicks = (unsigned int) gm_GameTicks + 1;
			}
		} else {
			gm_GameTicks = (unsigned int) gm_GameTicks + 1;
		}
	}
	if (tb_TimerOneshot != 0) {
		(*(unsigned int*)&tb_TimerId) = timeSetEvent(tb_TimerDelay, (*(unsigned int*)tb_TimeCaps) + 5, tb_TimerCallback, 0, 0);
	}
	g_6b7fbc = 0;
}
unsigned char _dpad_fe7a20[128] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_fe7aa0[122240];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_1005764[4];
unsigned char _dpad_100576c[20];
unsigned char _dpad_1005784[152];
#endif
