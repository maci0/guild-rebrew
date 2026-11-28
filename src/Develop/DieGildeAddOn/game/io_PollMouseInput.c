#include "Develop/DieGildeAddOn/game/client_input.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int io_ActiveInputState[];
extern short io_MouseY;
extern short g_14ce924;
extern short io_ActiveCursorY;
extern int g_14ce8e8;
extern int g_6b5c88;
void __cdecl io_SwapMouseButtons(void);
void __cdecl io_UpdateMouseClickState(void);

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
/* ADDRESS: GOLDDE 0x00410c40 */
void __cdecl io_PollMouseInput(void)
{
	DWORD count;
	DI_OBJDATA_411FE0 ev;
	int v;

	count = 1;
	((short*) io_ActiveInputState)[3] = 0;
	((short*) io_ActiveInputState)[4] = 0;
	((short*) io_ActiveInputState)[5] = 0;
	if (io_MouseDevice == 0) {
		return;
	}
	while (1) {
		io_ActiveInputState[6] = 0;
		io_ActiveInputState[3] = 0;
		io_ActiveInputState[7] = 0;
		io_ActiveInputState[11] = 0;
		io_ActiveInputState[8] = 0;
		io_ActiveInputState[15] = 0;
		io_ActiveInputState[12] = 0;
		io_ActiveInputState[16] = 0;
		io_ActiveInputState[17] = 0;
		if (io_MouseDevice->vtbl->GetDeviceData(io_MouseDevice, 0x14, (LPDIDEVICEOBJECTDATA) &ev, &count, 0) < 0 || count == 0) {
			break;
		}
		switch (ev.dwOfs) {
		case 0:
			v = (int) ((*(int*) 0x6772b8 / 256.0f) * ev.dwData);
			*(short*) io_ActiveInputState += (short) v;
			((short*) io_ActiveInputState)[3] = (short) v;
			break;
		case 4:
			v = (int) ((*(int*) 0x6772b8 / 256.0f) * ev.dwData);
			io_MouseY += (short) v;
			((short*) io_ActiveInputState)[4] = (short) v;
			break;
		case 8:
			v = *(int*) 0x6772b8 * ev.dwData;
			v >>= 8;
			if (v > 0) {
				io_ActiveInputState[17] = 1;
			} else if (v < 0) {
				io_ActiveInputState[16] = 1;
			}
			g_14ce924 += (short) v;
			((short*) io_ActiveInputState)[5] = (short) v;
			io_UpdateMouseClickState();
			break;
		case 12:
			v = ev.dwData;
			if (v & 0x80) {
				io_ActiveInputState[4] = 1;
				io_ActiveInputState[3] = 0;
				if (g_14ce8e8 == 0) {
					io_ActiveInputState[6] = 1;
				}
				io_SwapMouseButtons();
				io_UpdateMouseClickState();
			}
			if (!(v & 0x80)) {
				io_ActiveInputState[3] = 1;
				io_ActiveInputState[4] = 0;
				io_SwapMouseButtons();
				io_UpdateMouseClickState();
			}
			break;
		case 13:
			v = ev.dwData;
			if (v & 0x80) {
				io_ActiveInputState[9] = 1;
				io_ActiveInputState[8] = 0;
				io_ActiveInputState[11] = 1;
				io_SwapMouseButtons();
				io_UpdateMouseClickState();
			}
			if (!(v & 0x80)) {
				io_ActiveInputState[8] = 1;
				io_ActiveInputState[9] = 0;
				io_SwapMouseButtons();
				io_UpdateMouseClickState();
			}
			break;
		case 14:
			v = ev.dwData;
			if (v & 0x80) {
				io_ActiveInputState[13] = 1;
				io_ActiveInputState[12] = 0;
				io_ActiveInputState[15] = 1;
				io_SwapMouseButtons();
				io_UpdateMouseClickState();
			}
			if (!(v & 0x80)) {
				io_ActiveInputState[12] = 1;
				io_ActiveInputState[13] = 0;
				io_SwapMouseButtons();
				io_UpdateMouseClickState();
			}
			break;
		}
	}
	if ((int) *(short*) io_ActiveInputState < g_6b5c80) {
		*(short*) io_ActiveInputState = (short) g_6b5c80;
	}
	if ((int) *(short*) io_ActiveInputState > d2_MouseRightBoundary) {
		*(short*) io_ActiveInputState = (short) d2_MouseRightBoundary;
	}
	if ((int) io_MouseY < d2_MouseTopBoundary) {
		io_MouseY = (short) d2_MouseTopBoundary;
	}
	if ((int) io_MouseY > d2_MouseBottomBoundary) {
		io_MouseY = (short) d2_MouseBottomBoundary;
	}
	if (g_6b5c88 & 4) {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(io_InputHwnd, &pt);
		if (g_6772c4 == 0) {
			*(short*) io_ActiveInputState = (short) (*(short*) io_ActiveInputState + pt.x - *(int*) &io_ActiveCursorX);
			io_MouseY = (short) (io_MouseY + (short) pt.y - io_ActiveCursorY);
			pt.x = (short) *(int*) &io_ActiveCursorX;
			pt.y = io_ActiveCursorY;
			ClientToScreen(io_InputHwnd, &pt);
			SetCursorPos(pt.x, pt.y);
			io_UpdateMouseClickState();
			return;
		}
		*(short*) io_ActiveInputState = (short) MAX411FE0(g_6b5c80, MIN411FE0(pt.x, d2_MouseRightBoundary));
		io_MouseY = (short) MAX411FE0(d2_MouseTopBoundary, MIN411FE0(pt.y, d2_MouseBottomBoundary));
	}
	io_UpdateMouseClickState();
}
