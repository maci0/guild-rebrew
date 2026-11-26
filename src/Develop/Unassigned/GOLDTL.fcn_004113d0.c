


#include <string.h>
#include <windows.h>

int __cdecl io_ReadRegistryString(HKEY key, const char* name, char* out)
{
	DWORD size;
	char buf[0x80];

	size = 0x80;
	if (RegQueryValueExA(key, name, 0, 0, (LPBYTE) buf, &size) == 0) {
		strcpy(out, buf);
		return 1;
	}
	return 0;
}
