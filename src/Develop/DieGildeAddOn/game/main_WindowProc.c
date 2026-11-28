/* The game's main window procedure (registered as lpfnWndProc by
 * fcn_00539090).  stdcall, four args; the switch table at 0x538454/0x538464
 * is compiler-generated from the case labels below. */

#include <windows.h>

extern int g_77493c;
extern char g_774944;
extern int d2_ScreenSurface;
extern volatile int tb_TimerPaused;

int __cdecl d3_TestCooperativeLevel(void);
void __cdecl d3_ReleaseRenderVertexBuffers(void);
void __cdecl d3_CreateRenderVertexBuffers(void);
void __cdecl io_AcquireKeyboard(int);
void __cdecl io_AcquireMouse(int);
void __cdecl msx_ReleaseAllDrivers(void);
void __cdecl msx_ReacquireWaveDriver(int, int, int);
void __cdecl msx_ReacquireAllWaveDrivers(int, int);
void __cdecl d3_ResetDeviceObjects(void);
void __cdecl d3_ReleaseBackBuffer(void);
void __cdecl d3_AcquireBackBuffer(void);
void __cdecl d2_ClearSurface(int);
void __cdecl d2_OnLostRenderToSurface(void);
void __cdecl d2_ResetRenderToSurface(void);
void __cdecl d2_ReleaseQuadVertexBufferThunk(void);
void __cdecl d2_RebuildQuadVertexBuffer(void);

#define WM_PRIVATE_7E7 0x7e7
#define WM_MOUSEHWHEEL_VALUE 0x20a
/* This SDK's winuser.h still has the Win16 value for WM_GETMINMAXINFO (0x24);
 * the reference binary switches on 0x14. */
#define WM_GETMINMAXINFO_VALUE 0x14
#define D3DERR_DEVICELOST_VALUE 0x88760869

/* ADDRESS: GOLDTL 0x00538250 */
/* ADDRESS: GOLDDE 0x0051fb20 */
LRESULT CALLBACK main_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		if (d2_ScreenSurface)
			d2_ClearSurface(d2_ScreenSurface);
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
			hr = d3_TestCooperativeLevel();
			if (hr == E_FAIL)
				goto resume;
			hr = d3_TestCooperativeLevel();
			if (hr == 0)
				goto resume;
			hr = d3_TestCooperativeLevel();
			if (hr == (int) D3DERR_DEVICELOST_VALUE)
				goto teardown;
			do {
				Sleep(250);
				hr = d3_TestCooperativeLevel();
			} while (hr != (int) D3DERR_DEVICELOST_VALUE);
		teardown:
			d3_ReleaseRenderVertexBuffers();
			d3_ReleaseBackBuffer();
			d2_OnLostRenderToSurface();
			d2_ReleaseQuadVertexBufferThunk();
			d3_ResetDeviceObjects();
			d2_RebuildQuadVertexBuffer();
			d2_ResetRenderToSurface();
			d3_AcquireBackBuffer();
			d3_CreateRenderVertexBuffers();
		resume:
			tb_TimerPaused = 0;
			msx_ReacquireAllWaveDrivers((int) hWnd, WM_PRIVATE_7E7);
			io_AcquireKeyboard(1);
			io_AcquireMouse(1);
		cleared:
			g_77493c = 0;
			return 0;
		}
		if (g_77493c == 1)
			goto exit0;
		active = g_774944;
		g_77493c = 1;
		if (active) {
			io_AcquireKeyboard(0);
			io_AcquireMouse(0);
			msx_ReleaseAllDrivers();
			tb_TimerPaused = 1;
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
		msx_ReacquireWaveDriver((int) wParam, (int) hWnd, WM_PRIVATE_7E7);
		goto exit0;
	}
exit0:
	return 0;
}
