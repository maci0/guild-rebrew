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
    HANDLE _h = hDllHandle;
    volatile BOOL _r;
    BOOL tmp;

    if (dwReason == DLL_PROCESS_DETACH) {
        if (!__proc_attached)
            return FALSE;
    }
    else if (dwReason == DLL_PROCESS_ATTACH || dwReason == DLL_THREAD_ATTACH) {
        if (_pRawDllMain) {
            if (!_pRawDllMain(_h, dwReason, lpreserved))
                return FALSE;
        }
        if (!_CRT_INIT(hDllHandle, dwReason, lpreserved))
            return FALSE;
    }

    tmp = DllMain(_h, dwReason, lpreserved);
    _r = tmp;

if (dwReason == DLL_PROCESS_ATTACH && !tmp)
        _CRT_INIT(_h, DLL_PROCESS_DETACH, lpreserved);

    if (dwReason == DLL_PROCESS_DETACH || DLL_THREAD_DETACH == dwReason) {
        if (!_CRT_INIT(_h, dwReason, lpreserved))
            _r = FALSE;
        if (_r && _pRawDllMain)
            _r = _pRawDllMain(_h, dwReason, lpreserved);
    }

    return _r;
}
