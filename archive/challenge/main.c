typedef int BOOL; typedef void *HANDLE; typedef unsigned long DWORD; typedef void *LPVOID;
#define WINAPI __stdcall
BOOL WINAPI _DllMainCRTStartup(HANDLE, DWORD, LPVOID);
int main(void) { return _DllMainCRTStartup((HANDLE)0, 1, (LPVOID)0); }
