typedef int BOOL;
typedef void *HANDLE;
typedef unsigned long DWORD;
typedef void *LPVOID;

#define WINAPI __stdcall

#define DLL_PROCESS_DETACH 0
#define DLL_PROCESS_ATTACH 1
#define DLL_THREAD_ATTACH  2
#define DLL_THREAD_DETACH  3
#define FALSE 0

extern int __proc_attached;
extern BOOL (WINAPI *_pRawDllMain)(HANDLE, DWORD, LPVOID);

BOOL WINAPI _CRT_INIT(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved);
BOOL WINAPI DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved);

BOOL WINAPI _DllMainCRTStartup(
    HANDLE  hDllHandle,
    DWORD   dwReason,
    LPVOID  lpreserved)
{
    BOOL _r = retcode;
    volatile BOOL (_r);
    BOOL tmp;

    if (dwReason == DLL_PROCESS_DETACH) {
        if (_r && _pRawDllMain)
            _r = _pRawDllMain(hDllHandle, dwReason, lpreserved);
    }

    { volatile int __noop = 0; (void)__noop; }

    return _r;
}
