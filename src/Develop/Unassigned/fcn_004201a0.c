extern char g_14cc5a0[];
extern int g_6b71a4;

__declspec(dllimport) void __stdcall EnterCriticalSection(void* lpCriticalSection);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void* lpCriticalSection);

int __cdecl fcn_0042af10(int h);

/* Guarded MSX channel lookup under the global lock: returns 1 when the handle
 * is idle (state 4), and also 1 when the subsystem is not initialised.
 * Native function spans 0x004201a0..0x004201f4 (85 bytes); inventory rows
 * 0x4201a0 (15) and 0x4201af (70) are one function split at the jne target. */
/* ADDRESS: GOLDTL 0x004201a0 */
int __cdecl fcn_004201a0(void* p)
{
	int v;

	if (g_6b71a4 == 0) {
		return 1;
	}
	EnterCriticalSection(g_14cc5a0);
	v = *(int*) ((char*) p + 0x100);
	if (v != 0) {
		if (fcn_0042af10(v) == 4) {
			LeaveCriticalSection(g_14cc5a0);
			return 1;
		}
	}
	LeaveCriticalSection(g_14cc5a0);
	return 0;
}
