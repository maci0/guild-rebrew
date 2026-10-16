void __cdecl m_FreeTracked(int);
__declspec(dllimport) void __stdcall OutputDebugStringA(const char *);

/* ADDRESS: GOLD 0x0045ef50 */
void __cdecl fcn_0045ef50(int s)
{
	if (s == 0)
		return;
	if (s == *(int *)0x633df8)
		OutputDebugStringA((const char *)0x5fd098);
	else
		OutputDebugStringA((const char *)0x5fd088);
	if (*(int *)(s + 0x24) != 0) {
		m_FreeTracked(*(int *)(s + 0x24));
		*(int *)(s + 0x24) = 0;
	}
	if (*(int *)(s + 0x28) != 0) {
		m_FreeTracked(*(int *)(s + 0x28));
		*(int *)(s + 0x28) = 0;
	}
	m_FreeTracked(s);
}
