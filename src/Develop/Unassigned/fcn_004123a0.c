#include "client_input.h"

extern int g_14ce8d0;
extern int g_14ce8d8;
extern int g_14ce920[];
extern short g_14ce922;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_14cf900[];
extern short g_14cf902;
extern int g_6772c4;



void __cdecl io_FormatInputError(int a1, int err, char* text, ...);

/* ADDRESS: GOLDTL 0x004123a0 */
void __cdecl fcn_004123a0(void)
{
	DIMOUSESTATE state;
	POINT pt;
	INPUT_DEVICE* dev;
	INPUT_DEVICE_VTABLE* vtable;
	int err;
	short dx;
	short dy;
	HWND hwnd;

	dev = g_14ce8a0;
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
	dx = (short) (g_14ce920[0] + state.lX);
	dy = (short) (g_14ce922 + *(short*) &state.lY);
	g_6772c4 = 1;
	g_14ce8c0 = dx;
	*(short*) g_14cf900 = dx;
	g_14ce8c2 = dy;
	g_14cf902 = dy;
	*(short*) g_14ce920 = dx;
	g_14ce922 = dy;
	pt.x = dx;
	pt.y = dy;
	hwnd = g_14ce89c;
	ClientToScreen(hwnd, &pt);
	SetCursorPos(pt.x, pt.y);
}
