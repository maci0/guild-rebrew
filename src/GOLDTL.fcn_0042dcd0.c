extern int g_6b7fbc;

// SIZE 0xc
struct tick_42dcd0 {
	void (__cdecl* fn)(void);
	unsigned int period;
	int paused;
};

extern volatile int g_6b7fb8;
extern volatile int g_6b7fc0;
extern struct tick_42dcd0 g_1052c60[32];
extern volatile unsigned int g_6b7fac;
extern volatile int g_6b7fb0;
extern volatile int g_6b7fb4;
extern volatile char g_6b7fc8;
extern int g_6b7fcc;
extern volatile int g_6b7fc4;
extern unsigned int g_1052c48;
extern unsigned int g_1052c50;
extern unsigned int g_6b7fa8;

typedef void (__stdcall* timecb_42dcd0)(unsigned int, unsigned int, unsigned long, unsigned long, unsigned long);

__declspec(dllimport) unsigned int __stdcall timeSetEvent(unsigned int, unsigned int, timecb_42dcd0, unsigned long, unsigned int);

// FUNCTION: GOLD 0x0042e7b0
// SIZE: 262
// FUNCTION: GOLDTL 0x42dcd0
// SIZE: 262

/* Multimedia timer tick: runs the periodic callbacks and re-arms the
 * one-shot timer. */
void __stdcall fcn_0042dcd0(unsigned int id, unsigned int msg, unsigned long user, unsigned long dw1, unsigned long dw2)
{
	int i;

	if (g_6b7fbc != 0) {
		return;
	}
	g_6b7fbc = 1;
	g_6b7fb8++;
	if (g_6b7fc0 == 0) {
		for (i = 0; i < 32; i++) {
			if (g_1052c60[i].fn != 0 && g_6b7fac % g_1052c60[i].period == 0 && g_1052c60[i].paused == 0) {
				g_1052c60[i].fn();
			}
		}
		if (g_6b7fac % 3 == 0) {
			g_6b7fb0++;
		}
		if (g_6b7fac & 1) {
			g_6b7fb4++;
		}
		if (g_6b7fc8 != 0) {
			if (++g_6b7fcc % 20 == 0) {
				g_6b7fac++;
			}
		} else {
			g_6b7fac++;
		}
	}
	if (g_6b7fc4 != 0) {
		g_6b7fa8 = timeSetEvent(g_1052c50, g_1052c48 + 5, fcn_0042dcd0, 0, 0);
	}
	g_6b7fbc = 0;
}
