// FUNCTION: GOLDTL 0x004112b0
// SIZE: 144

#include <stdio.h>
#include <windows.h>

int __cdecl fcn_004112b0(const char* sub, int mode)
{
	HKEY key;
	DWORD disp;
	char path[0x100];
	LONG r;

	sprintf(path, "%s%s", "Software\\Ahead Entertainment\\", sub);
	switch (mode) {
	case 1:
		r = RegOpenKeyExA(HKEY_CURRENT_USER, path, 0, KEY_READ, &key);
		break;
	case 2:
		r = RegCreateKeyExA(HKEY_CURRENT_USER, path, 0, 0, 0, KEY_WRITE, 0, &key, &disp);
		break;
	default:
		r = -1;
		break;
	}
	if (r == 0) {
		return (int) key;
	}
	return -1;
}
