typedef int BOOL; typedef void *HANDLE; typedef unsigned long DWORD; typedef void *LPVOID;
#define WINAPI __stdcall
int __proc_attached = 1;
BOOL (WINAPI *_pRawDllMain)(HANDLE, DWORD, LPVOID) = 0;
BOOL WINAPI _CRT_INIT(HANDLE h, DWORD r, LPVOID p) { return 1; }
BOOL WINAPI DllMain(HANDLE h, DWORD r, LPVOID p) { return 1; }
