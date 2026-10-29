/* The game's main window procedure (registered as lpfnWndProc by
 * fcn_00539090).  stdcall, four args; the switch table at 0x538454/0x538464
 * is compiler-generated from the case labels below. */

#include <windows.h>

extern int g_77493c;
extern char g_774944;
extern int g_77250c;
extern int g_6b7fc0;

int __cdecl fcn_0041baa0(void);
void __cdecl fcn_00418640(void);
void __cdecl fcn_00418680(void);
void __cdecl fcn_004117c0(int);
void __cdecl fcn_004117f0(int);
void __cdecl fcn_0042a3d0(void);
void __cdecl fcn_0042a410(int, int, int);
void __cdecl fcn_0042a460(int, int);
void __cdecl fcn_0043b360(void);
void __cdecl fcn_00473610(void);
void __cdecl fcn_00473640(void);
void __cdecl fcn_00476970(int);
void __cdecl fcn_004774a0(void);
void __cdecl fcn_004774b0(void);
void __cdecl fcn_0047ce70(void);
void __cdecl fcn_0047ce80(void);

#define WM_PRIVATE_7E7 0x7e7
#define WM_MOUSEHWHEEL_VALUE 0x20a
/* This SDK's winuser.h still has the Win16 value for WM_GETMINMAXINFO (0x24);
 * the reference binary switches on 0x14. */
#define WM_GETMINMAXINFO_VALUE 0x14
#define D3DERR_DEVICELOST_VALUE 0x88760869

/* ADDRESS: GOLDTL 0x00538250 */
LRESULT CALLBACK fcn_00538250(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int hr;
	int active;

	switch (uMsg) {
	case WM_DESTROY:
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		ValidateRect(hWnd, 0);
		return 0;
	case WM_GETMINMAXINFO_VALUE:
		ValidateRect(hWnd, 0);
		if (g_77250c)
			fcn_00476970(g_77250c);
		return 1;
	case WM_ACTIVATEAPP:
		/* The two guard exits share one `return 0` epilogue in the target
		 * (0x538414) and the flag-clear exits share another (0x538386);
		 * spelled with gotos so the blocks are shared directly instead of
		 * tail-merged or duplicated. */
		if (wParam != 0) {
			if (!g_77493c)
				goto exit0;
			if (!g_774944)
				goto cleared;
			hr = fcn_0041baa0();
			if (hr == E_FAIL)
				goto resume;
			hr = fcn_0041baa0();
			if (hr == 0)
				goto resume;
			hr = fcn_0041baa0();
			if (hr == (int) D3DERR_DEVICELOST_VALUE)
				goto teardown;
			do {
				Sleep(250);
				hr = fcn_0041baa0();
			} while (hr != (int) D3DERR_DEVICELOST_VALUE);
		teardown:
			fcn_00418640();
			fcn_00473610();
			fcn_004774a0();
			fcn_0047ce70();
			fcn_0043b360();
			fcn_0047ce80();
			fcn_004774b0();
			fcn_00473640();
			fcn_00418680();
		resume:
			g_6b7fc0 = 0;
			fcn_0042a460((int) hWnd, WM_PRIVATE_7E7);
			fcn_004117c0(1);
			fcn_004117f0(1);
		cleared:
			g_77493c = 0;
			return 0;
		}
		if (g_77493c == 1)
			goto exit0;
		active = g_774944;
		g_77493c = 1;
		if (active) {
			fcn_004117c0(0);
			fcn_004117f0(0);
			fcn_0042a3d0();
			g_6b7fc0 = 1;
		}
		/* HWND_BOTTOM (1), not HWND_TOP: the reference pushes the live
		 * `mov esi,1` value from the flag stores. */
		SetWindowPos(hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		return 0;
	case WM_MOUSEHWHEEL_VALUE:
		ValidateRect(hWnd, 0);
		return 1;
	case WM_POWERBROADCAST:
		if (wParam == 0)
			return 0x424D5144;
	default:
		return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	case WM_PRIVATE_7E7:
		fcn_0042a410((int) wParam, (int) hWnd, WM_PRIVATE_7E7);
		goto exit0;
	}
exit0:
	return 0;
}
