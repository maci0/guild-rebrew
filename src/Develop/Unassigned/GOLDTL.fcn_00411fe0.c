#include "client_input.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14ce920[];
extern short g_14ce922;
extern short g_14ce924;
extern short g_14ce8c2;
extern int g_14ce8e8;
extern int g_6b5c88;
void __cdecl io_SwapMouseButtons(void);
void __cdecl fcn_00411b80(void);

typedef struct {
	int dwOfs;
	int dwData;
	int dwTimeStamp;
	int dwSequence;
	int uAppData;
} DI_OBJDATA_411FE0;

#define MIN411FE0(a, b) ((a) < (b) ? (a) : (b))
#define MAX411FE0(a, b) ((a) > (b) ? (a) : (b))

/* Reads the 0x14-byte UI event records of the active input object and applies
 * them to the cursor position and the three button latches. Cases 0/4 scale the
 * event value into the cursor delta, case 8 accumulates the wheel step, cases
 * 12/13/14 latch the three buttons. The cursor is clamped to the screen rect
 * and the whole state is published afterwards. */
/* ADDRESS: GOLDTL 0x00411fe0 */
void __cdecl fcn_00411fe0(void)
{
	DWORD count;
	DI_OBJDATA_411FE0 ev;
	int v;

	count = 1;
	((short*) g_14ce920)[3] = 0;
	((short*) g_14ce920)[4] = 0;
	((short*) g_14ce920)[5] = 0;
	if (g_14ce8a0 == 0) {
		return;
	}
	while (1) {
		g_14ce920[6] = 0;
		g_14ce920[3] = 0;
		g_14ce920[7] = 0;
		g_14ce920[11] = 0;
		g_14ce920[8] = 0;
		g_14ce920[15] = 0;
		g_14ce920[12] = 0;
		g_14ce920[16] = 0;
		g_14ce920[17] = 0;
		if (g_14ce8a0->vtbl->GetDeviceData(g_14ce8a0, 0x14, (LPDIDEVICEOBJECTDATA) &ev, &count, 0) < 0 || count == 0) {
			break;
		}
		switch (ev.dwOfs) {
		case 0:
			v = (int) ((*(int*) 0x6772b8 / 256.0f) * ev.dwData);
			*(short*) g_14ce920 += (short) v;
			((short*) g_14ce920)[3] = (short) v;
			break;
		case 4:
			v = (int) ((*(int*) 0x6772b8 / 256.0f) * ev.dwData);
			g_14ce922 += (short) v;
			((short*) g_14ce920)[4] = (short) v;
			break;
		case 8:
			v = *(int*) 0x6772b8 * ev.dwData;
			v >>= 8;
			if (v > 0) {
				g_14ce920[17] = 1;
			} else if (v < 0) {
				g_14ce920[16] = 1;
			}
			g_14ce924 += (short) v;
			((short*) g_14ce920)[5] = (short) v;
			fcn_00411b80();
			break;
		case 12:
			v = ev.dwData;
			if (v & 0x80) {
				g_14ce920[4] = 1;
				g_14ce920[3] = 0;
				if (g_14ce8e8 == 0) {
					g_14ce920[6] = 1;
				}
				io_SwapMouseButtons();
				fcn_00411b80();
			}
			if (!(v & 0x80)) {
				g_14ce920[3] = 1;
				g_14ce920[4] = 0;
				io_SwapMouseButtons();
				fcn_00411b80();
			}
			break;
		case 13:
			v = ev.dwData;
			if (v & 0x80) {
				g_14ce920[9] = 1;
				g_14ce920[8] = 0;
				g_14ce920[11] = 1;
				io_SwapMouseButtons();
				fcn_00411b80();
			}
			if (!(v & 0x80)) {
				g_14ce920[8] = 1;
				g_14ce920[9] = 0;
				io_SwapMouseButtons();
				fcn_00411b80();
			}
			break;
		case 14:
			v = ev.dwData;
			if (v & 0x80) {
				g_14ce920[13] = 1;
				g_14ce920[12] = 0;
				g_14ce920[15] = 1;
				io_SwapMouseButtons();
				fcn_00411b80();
			}
			if (!(v & 0x80)) {
				g_14ce920[12] = 1;
				g_14ce920[13] = 0;
				io_SwapMouseButtons();
				fcn_00411b80();
			}
			break;
		}
	}
	if ((int) *(short*) g_14ce920 < g_6b5c80) {
		*(short*) g_14ce920 = (short) g_6b5c80;
	}
	if ((int) *(short*) g_14ce920 > d2_MouseRightBoundary) {
		*(short*) g_14ce920 = (short) d2_MouseRightBoundary;
	}
	if ((int) g_14ce922 < d2_MouseTopBoundary) {
		g_14ce922 = (short) d2_MouseTopBoundary;
	}
	if ((int) g_14ce922 > d2_MouseBottomBoundary) {
		g_14ce922 = (short) d2_MouseBottomBoundary;
	}
	if (g_6b5c88 & 4) {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_14ce89c, &pt);
		if (g_6772c4 == 0) {
			*(short*) g_14ce920 = (short) (*(short*) g_14ce920 + pt.x - *(int*) &g_14ce8c0);
			g_14ce922 = (short) (g_14ce922 + (short) pt.y - g_14ce8c2);
			pt.x = (short) *(int*) &g_14ce8c0;
			pt.y = g_14ce8c2;
			ClientToScreen(g_14ce89c, &pt);
			SetCursorPos(pt.x, pt.y);
			fcn_00411b80();
			return;
		}
		*(short*) g_14ce920 = (short) MAX411FE0(g_6b5c80, MIN411FE0(pt.x, d2_MouseRightBoundary));
		g_14ce922 = (short) MAX411FE0(d2_MouseTopBoundary, MIN411FE0(pt.y, d2_MouseBottomBoundary));
	}
	fcn_00411b80();
}
