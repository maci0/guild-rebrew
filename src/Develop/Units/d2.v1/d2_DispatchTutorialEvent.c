#include "Develop/DieGildeAddOn/game/game_data.h"
extern volatile int tb_TimerPaused;

// SIZE 0x40
struct cb_57eba0 {
	char pad[0x3c];
	int (__cdecl* fn)(int*);
};

// SIZE 0x1c
struct host_57eba0 {
	char pad[0x18];
	struct cb_57eba0* cb;
};

extern int* d2_TutorialState;


/* ADDRESS: GOLDTL 0x0057eba0 */
/* ADDRESS: GOLDDE 0x00564970 */
int __cdecl d2_DispatchTutorialEvent(int a, int b, int c, int d)
{
	int buf[4];

	if (d2_TutorialActive == 0) {
		return 1;
	}
	if (((struct host_57eba0*)d2_TutorialState)->cb == 0) {
		return 1;
	}
	if (tb_TimerPaused != 0) {
		return 0;
	}
	if (((struct host_57eba0*)d2_TutorialState)->cb->fn == 0) {
		return 1;
	}
	buf[0] = a;
	buf[1] = b;
	buf[2] = c;
	buf[3] = d;
	return ((struct host_57eba0*)d2_TutorialState)->cb->fn(buf);
}
