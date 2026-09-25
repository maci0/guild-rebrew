// FUNCTION: GOLDTL 0x00539090
// SIZE: 520

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

extern char g_7e25a0[];
extern HWND g_774940;
extern int g_6acf80;
extern int g_6acf84;

LRESULT CALLBACK fcn_00538250(HWND, UINT, WPARAM, LPARAM);
void __cdecl fcn_00538500(char*);

int __cdecl fcn_00539090(HINSTANCE inst, int unused, int windowed)
{
	RECT work;
	WNDCLASSA wc;
	RECT client;
	char title[0x80];
	DWORD style;
	DWORD ex_style;
	int w;
	int h;
	int nw;
	int nh;

	memset(&wc, 0, sizeof(wc));
	wc.style = 0;
	wc.lpfnWndProc = fcn_00538250;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = inst;
	wc.hIcon = LoadIconA(inst, MAKEINTRESOURCE(0x65));
	wc.hCursor = LoadCursorA(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "Die Gilde";
	if (RegisterClassA(&wc) == 0) {
		return 0;
	}
	fcn_00538500(g_7e25a0);
	sprintf(title, " %s", g_7e25a0);
	SystemParametersInfoA(SPI_GETWORKAREA, 0, &work, 0);
	w = work.right - work.left;
	h = work.bottom - work.top;
	if (windowed == 0) {
		style = WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN;
		ex_style = WS_EX_TOPMOST;
		work.top = 0;
		work.left = 0;
		w = work.right;
		h = work.bottom;
	} else {
		style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		ex_style = 0;
	}
	g_774940 = CreateWindowExA(ex_style, "Die Gilde", title, style, work.left, work.top, w, h, 0, 0, inst, 0);
	if (g_774940 == 0) {
		return 0;
	}
	ShowWindow(g_774940, SW_SHOW);
	UpdateWindow(g_774940);
	SetFocus(g_774940);
	if (windowed != 0) {
		GetClientRect(g_774940, &client);
		nw = g_6acf80 - client.right + w;
		nh = g_6acf84 - client.bottom + h;
		MoveWindow(g_774940, abs(w - nw) / 2, abs(h - nh) / 2, nw, nh, TRUE);
		SetWindowPos(g_774940, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	} else {
		SetWindowPos(g_774940, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 0);
	}
	return 1;
}
