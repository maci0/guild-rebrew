


__declspec(dllimport) void* __stdcall CreateMutexA(void*, int, const char*);
__declspec(dllimport) unsigned long __stdcall GetLastError(void);

int __cdecl fcn_00538680(void** mutexOut)
{
	void* mutex;

	mutex = CreateMutexA(0, 1, "Die Gilde");
	if (mutex != 0) {
		*mutexOut = mutex;
		return GetLastError() == 0xb7;
	}
	return -1;
}
