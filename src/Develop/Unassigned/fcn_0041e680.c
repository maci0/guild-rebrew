#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct Com Com;

/* SIZE 0x4 */
struct Com {
	int* vt;
};

/* SIZE 0x10 */
typedef struct {
	int left;
	int top;
	int right;
	int bottom;
} Rect41e680;

__declspec(dllimport) int __stdcall IsWindow(void*);
__declspec(dllimport) int __stdcall GetClientRect(void*, Rect41e680*);
__declspec(dllimport) int __stdcall MultiByteToWideChar(unsigned int, unsigned long, const char*, int, unsigned short*, int);
__declspec(dllimport) HCURSOR __stdcall LoadCursorA(void*, const char*);
__declspec(dllimport) short __stdcall RegisterClassExA(const void*);
__declspec(dllimport) HWND __stdcall CreateWindowExA(unsigned long, const char*, const char*, unsigned long, int, int, int, int, void*, void*, void*, void*);
__declspec(dllimport) int __stdcall GetSystemMetrics(int);
__declspec(dllimport) int __stdcall ShowCursor(int);
extern long __stdcall CoCreateInstance(void*, void*, unsigned long, void*, void**);

extern short g_14cc5b8;
extern int g_14cc5bc;
extern char g_6750e8[];
extern char g_6b5c60[];

LRESULT CALLBACK fcn_0041e530(HWND, UINT, WPARAM, LPARAM);
char* __cdecl AllocVideoListNode(void);
void __cdecl ReleaseVideoInterfaces(char*);
void __cdecl FreeVideoListNode(char*);

/* Creates the MOVIEWNDCLASS movie window for a file, opens the DirectShow
   filter graph on it and returns the movie client id, or 0 on failure. */
/* ADDRESS: GOLDTL 0x0041e680 */
int __cdecl fcn_0041e680(char* name, void* hwnd, void* inst, int x, int y, int w, int h, int flags)
{
	WNDCLASSEXA wc;
	FILE* fp;
	char* v;
	Com* filter;
	Com* graph;
	Com* window;
	Com* event;
	Rect41e680 rc;
	Rect41e680 client;
	int scaled;
	int id;
	long res;
	unsigned short wname[0x104];
	char msg[0x108];

	fp = fopen(name, (char*) g_6750e8);
	if (fp == 0) {
		return 0;
	}
	fclose(fp);
	if (hwnd == 0) {
		if (g_14cc5b8 == 0) {
			memset(&wc, 0, 0x2c);
			wc.cbSize = 0x30;
			wc.style = 0;
			wc.lpfnWndProc = fcn_0041e530;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = (HINSTANCE) inst;
			wc.hIcon = 0;
			wc.hCursor = LoadCursorA(0, (const char*) 0x7f00);
			wc.hbrBackground = 0;
			wc.lpszMenuName = 0;
			wc.lpszClassName = "MOVIEWNDCLASS";
			wc.hIconSm = 0;
			g_14cc5b8 = RegisterClassExA(&wc);
		}
		if ((char) flags < 0) {
			hwnd = CreateWindowExA(8, "MOVIEWNDCLASS", (char*) g_6b5c60, 0x86000000,
			    0, 0, GetSystemMetrics(0), GetSystemMetrics(1), 0, 0, inst, 0);
			ShowCursor(0);
		} else {
			hwnd = CreateWindowExA(8, "MOVIEWNDCLASS", (char*) g_6b5c60, 0xcf0000,
			    0x80000000, 0x80000000, 0x80000000, 0x80000000, 0, 0, inst, 0);
		}
		flags |= 0x100;
	}
	if (!IsWindow(hwnd)) {
		sprintf(msg, (char*) 0x6780b8, name, hwnd);
		return 0;
	}
	v = AllocVideoListNode();
	if (v == 0) {
		return 0;
	}
	strcpy(v + 0x10, name);
	*(void**) (v + 0x114) = hwnd;
	*(int*) (v + 0xc) = flags;
	res = CoCreateInstance((void*) 0x6707a0, 0, 1, (void*) 0x66f230, (void**) (v + 0x11c));
	if (res < 0) {
		goto fail;
	}
	filter = *(Com**) (v + 0x11c);
	if ((*(long (__stdcall**) (Com*, void*, void**)) filter->vt)(filter, (void*) 0x66f900, (void**) (v + 0x128)) < 0) {
		goto fail;
	}
	filter = *(Com**) (v + 0x11c);
	if ((*(long (__stdcall**) (Com*, void*, void**)) filter->vt)(filter, (void*) 0x66f920, (void**) (v + 0x12c)) < 0) {
		goto fail;
	}
	filter = *(Com**) (v + 0x11c);
	if ((*(long (__stdcall**) (Com*, void*, void**)) filter->vt)(filter, (void*) 0x66f960, (void**) (v + 0x120)) < 0) {
		goto fail;
	}
	filter = *(Com**) (v + 0x11c);
	if ((*(long (__stdcall**) (Com*, void*, void**)) filter->vt)(filter, (void*) 0x66f940, (void**) (v + 0x124)) < 0) {
		goto fail;
	}
	MultiByteToWideChar(0, 2, name, (int) strlen(name) + 1, wname, 0x104);
	filter = *(Com**) (v + 0x11c);
	if ((*(long (__stdcall**) (Com*, void*, void*)) (filter->vt + 0x34 / 4))(filter, wname, 0) < 0) {
		goto fail;
	}
	graph = *(Com**) (v + 0x11c);
	if ((*(long (__stdcall**) (Com*, void*, void**)) graph->vt)(graph, (void*) 0x66f910, (void**) (v + 0x130)) < 0) {
		goto fail;
	}
	window = *(Com**) (v + 0x130);
	if ((*(long (__stdcall**) (Com*, void*)) (window->vt + 0x74 / 4))(window, *(void**) (v + 0x114)) < 0) {
		goto fail;
	}
	window = *(Com**) (v + 0x130);
	if ((*(long (__stdcall**) (Com*, int)) (window->vt + 0x24 / 4))(window, 0x40000000) < 0) {
		goto fail;
	}
	if (flags & 2) {
		GetClientRect(hwnd, &rc);
		if (flags & 4) {
			filter = *(Com**) (v + 0x128);
			if ((*(long (__stdcall**) (Com*, int*, int*)) (filter->vt + 0x88 / 4))(filter, &client.left, &client.top) < 0) {
				goto fail;
			}
			scaled = (int) ((float) ((rc.right - rc.left) * client.top) / (float) client.left);
			rc.top = (rc.bottom - rc.top) / 2 - scaled / 2;
			rc.bottom = scaled + rc.top;
		}
	} else if (w != 0 && h != 0) {
		if (flags & 4) {
			filter = *(Com**) (v + 0x128);
			if ((*(long (__stdcall**) (Com*, int*, int*)) (filter->vt + 0x88 / 4))(filter, &client.left, &client.top) < 0) {
				goto fail;
			}
			scaled = (int) ((float) (w * client.top) / (float) client.left);
			if (flags & 1) {
				GetClientRect(hwnd, &client);
				rc.left = (client.right - client.left) / 2 - w / 2;
				rc.top = (client.bottom - client.top) / 2 - scaled / 2;
				rc.right = w + rc.left;
				rc.bottom = scaled + rc.top;
			} else {
				rc.left = x;
				rc.top = y;
				rc.right = x + w;
				rc.bottom = y + scaled;
			}
		} else {
			rc.left = x;
			rc.top = y;
			rc.right = x + w;
			rc.bottom = y + h;
			if (flags & 1) {
				GetClientRect(hwnd, &client);
				rc.left = (client.right - client.left) / 2 - (rc.right - rc.left) / 2;
				rc.top = (client.bottom - client.top) / 2 - (rc.bottom - rc.top) / 2;
			}
		}
	} else {
		GetClientRect(hwnd, &rc);
		filter = *(Com**) (v + 0x128);
		if ((*(long (__stdcall**) (Com*, int*, int*)) (filter->vt + 0x88 / 4))(filter, &client.left, &client.top) < 0) {
			goto fail;
		}
		rc.left = (rc.right - rc.left) / 2 - client.left / 2;
		rc.top = (rc.bottom - rc.top) / 2 - client.top / 2;
		rc.right = rc.left + client.left;
		rc.bottom = rc.top + client.top;
	}
	window = *(Com**) (v + 0x130);
	if ((*(long (__stdcall**) (Com*, int, int, int, int)) (window->vt + 0x9c / 4))(window, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top) < 0) {
		goto fail;
	}
	*(int*) (v + 8) = *(int*) 0x14cc5bc;
	id = *(int*) 0x14cc5bc;
	*(int*) 0x14cc5bc = id + 1;
	if (flags & 8) {
		event = *(Com**) (v + 0x124);
		(*(long (__stdcall**) (Com*, void*, int, int)) (event->vt + 0x34 / 4))(event, hwnd, 0x9021, id);
	}
	window = *(Com**) (v + 0x130);
	(*(long (__stdcall**) (Com*, int)) (window->vt + 0x94 / 4))(window, -1);
	window = *(Com**) (v + 0x130);
	(*(long (__stdcall**) (Com*, int)) (window->vt + 0x44 / 4))(window, 0);
	return id;

fail:
	ReleaseVideoInterfaces(v);
	FreeVideoListNode(v);
	return 0;
}
