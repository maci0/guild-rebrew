#include <string.h>
extern int g_6b7fb8;
#include "Develop/DieGildeAddOn/game/game_data.h"
/* Watch the cursor and the two button click latches, then publish the new
 * /selection state into the shared UI state block. */
/* ADDRESS: GOLDTL 0x00411b80 */
void __cdecl fcn_00411b80(void)
{
	int t;
	int pressed;
	int other;
	int armed;
	int state;
	int timedout;
	int* probe;

	t = g_6b7fb8;
	if (*(int*) 0x6b5c90) {
		return;
	}
	pressed = *(int*) 0x6b5c98;
	other = *(int*) 0x6b5ca4;
	if (pressed != 0) {
		if (t - pressed > 0xf || (int) *(short*) &g_14ce920 < other - 3 ||
		    (int) *(short*) &g_14ce920 > other + 3 ||
		    (int) *(short*) &g_14ce922 > *(int*) 0x6b5ca8 + 3 ||
		    (int) *(short*) &g_14ce922 < *(int*) 0x6b5ca8 - 3) {
			g_14ce920[5] = 1;
			*(int*) 0x6b5c98 = 0;
			pressed = 0;
			*(int*) 0x6b5cac = -1;
			armed = -1;
			goto after_check;
		}
	}
	armed = *(int*) 0x6b5cac;
after_check:
	if (g_14ce920[3] && *(int*) 0x6b5c8c) {
		*(int*) 0x6b5c98 = 0;
		*(int*) 0x6b5c8c = 0;
		g_14ce920[4] = 0;
		goto label_411cbe;
	}
	if (g_14ce920[4] && !pressed) {
		other = (int) *(short*) &g_14ce920;
		*(int*) 0x6b5ca8 = (int) *(short*) &g_14ce922;
		*(int*) 0x6b5c98 = t;
		*(int*) 0x6b5ca4 = other;
	}
	if (armed != -1 && t - armed > 0x28) {
		armed = -1;
		*(int*) 0x6b5c98 = 0;
		*(int*) 0x6b5cac = -1;
	}
	if (g_14ce920[3]) {
		if (armed == -1 || 0x28 <= t - armed) {
			*(int*) 0x6b5c98 = 0;
			*(int*) 0x6b5cac = t;
			if (g_14ce920[5]) {
label_411cbe:
				g_14ce920[3] = 0;
				*(int*) 0x6b5cac = -1;
label_411cca:
				*(int*) 0x6b5c98 = 0;
				g_14ce920[5] = 0;
			} else {
				goto label_411cca;
			}
		} else {
			g_14ce920[7] = 1;
			g_14ce920[3] = 0;
			*(int*) 0x6b5cac = -1;
			*(int*) 0x6b5c98 = 0;
		}
	}
	armed = *(int*) 0x6b5c9c;
	pressed = g_14ce920[10];
	if (g_14ce920[9]) {
		if (!*(int*) 0x6b5c9c) {
			other = (int) *(short*) &g_14ce920;
			*(int*) 0x6b5ca8 = (int) *(short*) &g_14ce922;
			*(int*) 0x6b5c9c = t;
			armed = t;
			*(int*) 0x6b5ca4 = other;
			goto label_411d04;
		}
label_411d08:
		if (!g_14ce920[10] && g_14ce920[9]) {
			if (t - armed > 0xf) {
				pressed = 1;
				*(int*) 0x6b5c9c = 0;
				g_14ce920[10] = 1;
			}
			if ((int) *(short*) &g_14ce920 < other - 3 || (int) *(short*) &g_14ce920 > other + 3 || (int) *(short*) &g_14ce922 > *(int*) 0x6b5ca8 + 3 || (int) *(short*) &g_14ce922 < *(int*) 0x6b5ca8 - 3) {
				*(int*) 0x6b5c9c = 0;
				g_14ce920[10] = 1;
				pressed = 1;
			}
		}
	} else {
label_411d04:
		if (armed) {
			goto label_411d08;
		}
	}
	armed = g_14ce920[8];
	if (g_14ce920[8]) {
		if (pressed) {
			armed = 0;
			pressed = 0;
			g_14ce920[8] = 0;
			g_14ce920[10] = 0;
			g_14ce920[4] = 0;
			g_14ce920[5] = 0;
		}
		*(int*) 0x6b5c9c = 0;
	}
	state = *(int*) 0x6b5ca0;
	timedout = g_14ce920[14];
	if (g_14ce920[13]) {
		if (!*(int*) 0x6b5ca0) {
			other = (int) *(short*) &g_14ce920;
			*(int*) 0x6b5ca8 = (int) *(short*) &g_14ce922;
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
	if (!g_14ce920[14] && g_14ce920[13]) {
		if (t - state > 0xf) {
			timedout = 1;
			*(int*) 0x6b5ca0 = 0;
			g_14ce920[14] = 1;
		}
		if ((int) *(short*) &g_14ce920 < other - 3 || (int) *(short*) &g_14ce920 > other + 3 || (int) *(short*) &g_14ce922 > *(int*) 0x6b5ca8 + 3 || (int) *(short*) &g_14ce922 < *(int*) 0x6b5ca8 - 3) {
			*(int*) 0x6b5ca0 = 0;
			g_14ce920[14] = 1;
			timedout = 1;
		}
	}
label_411e58:
	if (g_14ce920[12]) {
		g_14ce920[12] = 0;
		if (timedout) {
			timedout = 0;
			g_14ce920[14] = 0;
		}
		*(int*) 0x6b5ca0 = 0;
	}
	if ((g_14ce920[3] != g_14cf900[3] || g_14ce920[4] != g_14cf900[4] || g_14ce920[5] != g_14cf900[5] || g_14ce920[7] != g_14cf900[7] ||
	    armed != g_14cf900[8] || g_14ce920[9] != g_14cf900[9] || pressed != g_14cf900[10] || g_14cf900[12] || g_14ce920[13] != g_14cf900[13] ||
	    timedout != g_14cf900[14] || g_14ce920[17] != g_14cf900[17] || g_14ce920[16] != g_14cf900[16]) && !*(int*) 0x14cf2fc) {
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
			memcpy((void*) (armed * 0x4c + 0x14ce980), (void*) &g_14ce920, 0x4c);
			*(unsigned int*) (armed * 0x4c + 0x14ce9c8) = 1;
		}
	}
	memcpy((void*) &g_14cf900, (void*) &g_14ce920, 0x4c);
}
