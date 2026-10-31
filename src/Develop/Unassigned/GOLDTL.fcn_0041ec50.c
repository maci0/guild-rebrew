#include <stdio.h>
#include <string.h>

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
} Rect41ec50;

__declspec(dllimport) int __stdcall IsWindow(void*);
__declspec(dllimport) int __stdcall GetClientRect(void*, Rect41ec50*);
__declspec(dllimport) int __stdcall MultiByteToWideChar(unsigned int, unsigned long, const char*, int, unsigned short*, int);
extern long __stdcall DirectDrawCreateEx(void*, void**, void*, void*);
extern long __stdcall CoCreateInstance(void*, void*, unsigned long, void*, void**);

char* __cdecl AllocVideoListNode(void);
void __cdecl ReleaseVideoInterfaces(char*);
void __cdecl FreeVideoListNode(char*);

/* Starts playback of a video file: opens the DirectDraw surface and the
   DirectShow filter graph, then places the video window. Returns the new
   client id, or 0 on failure. */
/* ADDRESS: GOLDTL 0x0041ec50 */
int __cdecl fcn_0041ec50(char* name, void* hwnd, int x, int y, int w, int h, int flags, int mode_w, int mode_h, int mode_bpp)
{
	FILE* fp;
	char* v;
	Com* dd;
	Com* graph;
	Com* filter;
	Com* surface;
	Com* window;
	Rect41ec50 rc;
	Rect41ec50 client;
	int desc[0x1f];
	int scaled;
	int num;
	int wflags;
	int id;
	long res;
	char msg[0x100];
	unsigned short wname[0x104];

	fp = fopen(name, (char*) 0x6750e8);
	if (fp == 0) {
		return 0;
	}
	fclose(fp);
	if (!IsWindow(hwnd)) {
		sprintf(msg, (char*) 0x6780b8, name, hwnd);
		return 0;
	}
	v = AllocVideoListNode();
	if (v == 0) {
		return 0;
	}
	wflags = 0;
	desc[0] = 0;
	memset(&desc[1], 0, 0x78);
	window = 0;
	strcpy(v + 0x10, name);
	*(void**) (v + 0x114) = hwnd;
	*(int*) (v + 0xc) = flags;
	res = DirectDrawCreateEx(0, (void**) (v + 0x13c), (void*) 0x66dad0, 0);
	if (res < 0) {
		goto fail;
	}
	dd = *(Com**) (v + 0x13c);
	if ((*(long (__stdcall**) (Com*, void*, void**)) dd->vt)(dd, (void*) 0x66db00, (void**) (v + 0x138)) < 0) {
		goto fail;
	}
	if (flags & 0x10) {
		wflags = 8;
	} else if (flags & 0x20) {
		wflags = 0x11;
	}
	if (flags & 0x40) {
		wflags |= 0x400;
	}
	dd = *(Com**) (v + 0x13c);
	if ((*(long (__stdcall**) (Com*, void*, int)) (dd->vt + 0x50 / 4))(dd, hwnd, wflags) < 0) {
		goto fail;
	}
	if ((wflags & 0x10) && mode_w != 0 && mode_h != 0 && mode_bpp != 0) {
		if ((*(long (__stdcall**) (Com*, int, int, int, int, int)) (dd->vt + 0x54 / 4))(dd, mode_w, mode_h, mode_bpp, 0, 0) < 0) {
			goto fail;
		}
	}
	dd = *(Com**) (v + 0x13c);
	desc[0] = 0x7c;
	desc[1] = 1;
	*(int*) (&desc[0x68 / 4]) = 0x184200;
	if ((*(long (__stdcall**) (Com*, int*, void**, void*)) (dd->vt + 0x18 / 4))(dd, desc, (void**) (v + 0x144), 0) < 0) {
		goto fail;
	}
	surface = *(Com**) (v + 0x144);
	if ((*(long (__stdcall**) (Com*, void*, void**)) surface->vt)(surface, (void*) 0x66dac0, (void**) (v + 0x140)) < 0) {
		goto fail;
	}
	res = CoCreateInstance((void*) 0x670470, 0, 1, (void*) 0x66ed70, (void**) (v + 0x134));
	if (res < 0) {
		goto fail;
	}
	graph = *(Com**) (v + 0x134);
	if ((*(long (__stdcall**) (Com*, void*)) (graph->vt + 0xc / 4))(graph, *(void**) (v + 0x138)) < 0) {
		goto fail;
	}
	res = (*(long (__stdcall**) (Com*, void*)) (graph->vt + 0x14 / 4))(graph, *(void**) (v + 0x140));
	if (res < 0) {
		if (res == 0x80070057L) {
			sprintf(msg, (char*) 0x678124);
		} else {
			sprintf(msg, (char*) 0x6780f0, res);
		}
		goto fail;
	}
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
			num = (rc.right - rc.left) * client.top;
			scaled = (int) ((float) num / (float) client.left);
			rc.top = (rc.bottom - rc.top) / 2 - scaled / 2;
			rc.bottom = scaled + rc.top;
		}
	} else if (x != 0 && y != 0) {
		if (flags & 4) {
			filter = *(Com**) (v + 0x128);
			if ((*(long (__stdcall**) (Com*, int*, int*)) (filter->vt + 0x88 / 4))(filter, &client.left, &client.top) < 0) {
				goto fail;
			}
			num = w * client.top;
			scaled = (int) ((float) num / (float) client.left);
			if (flags & 1) {
				GetClientRect(hwnd, &client);
				rc.left = (client.right - client.left) / 2 - w / 2;
				rc.top = (client.bottom - client.top) / 2 - scaled / 2;
				rc.right = w + rc.left;
				rc.bottom = scaled + rc.top;
			} else {
				rc.left = x;
				rc.top = y;
				rc.right = w + rc.left;
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
		window = *(Com**) (*(char**) (v + 0x3c));
		if (window != 0) {
			(*(long (__stdcall**) (Com*, void*, int, int)) (window->vt + 0x34 / 4))(window, hwnd, 0x9021, id);
		}
	}
	return id;

fail:
	ReleaseVideoInterfaces(v);
	FreeVideoListNode(v);
	return 0;
}
