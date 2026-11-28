#include <string.h>
extern volatile int tb_TimerTicks;
extern int g_6b5c8c;
#include "Develop/DieGildeAddOn/game/game_data.h"
/* Watch the cursor and the two button click latches, then publish the new
 * /selection state into the shared UI state block. */
/* ADDRESS: GOLDTL 0x00411b80 */
/* ADDRESS: GOLDDE 0x004107e0 */
void __cdecl io_UpdateMouseClickState(void)
{
	int t;
	int pressed;
	int other;
	int armed;
	int state;
	int timedout;
	int* probe;

	t = tb_TimerTicks;
	if (*(int*) 0x6b5c90) {
		return;
	}
	pressed = *(int*) 0x6b5c98;
	other = *(int*) 0x6b5ca4;
	if (pressed != 0) {
		if (t - 0xf < pressed || (int) *(short*) &io_ActiveInputState < other - 3 ||
		    (int) *(short*) &io_ActiveInputState > other + 3 ||
		    (int) *(short*) &io_MouseY > *(int*) 0x6b5ca8 + 3 ||
		    (int) *(short*) &io_MouseY < *(int*) 0x6b5ca8 - 3) {
			io_ActiveInputState[5] = 1;
			*(int*) 0x6b5c98 = 0;
			pressed = 0;
			*(int*) 0x6b5cac = -1;
			armed = -1;
			goto after_check;
		}
	}
	armed = *(int*) 0x6b5cac;
after_check:
	if (io_ActiveInputState[3] && g_6b5c8c) {
		*(int*) 0x6b5c98 = 0;
		g_6b5c8c = 0;
		io_ActiveInputState[4] = 0;
		goto label_411cbe;
	}
	if (io_ActiveInputState[4] && !pressed) {
		other = (int) *(short*) &io_ActiveInputState;
		*(int*) 0x6b5ca8 = (int) *(short*) &io_MouseY;
		*(int*) 0x6b5c98 = t;
		*(int*) 0x6b5ca4 = other;
	}
	if (armed != -1 && t - armed > 0x28) {
		armed = -1;
		*(int*) 0x6b5c98 = 0;
		*(int*) 0x6b5cac = -1;
	}
	if (io_ActiveInputState[3]) {
		if (armed == -1 || 0x28 <= t - armed) {
			*(int*) 0x6b5c98 = 0;
			*(int*) 0x6b5cac = t;
			if (io_ActiveInputState[5]) {
label_411cbe:
				io_ActiveInputState[3] = 0;
				*(int*) 0x6b5cac = -1;
label_411cca:
				*(int*) 0x6b5c98 = 0;
				io_ActiveInputState[5] = 0;
			} else {
				goto label_411cca;
			}
		} else {
			io_ActiveInputState[7] = 1;
			io_ActiveInputState[3] = 0;
			*(int*) 0x6b5cac = -1;
			*(int*) 0x6b5c98 = 0;
		}
	}
	armed = *(int*) 0x6b5c9c;
	pressed = io_ActiveInputState[10];
	if (io_ActiveInputState[9]) {
		if (!*(int*) 0x6b5c9c) {
			other = (int) *(short*) &io_ActiveInputState;
			*(int*) 0x6b5ca8 = (int) *(short*) &io_MouseY;
			*(int*) 0x6b5c9c = t;
			armed = t;
			*(int*) 0x6b5ca4 = other;
			goto label_411d04;
		}
label_411d08:
		if (!io_ActiveInputState[10] && io_ActiveInputState[9]) {
			if (t - armed > 0xf) {
				pressed = 1;
				*(int*) 0x6b5c9c = 0;
				io_ActiveInputState[10] = 1;
			}
			if ((int) *(short*) &io_ActiveInputState < other - 3 || (int) *(short*) &io_ActiveInputState > other + 3 || (int) *(short*) &io_MouseY > *(int*) 0x6b5ca8 + 3 ||
				(int) *(short*) &io_MouseY < *(int*) 0x6b5ca8 - 3) {
				*(int*) 0x6b5c9c = 0;
				io_ActiveInputState[10] = 1;
				pressed = 1;
			}
		}
	} else {
label_411d04:
		if (armed) {
			goto label_411d08;
		}
	}
	armed = io_ActiveInputState[8];
	if (io_ActiveInputState[8]) {
		if (pressed) {
			armed = 0;
			pressed = 0;
			io_ActiveInputState[8] = 0;
			io_ActiveInputState[10] = 0;
			io_ActiveInputState[4] = 0;
			io_ActiveInputState[5] = 0;
		}
		*(int*) 0x6b5c9c = 0;
	}
	state = *(int*) 0x6b5ca0;
	timedout = io_ActiveInputState[14];
	if (io_ActiveInputState[13]) {
		if (!*(int*) 0x6b5ca0) {
			other = (int) *(short*) &io_ActiveInputState;
			*(int*) 0x6b5ca8 = (int) *(short*) &io_MouseY;
			*(int*) 0x6b5ca0 = t;
			state = t;
			*(int*) 0x6b5ca4 = other;
			goto label_411ddd;
		}
	} else {
label_411ddd:
		if (!state) {
			goto label_411e58;
		}
	}
	if (!io_ActiveInputState[14] && io_ActiveInputState[13]) {
		if (t - state > 0xf) {
			timedout = 1;
			*(int*) 0x6b5ca0 = 0;
			io_ActiveInputState[14] = 1;
		}
		if ((int) *(short*) &io_ActiveInputState < other - 3 || (int) *(short*) &io_ActiveInputState > other + 3 || (int) *(short*) &io_MouseY > *(int*) 0x6b5ca8 + 3 ||
			(int) *(short*) &io_MouseY < *(int*) 0x6b5ca8 - 3) {
			*(int*) 0x6b5ca0 = 0;
			io_ActiveInputState[14] = 1;
			timedout = 1;
		}
	}
label_411e58:
	if (io_ActiveInputState[12]) {
		io_ActiveInputState[12] = 0;
		if (timedout) {
			timedout = 0;
			io_ActiveInputState[14] = 0;
		}
		*(int*) 0x6b5ca0 = 0;
	}
	if ((io_ActiveInputState[3] != io_PolledCursorState[3] || io_ActiveInputState[4] != io_PolledCursorState[4] || io_ActiveInputState[5] != io_PolledCursorState[5] ||
		io_ActiveInputState[7] != io_PolledCursorState[7] ||
	    armed != io_PolledCursorState[8] || io_ActiveInputState[9] != io_PolledCursorState[9] || pressed != io_PolledCursorState[10] || io_PolledCursorState[12] ||
	    	io_ActiveInputState[13] != io_PolledCursorState[13] ||
	    timedout != io_PolledCursorState[14] || io_ActiveInputState[17] != io_PolledCursorState[17] || io_ActiveInputState[16] != io_PolledCursorState[16]) && !*(int*) 0x14cf2fc) {
		probe = (int*) 0x14cf2fc;
		armed = 0x1f;
		do {
			probe = &probe[-0x13];
			armed -= 1;
			if ((int) probe < 0x14ce9c8) {
				armed = 0;
				goto label_411f42;
			}
		} while (!*probe);
		if (armed < 0x1f) {
label_411f42:
			armed += 1;
			memcpy((void*) (armed * 0x4c + 0x14ce980), (void*) &io_ActiveInputState, 0x4c);
			*(unsigned int*) (armed * 0x4c + 0x14ce9c8) = 1;
		}
	}
	memcpy((void*) &io_PolledCursorState, (void*) &io_ActiveInputState, 0x4c);
}
