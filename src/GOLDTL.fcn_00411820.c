// FUNCTION: GOLDTL 0x00411820

#include <windows.h>

typedef struct Com Com;

// SIZE 0x38
typedef struct {
	void* QueryInterface;
	void* AddRef;
	void* Release;
	HRESULT (__stdcall* CreateDevice)(Com* self, const void* guid, Com** dev, void* outer);
	void* m10;
	void* m14;
	HRESULT (__stdcall* SetProperty)(Com* self, const void* prop, void* hdr);
	void* m1c;
	void* m20;
	void* m24;
	void* m28;
	HRESULT (__stdcall* SetDataFormat)(Com* self, const void* fmt);
	HRESULT (__stdcall* SetEventNotification)(Com* self, HANDLE ev);
	HRESULT (__stdcall* SetCooperativeLevel)(Com* self, HWND hwnd, DWORD flags);
} ComVtbl;

// SIZE 0x4
struct Com {
	ComVtbl* vtbl;
};

// SIZE 0x14
typedef struct {
	DWORD dwSize;
	DWORD dwHeaderSize;
	DWORD dwObj;
	DWORD dwHow;
	DWORD dwData;
} PropDword;

extern HWND g_14ce89c;
extern HINSTANCE g_14ce8a4;
extern int g_6b5c88;
extern Com* g_14cf954;
extern Com* g_14ce8a0;
extern Com* g_14ce90c;
extern int g_14ce920[];
extern short g_14ce922;
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
void __cdecl fcn_00411780(int a1, int a2, char* fmt, ...);
int __cdecl fcn_004117c0(int a1);
int __cdecl fcn_004117f0(int a1);
int __cdecl fcn_00411590(void);

int __cdecl fcn_00411820(HWND hwnd, HINSTANCE hinst, int flags)
{
	HRESULT hr;
	PropDword dipdw;

	g_14ce8a4 = hinst;
	g_6b5c88 = flags;
	g_14ce89c = hwnd;
	hr = DirectInput8Create(hinst, 0x800, g_66cdb0, (void**) &g_14cf954, 0);
	if (hr < 0) {
		if (hr == 0x80070481) {
			fcn_00411780(0, hr, g_67747c);
			return 0;
		}
		if (hr == 0x80070057) {
			fcn_00411780(0, hr, g_67745c);
			return 0;
		}
		if (hr == 0x8007047e) {
			fcn_00411780(0, hr, g_67743c);
			return 0;
		}
		if (hr == 0x8007000e) {
			fcn_00411780(0, hr, g_67741c);
		}
		return 0;
	}
	hr = g_14cf954->vtbl->CreateDevice(g_14cf954, g_66cc50, &g_14ce8a0, 0);
	if (hr < 0) {
		fcn_00411780(0, hr, g_677404);
		return 0;
	}
	hr = g_14ce8a0->vtbl->SetDataFormat(g_14ce8a0, g_6711b4);
	if (hr < 0) {
		fcn_00411780(0, hr, g_6773e0);
		return 0;
	}
	if (flags & 2) {
		hr = g_14ce8a0->vtbl->SetCooperativeLevel(g_14ce8a0, hwnd, 0xa);
	} else {
		hr = g_14ce8a0->vtbl->SetCooperativeLevel(g_14ce8a0, hwnd, 5);
	}
	if (hr != 0) {
		if (hr == 0x80070057) {
			fcn_00411780(0, hr, g_6773b4);
		} else if (hr == 0x80070015) {
			fcn_00411780(0, hr, g_677380);
		} else {
			fcn_00411780(0, hr, g_677354);
		}
	}
	hr = g_14ce8a0->vtbl->SetEventNotification(g_14ce8a0, 0);
	if (hr != 0) {
		fcn_00411780(0, hr, g_677334);
		return 0;
	}
	dipdw.dwSize = sizeof(PropDword);
	dipdw.dwHeaderSize = 0x10;
	dipdw.dwObj = 0;
	dipdw.dwHow = 0;
	dipdw.dwData = 0x80;
	hr = g_14ce8a0->vtbl->SetProperty(g_14ce8a0, (const void*) 1, &dipdw);
	if (hr < 0) {
		fcn_00411780(0, hr, g_677318);
		return 0;
	}
	fcn_004117c0(1);
	*(short*) g_14ce920 = 200;
	g_14ce922 = 200;
	g_14ce924 = 0;
	hr = g_14cf954->vtbl->CreateDevice(g_14cf954, g_66cc40, &g_14ce90c, 0);
	if (hr < 0) {
		fcn_00411780(0, hr, g_6772f8);
		return 0;
	}
	hr = g_14ce90c->vtbl->SetDataFormat(g_14ce90c, g_670fac);
	if (hr < 0) {
		fcn_00411780(0, hr, g_6772d8);
		return 0;
	}
	if (flags & 1) {
		hr = g_14ce90c->vtbl->SetCooperativeLevel(g_14ce90c, hwnd, 0x15);
	} else {
		hr = g_14ce90c->vtbl->SetCooperativeLevel(g_14ce90c, hwnd, 0xa);
	}
	if (hr != 0) {
		return 0;
	}
	dipdw.dwSize = sizeof(PropDword);
	dipdw.dwHeaderSize = 0x10;
	dipdw.dwObj = 0;
	dipdw.dwHow = 0;
	dipdw.dwData = 0x80;
	if (g_14ce90c->vtbl->SetProperty(g_14ce90c, (const void*) 1, &dipdw) < 0) {
		return 0;
	}
	fcn_004117f0(1);
	fcn_00411590();
	return 1;
}
