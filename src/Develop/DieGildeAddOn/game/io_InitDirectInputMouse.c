

#include "Develop/DieGildeAddOn/game/client_input.h"


























// SIZE 0x14
typedef struct {
	DWORD dwSize;
	DWORD dwHeaderSize;
	DWORD dwObj;
	DWORD dwHow;
	DWORD dwData;
} PropDword;


extern HINSTANCE g_14ce8a4;
extern int g_6b5c88;



extern int io_ActiveInputState[];
extern short io_MouseY;
extern short g_14ce924;
extern char g_66cdb0[];
extern char g_66cc50[];
extern char g_66cc40[];
extern char g_6711b4[];
extern char g_670fac[];
extern char g_67747c[];
extern char g_67745c[];
extern char g_67743c[];
extern char g_67741c[];
extern char g_677404[];
extern char g_6773e0[];
extern char g_6773b4[];
extern char g_677380[];
extern char g_677354[];
extern char g_677334[];
extern char g_677318[];
extern char g_6772f8[];
extern char g_6772d8[];

HRESULT __stdcall DirectInput8Create(HINSTANCE hinst, DWORD version, const void* iid, void** out, void* outer);
void __cdecl io_FormatInputError(int a1, int a2, char* fmt, ...);


int __cdecl io_BuildKeyTranslateTable(void);

int __cdecl io_InitDirectInputMouse(HWND hwnd, HINSTANCE hinst, int flags)
{
	HRESULT hr;
	PropDword dipdw;

	g_14ce8a4 = hinst;
	g_6b5c88 = flags;
	io_InputHwnd = hwnd;
	hr = DirectInput8Create(hinst, 0x800, g_66cdb0, (void**) &io_DirectInput, 0);
	if (hr < 0) {
		if (hr == 0x80070481) {
			io_FormatInputError(0, hr, g_67747c);
			return 0;
		}
		if (hr == 0x80070057) {
			io_FormatInputError(0, hr, g_67745c);
			return 0;
		}
		if (hr == 0x8007047e) {
			io_FormatInputError(0, hr, g_67743c);
			return 0;
		}
		if (hr == 0x8007000e) {
			io_FormatInputError(0, hr, g_67741c);
		}
		return 0;
	}
	hr = io_DirectInput->vtbl->CreateDevice(io_DirectInput, g_66cc50, &io_MouseDevice, 0);
	if (hr < 0) {
		io_FormatInputError(0, hr, g_677404);
		return 0;
	}
	hr = io_MouseDevice->vtbl->SetDataFormat(io_MouseDevice, g_6711b4);
	if (hr < 0) {
		io_FormatInputError(0, hr, g_6773e0);
		return 0;
	}
	if (flags & 2) {
		hr = io_MouseDevice->vtbl->SetCooperativeLevel(io_MouseDevice, hwnd, 0xa);
	} else {
		hr = io_MouseDevice->vtbl->SetCooperativeLevel(io_MouseDevice, hwnd, 5);
	}
	if (hr != 0) {
		if (hr == 0x80070057) {
			io_FormatInputError(0, hr, g_6773b4);
		} else if (hr == 0x80070015) {
			io_FormatInputError(0, hr, g_677380);
		} else {
			io_FormatInputError(0, hr, g_677354);
		}
	}
	hr = io_MouseDevice->vtbl->SetEventNotification(io_MouseDevice, 0);
	if (hr != 0) {
		io_FormatInputError(0, hr, g_677334);
		return 0;
	}
	dipdw.dwSize = sizeof(PropDword);
	dipdw.dwHeaderSize = 0x10;
	dipdw.dwObj = 0;
	dipdw.dwHow = 0;
	dipdw.dwData = 0x80;
	hr = io_MouseDevice->vtbl->SetProperty(io_MouseDevice, (const void*) 1, &dipdw);
	if (hr < 0) {
		io_FormatInputError(0, hr, g_677318);
		return 0;
	}
	io_AcquireKeyboard(1);
	*(short*) io_ActiveInputState = 200;
	io_MouseY = 200;
	g_14ce924 = 0;
	hr = io_DirectInput->vtbl->CreateDevice(io_DirectInput, g_66cc40, &io_KeyboardDevice, 0);
	if (hr < 0) {
		io_FormatInputError(0, hr, g_6772f8);
		return 0;
	}
	hr = io_KeyboardDevice->vtbl->SetDataFormat(io_KeyboardDevice, g_670fac);
	if (hr < 0) {
		io_FormatInputError(0, hr, g_6772d8);
		return 0;
	}
	if (flags & 1) {
		hr = io_KeyboardDevice->vtbl->SetCooperativeLevel(io_KeyboardDevice, hwnd, 0x15);
	} else {
		hr = io_KeyboardDevice->vtbl->SetCooperativeLevel(io_KeyboardDevice, hwnd, 0xa);
	}
	if (hr != 0) {
		return 0;
	}
	dipdw.dwSize = sizeof(PropDword);
	dipdw.dwHeaderSize = 0x10;
	dipdw.dwObj = 0;
	dipdw.dwHow = 0;
	dipdw.dwData = 0x80;
	if (io_KeyboardDevice->vtbl->SetProperty(io_KeyboardDevice, (const void*) 1, &dipdw) < 0) {
		return 0;
	}
	io_AcquireMouse(1);
	io_BuildKeyTranslateTable();
	return 1;
}
