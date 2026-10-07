extern char g_7e2a80[];
typedef void* HWND;

extern HWND g_774940;
extern int g_77496c;

// FUNCTION: GOLDTL 0x5356e0

__declspec(dllimport) int __stdcall PeekMessageA(void*, HWND, unsigned int, unsigned int, unsigned int);
__declspec(dllimport) int __stdcall GetMessageA(void*, HWND, unsigned int, unsigned int);
__declspec(dllimport) int __stdcall TranslateMessage(void*);
__declspec(dllimport) int __stdcall DispatchMessageA(void*);

int __cdecl fcn_005356e0(void)
{
	while (PeekMessageA(g_7e2a80, g_774940, 0, 0, 0) != 0) {
		if (GetMessageA(g_7e2a80, g_774940, 0, 0) == 0) {
			g_77496c = 1;
		} else {
			TranslateMessage(g_7e2a80);
			DispatchMessageA(g_7e2a80);
		}
	}
	return 1;
}
