

__declspec(dllimport) int __stdcall SystemParametersInfoA(unsigned int, unsigned int, void*, unsigned int);

int __cdecl main_IsScreensaverActive(void)
{
	int v;

	v = 0;
	SystemParametersInfoA(0x10, 0, &v, 0);
	return v;
}
