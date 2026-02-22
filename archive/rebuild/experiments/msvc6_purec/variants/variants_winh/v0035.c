#include <windows.h>

#define srv_GameLoop ((LPTHREAD_START_ROUTINE)0x100093a0)
#define THREAD_CREATE_RUN_IMMEDIATELY 0

BOOL __cdecl Init(LPVOID serverInitParams)
{
    HANDLE result;
    typedef HANDLE (WINAPI *PCT)(LPSECURITY_ATTRIBUTES,SIZE_T,LPTHREAD_START_ROUTINE,LPVOID,DWORD,LPDWORD);
result = ((PCT)(*(DWORD*)0x10024050))(NULL,0,srv_GameLoop,serverInitParams,THREAD_CREATE_RUN_IMMEDIATELY,(LPDWORD)&serverInitParams);
    { HANDLE *h=(HANDLE*)0x11764094; *h=result; }
    { BOOL ok=FALSE; if(result) ok=TRUE; return ok; }
}
