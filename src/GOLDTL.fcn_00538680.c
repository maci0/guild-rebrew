// FUNCTION: GOLD 0x00531bb0
// SIZE: 48
// FUNCTION: GOLDTL 0x538680
// SIZE: 48

__declspec(dllimport) void* __stdcall CreateMutexA(void*, int, const char*);
__declspec(dllimport) unsigned long __stdcall GetLastError(void);

int __cdecl fcn_00538680(void** a1)
{
	void* h;

	h = CreateMutexA(0, 1, "Die Gilde");
	if (h != 0) {
		*a1 = h;
		return GetLastError() == 0xb7;
	}
	return -1;
}
