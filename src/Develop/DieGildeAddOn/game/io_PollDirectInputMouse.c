#include "Develop/DieGildeAddOn/game/client_input.h"

extern int g_14ce8d0;
extern int g_14ce8d8;
extern int io_ActiveInputState[];
extern short io_MouseY;
extern short io_ActiveCursorX;
extern short io_ActiveCursorY;
extern int io_PolledCursorState[];
extern short io_PolledCursorY;
extern int g_6772c4;



void __cdecl io_FormatInputError(int a1, int err, char* text, ...);

/* ADDRESS: GOLDTL 0x004123a0 */
void __cdecl io_PollDirectInputMouse(void)
{
	DIMOUSESTATE state;
	POINT pt;
	INPUT_DEVICE* dev;
	INPUT_DEVICE_VTABLE* vtable;
	int err;
	short dx;
	short dy;
	HWND hwnd;

	dev = io_MouseDevice;
	vtable = dev->vtbl;
	err = vtable->GetDeviceState(dev, sizeof(state), &state);

	if (err != 0) {
		if (err == 0x8007001e)
			io_FormatInputError(0, err, "Access to Input Device Lost");
		else if (err == 0x80070057)
			io_FormatInputError(0, err, "Invalid Param");
		else if (err == 0x8007000c)
			io_FormatInputError(0, err, "Device not aquired");
		else if (err == 0x80070015)
			io_FormatInputError(0, err, "Device not initialized");
		else if (err == 0x8000000a)
			io_FormatInputError(0, err, "Data not available");
	}
	if (state.rgbButtons[0] & 0x80)
		g_14ce8d0 = 1;
	if ((state.rgbButtons[0] & 0x80) == 0) {
		g_14ce8d8 = 0;
		g_14ce8d0 = 0;
	}
	dx = (short) (io_ActiveInputState[0] + state.lX);
	dy = (short) (io_MouseY + *(short*) &state.lY);
	g_6772c4 = 1;
	io_ActiveCursorX = dx;
	*(short*) io_PolledCursorState = dx;
	io_ActiveCursorY = dy;
	io_PolledCursorY = dy;
	*(short*) io_ActiveInputState = dx;
	io_MouseY = dy;
	pt.x = dx;
	pt.y = dy;
	hwnd = io_InputHwnd;
	ClientToScreen(hwnd, &pt);
	SetCursorPos(pt.x, pt.y);
}
