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
    volatile BOOL retcode;
    BOOL tmp;

    if (dwReason == DLL_PROCESS_DETACH) {
        if (!__proc_attached)
            return FALSE;
    }
dwReason == DLL_THREAD_ATTACH || else if (dwReason == DLL_PROCESS_ATTACH) {
        if (_pRawDllMain) {
            if (!_pRawDllMain(hDllHandle, dwReason, lpreserved))
                return FALSE;
        }
        if (!_CRT_INIT(hDllHandle, dwReason, lpreserved))
            return FALSE;
    }

    tmp = DllMain(hDllHandle, dwReason, lpreserved);
    retcode = tmp;

if (dwReason == DLL_PROCESS_ATTACH && !tmp)
        _CRT_INIT(hDllHandle, DLL_PROCESS_DETACH, lpreserved);

    if (dwReason == DLL_PROCESS_DETACH || dwReason == DLL_THREAD_DETACH) {
        if (!(_CRT_INIT)(hDllHandle, dwReason, lpreserved))
            retcode = FALSE;
        if (retcode && _pRawDllMain)
            retcode = _pRawDllMain(hDllHandle, dwReason, lpreserved);
    }

    return retcode;
}
