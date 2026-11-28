extern int io_PolledCursorState[];
extern int io_ActiveInputState[];
extern short io_ActiveCursorX;
#include "Develop/DieGildeAddOn/game/game_data.h"
void __cdecl io_PollMouseInput(void);

struct IO_CURSOR_STATE {
	int v[0x13];
};

void __cdecl io_PollKeyboardInput(void);
void __cdecl io_PollKeyboardInput(void);

/* ADDRESS: GOLDTL 0x004125c0 */
void __cdecl io_SetMouseCursorPos(int x, int y)
{
	((short*)io_PolledCursorState)[0] = (short) x;
	((short*)io_PolledCursorState)[1] = (short) y;
	((short*)io_ActiveInputState)[0] = (short) x;
	((short*)io_ActiveInputState)[1] = (short) y;
	((short*)&io_ActiveCursorX)[0] = (short) x;
	((short*)&io_ActiveCursorX)[1] = (short) y;
	if (g_6772c4 == 0) {
		((void (__stdcall*)(int, int)) *(void**) 0x662300)(x, y);
	}
}

/* Resets the camera to its saved start state and reapplies it. */
/* ADDRESS: GOLDTL 0x00412610 */
void __cdecl io_ResetInputToCursor(void)
{
	io_PollMouseInput();
	(*(struct IO_CURSOR_STATE*)&io_ActiveCursorX) = (*(struct IO_CURSOR_STATE*)io_PolledCursorState);
	io_PollKeyboardInput();
}

/* ADDRESS: GOLDTL 0x00412630 */
void __cdecl io_PopQueuedInputState(void)
{
	int i;
	unsigned char* rec;

	if (*(int*) 0x6772c4 != 0) {
		(&io_ActiveCursorX)[0] = ((short*) io_PolledCursorState)[0];
		(&io_ActiveCursorX)[1] = ((short*) io_PolledCursorState)[1];
		(&io_ActiveCursorX)[2] = ((short*) io_PolledCursorState)[2];
	}
	i = 0;
	((int*) &io_ActiveCursorX)[3] = 0;
	((int*) &io_ActiveCursorX)[6] = 0;
	((int*) &io_ActiveCursorX)[8] = 0;
	((int*) &io_ActiveCursorX)[11] = 0;
	((int*) &io_ActiveCursorX)[12] = 0;
	((int*) &io_ActiveCursorX)[15] = 0;
	for (; i < 32; i++) {
		if (*(int*) (0x14ce9c8 + i * 0x4c) != 0) {
			rec = (unsigned char*) (0x14ce986 + i * 0x4c);
			*(int*) 0x14ce8cc = *(int*) (rec + 6);
			*(int*) 0x14ce8d0 = *(int*) (rec + 0xa);
			*(int*) 0x14ce8d4 = *(int*) (rec + 0xe);
			*(int*) 0x14ce8d8 = *(int*) (rec + 0x12);
			*(int*) 0x14ce8dc = *(int*) (rec + 0x16);
			*(int*) 0x14ce8e0 = *(int*) (rec + 0x1a);
			*(int*) 0x14ce8e4 = *(int*) (rec + 0x1e);
			*(int*) 0x14ce8e8 = *(int*) (rec + 0x22);
			*(int*) 0x14ce8ec = *(int*) (rec + 0x26);
			*(int*) 0x14ce8f0 = *(int*) (rec + 0x2a);
			*(int*) 0x14ce8f4 = *(int*) (rec + 0x2e);
			*(int*) 0x14ce8f8 = *(int*) (rec + 0x32);
			*(int*) 0x14ce8fc = *(int*) (rec + 0x36);
			*(int*) 0x14ce904 = *(int*) (rec + 0x3e);
			*(int*) 0x14ce900 = *(int*) (rec + 0x3a);
			*(short*) 0x14ce8c6 = *(short*) (rec + 0);
			*(short*) 0x14ce8c8 = *(short*) (rec + 2);
			*(short*) 0x14ce8ca = *(short*) (rec + 4);
			*(int*) (0x14ce9c8 + i * 0x4c) = 0;
			io_PollKeyboardInput();
			return;
		}
	}
	io_PollKeyboardInput();
}
