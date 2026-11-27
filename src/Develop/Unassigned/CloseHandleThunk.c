#include <windows.h>

/* ADDRESS: GOLDTL 0x005386b0 */
BOOL __cdecl CloseHandleThunk(HANDLE h)
{
	return CloseHandle(h);
}
