/* Fragment evidence:
   Fragment: continuation of the function that starts at 0x4201a0. Entry
   0x4201af is the jne target of 0x4201a7; the preceding block is the
   early-return arm of the same function, not a separate function.
*/
extern char g_14cc5a0[];

__declspec(dllimport) void __stdcall EnterCriticalSection(void* lpCriticalSection);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void* lpCriticalSection);

int __cdecl fcn_0042af10(int h);

/* ADDRESS: GOLDTL 0x004201af */
int __cdecl fcn_004201af(void* p)
{
	EnterCriticalSection(g_14cc5a0);
	if (*(int*) ((char*) p + 0x100) != 0) {
		if (fcn_0042af10(*(int*) ((char*) p + 0x100)) == 4) {
			LeaveCriticalSection(g_14cc5a0);
			return 1;
		}
	}
	LeaveCriticalSection(g_14cc5a0);
	return 0;
}
