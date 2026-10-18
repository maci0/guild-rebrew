#include "client_d3_dialog.h"
#include "Develop/Units/d3/d3_d3d.h"

#include <string.h>

/* Declaration-only views. Addresses are native operands. No storage is defined
 * here; backing owners are not established by this function.
 */

typedef struct IDirectDraw IDirectDraw;
typedef struct IDirectDraw4 IDirectDraw4;
typedef struct IDirect3D3 IDirect3D3;

typedef int (__stdcall *DD_ENUMDEVICES_CB)(int, int, int, int, int, int);

typedef struct DD_VTABLE {
	int (__stdcall *QueryInterface)(void *self, const GUID *iid, void **out);
	unsigned long (__stdcall *AddRef)(void *self);
	unsigned long (__stdcall *Release)(void *self);
} DD_VTABLE;

typedef struct D3D_VTABLE {
	int (__stdcall *QueryInterface)(void *self, const GUID *iid, void **out);
	unsigned long (__stdcall *AddRef)(void *self);
	unsigned long (__stdcall *Release)(void *self);
	int (__stdcall *EnumDevices)(void *self, DD_ENUMDEVICES_CB cb, void *ctx);
} D3D_VTABLE;

struct IDirectDraw {
	DD_VTABLE *lpVtbl;
};

struct IDirectDraw4 {
	DD_VTABLE *lpVtbl;
};

struct IDirect3D3 {
	D3D_VTABLE *lpVtbl;
};

/* Callback record, stride 0x338. Name at +0x110, description at +0x10,
 * GUID at +0, flag bit 0x04 at +0x30d. The dialog reads this layout;
 * 0x41c460 writes it.
 */
typedef struct DD_DEVICE {
	GUID guid;
	char description[256];
	char name[256];
	char gap[253];
	char flag;
	char tail[42];
} DD_DEVICE;

/* Driver record, stride 0x214. Stored GUID pointer at +0, description at
 * +0x14, name at +0x114.
 */
typedef struct DD_DRIVER {
	GUID *guid;
	char gap[16];
	char description[256];
	char name[256];
} DD_DRIVER;

typedef char dd_device_size_ok[(sizeof(DD_DEVICE) == 0x338) ? 1 : -1];
typedef char dd_driver_size_ok[(sizeof(DD_DRIVER) == 0x214) ? 1 : -1];

/* ADDRESS: GOLD 0x006311fc */
extern HWND dd_DriverCombo;
/* ADDRESS: GOLD 0x006311f8 */
extern HWND dd_DeviceCombo;
/* ADDRESS: GOLD 0x005f3c48 */
extern int dd_LastDriver;
/* ADDRESS: GOLD 0x01464fa8 */
extern int dd_DeviceCount;
/* ADDRESS: GOLD 0x014635b0 */
extern int dd_DriverCount;
/* ADDRESS: GOLD 0x0146356c */
extern int dd_ComResult;
/* ADDRESS: GOLD 0x014635e0 */
extern DD_DEVICE dd_Devices[];
/* ADDRESS: GOLD 0x01465100 */
extern DD_DRIVER dd_Drivers[];
/* ADDRESS: GOLD 0x014483bc */
extern char *dd_DialogCaption;
/* ADDRESS: GOLD 0x014483c0 */
extern char *dd_StaticText68;
/* ADDRESS: GOLD 0x014483c4 */
extern char *dd_StaticText69;
/* ADDRESS: GOLD 0x005eeed0 */
extern const GUID IID_IDirectDraw4;
/* ADDRESS: GOLD 0x005eeec0 */
extern const GUID IID_IDirect3D3;

int __stdcall DirectDrawCreate(const GUID *guid, IDirectDraw **out, void *outer);
int __cdecl fcn_004112b0(const char *sub, int mode);
void __cdecl fcn_00411520(int key, int name, char *value);
void __cdecl fcn_00410430(int key);
char *__cdecl fcn_0041b1e0(GUID *guid, char *out);
int __stdcall fcn_0041c460(int a1, int a2, int a3, int a4, int a5, int a6);

/* ADDRESS: GOLD 0x0041c830 */
BOOL __stdcall fcn_0041c830(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int saved;
	char text[512];
	char guidtext[256];

	saved = 0;
	switch (msg) {
	case WM_COMMAND:
		switch (wParam & 0xffff) {
		case 0x66: {
			int sel;
			GUID *driver;
			IDirectDraw *ddraw1;
			IDirectDraw4 *ddraw4;

			sel = (int) SendMessageA(dd_DriverCombo, CB_GETCURSEL, 0, 0);
			if (sel == dd_LastDriver)
				return 1;
			dd_LastDriver = sel;
			driver = (GUID *) SendMessageA(dd_DriverCombo, CB_GETITEMDATA, (WPARAM) sel, 0);
			SendMessageA(dd_DeviceCombo, CB_RESETCONTENT, 0, 0);
			dd_DeviceCount = 0;
			if (DirectDrawCreate(driver, &ddraw1, 0) == 0) {
				IDirect3D3 *d3d3;

				d3d_LastResult = ddraw1->lpVtbl->QueryInterface(ddraw1, &IID_IDirectDraw4, (void **) &ddraw4);
				if (d3d_LastResult != 0) {
					fcn_00418e90("D:\\develop\\Units\\dd_vesa\\Dd_vesa.c", 939,
						"ddraw1->lpVtbl->QueryInterface(ddraw1, &IID_IDirectDraw4, &ddraw4)");
				}
				if (d3d_LastResult == 0) {
					d3d_LastResult = ddraw4->lpVtbl->QueryInterface(ddraw4, &IID_IDirect3D3, (void **) &d3d3);
					if (d3d_LastResult != 0) {
						fcn_00418e90("D:\\develop\\Units\\dd_vesa\\Dd_vesa.c", 944,
							"ddraw4->lpVtbl->QueryInterface(ddraw4, &IID_IDirect3D3, &d3d3)");
					}
					if (d3d_LastResult == 0) {
						d3d_LastResult = d3d3->lpVtbl->EnumDevices(d3d3, fcn_0041c460, (void *) DialogArgument1);
						if (d3d_LastResult != 0) {
							fcn_00418e90("D:\\develop\\Units\\dd_vesa\\Dd_vesa.c", 947,
								"d3d3->lpVtbl->EnumDevices(d3d3, d3d_EnumDeviceCallback, (void *)dd_BitPlanes)");
						}
						dd_ComResult = (int) d3d3->lpVtbl->Release(d3d3);
						d3d3 = 0;
					}
					dd_ComResult = (int) ddraw4->lpVtbl->Release(ddraw4);
					ddraw4 = 0;
				}
				dd_ComResult = (int) ddraw1->lpVtbl->Release(ddraw1);
				ddraw1 = 0;
			}
			{
			int i;

			for (i = 0; i < dd_DeviceCount; i++) {
				int added;

				strcpy(text, dd_Devices[i].description);
				strcat(text, " (");
				strcat(text, dd_Devices[i].name);
				strcat(text, ")");
				added = (int) SendMessageA(dd_DeviceCombo, CB_ADDSTRING, 0, (LPARAM) text);
				SendMessageA(dd_DeviceCombo, CB_SETITEMDATA, (WPARAM) added, (LPARAM) &dd_Devices[i].guid);
				if ((dd_Devices[i].flag & 4) == 0)
					saved = added;
			}
			}
			SendMessageA(dd_DeviceCombo, CB_SETCURSEL, (WPARAM) saved, 0);
			return 1;
		}
		case 1:
			PostMessageA(hwnd, WM_CLOSE, 0, 0);
			return 1;
		default:
			break;
		}
		break;
	case WM_INITDIALOG:
		dd_DriverCombo = GetDlgItem(hwnd, 0x66);
		dd_DeviceCombo = GetDlgItem(hwnd, 0x67);
		SetWindowTextA(hwnd, dd_DialogCaption);
		SetDlgItemTextA(hwnd, 0x68, dd_StaticText68);
		SetDlgItemTextA(hwnd, 0x69, dd_StaticText69);
		if (DialogArgument4 != 0) {
			int i;
			IDirect3D3 *d3d;

			SetWindowLongA(hwnd, GWL_STYLE, GetWindowLongA(hwnd, GWL_STYLE) & 0xff3fffff);
			EnableWindow(dd_DriverCombo, 0);
			while (ShowCursor(1) < 1) {
			}
			SendMessageA(dd_DeviceCombo, CB_RESETCONTENT, 0, 0);
			d3d = (IDirect3D3 *) DialogArgument5;
			dd_DeviceCount = 0;
			d3d_LastResult = d3d->lpVtbl->EnumDevices(d3d, fcn_0041c460, (void *) DialogArgument1);
			if (d3d_LastResult != 0) {
				fcn_00418e90("D:\\develop\\Units\\dd_vesa\\Dd_vesa.c", 889,
					"dd_D3D3->lpVtbl->EnumDevices(dd_D3D3, d3d_EnumDeviceCallback, (void *)dd_BitPlanes)");
			}
			for (i = 0; i < dd_DeviceCount; i++) {
				int added;

				strcpy(text, dd_Devices[i].description);
				strcat(text, " (");
				strcat(text, dd_Devices[i].name);
				strcat(text, ")");
				added = (int) SendMessageA(dd_DeviceCombo, CB_ADDSTRING, 0, (LPARAM) text);
				SendMessageA(dd_DeviceCombo, CB_SETITEMDATA, (WPARAM) added, (LPARAM) &dd_Devices[i].guid);
				if ((dd_Devices[i].flag & 4) == 0)
					saved = added;
			}
			SendMessageA(dd_DeviceCombo, CB_SETCURSEL, (WPARAM) saved, 0);
			BringWindowToTop(hwnd);
			return 1;
		} else {
			int i;

			for (i = 0; i < dd_DriverCount; i++) {
				int added;

				strcpy(text, dd_Drivers[i].description);
				strcat(text, " (");
				strcat(text, dd_Drivers[i].name);
				strcat(text, ")");
				added = (int) SendMessageA(dd_DriverCombo, CB_ADDSTRING, 0, (LPARAM) text);
				SendMessageA(dd_DriverCombo, CB_SETITEMDATA, (WPARAM) added, (LPARAM) dd_Drivers[i].guid);
			}
			SendMessageA(dd_DriverCombo, CB_SETCURSEL, (WPARAM) saved, 0);
			SendMessageA(hwnd, WM_COMMAND, 0x66, (LPARAM) dd_DriverCombo);
			BringWindowToTop(hwnd);
			return 1;
		}
	case WM_CLOSE: {
		int key;
		char *value;
		int data;

		key = fcn_004112b0("dd_vesa", 2);
		if (key != 0) {
			if (DialogArgument4 == 0) {
				data = (int) SendMessageA(dd_DriverCombo, CB_GETCURSEL, 0, 0);
				data = (int) SendMessageA(dd_DriverCombo, CB_GETITEMDATA, (WPARAM) data, 0);
				if (data != 0) {
					value = fcn_0041b1e0((GUID *) data, guidtext);
					if (value != 0)
						fcn_00411520(key, (int) "dd_Guid", value);
				} else {
					fcn_00411520(key, (int) "dd_Guid", "00000000-0000-0000-0000000000000000");
				}
			}
write_device:
			data = (int) SendMessageA(dd_DeviceCombo, CB_GETCURSEL, 0, 0);
			data = (int) SendMessageA(dd_DeviceCombo, CB_GETITEMDATA, (WPARAM) data, 0);
			if (data != 0) {
				value = fcn_0041b1e0((GUID *) data, guidtext);
				if (value != 0)
					fcn_00411520(key, (int) "d3d_Guid", value);
			} else {
				fcn_00411520(key, (int) "d3d_Guid", "00000000-0000-0000-0000000000000000");
			}
close_key:
			fcn_00410430(key);
		}
		while (ShowCursor(0) > 0) {
		}
		EndDialog(hwnd, 0);
		return 1;
	}
	default:
		break;
	}
	return 0;
}
