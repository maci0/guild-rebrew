typedef void* HWND;
__declspec(dllimport) int __stdcall PeekMessageA(void*, HWND, unsigned int, unsigned int, unsigned int);
__declspec(dllimport) int __stdcall GetMessageA(void*, HWND, unsigned int, unsigned int);
__declspec(dllimport) int __stdcall TranslateMessage(void*);
__declspec(dllimport) long __stdcall DispatchMessageA(void*);

/* ADDRESS: GOLD 0x0052fbb0 */
int __cdecl fcn_0052fbb0(void)
{
    while (PeekMessageA((void*)0x75ec40, *(HWND*)0x6f2588, 0, 0, 0) != 0) {
        if (GetMessageA((void*)0x75ec40, *(HWND*)0x6f2588, 0, 0) == 0) {
            *(int*)0x6f25b4 = 1;
        } else {
            TranslateMessage((void*)0x75ec40);
            DispatchMessageA((void*)0x75ec40);
        }
    }
    return 1;
}
