


#include <windows.h>

char __cdecl fcn_0041d500(unsigned int protect)
{
	MEMORY_BASIC_INFORMATION mbi;

	VirtualQuery(fcn_0041d500, &mbi, 0x1c);

	switch (protect & 0xFF) {
	case 2:
	case 4:
		return mbi.Protect == 2 || mbi.Protect == 4;
	case 0x10:
	case 0x20:
	case 0x40:
	case 0x80:
		return 1;
	}
	return 0;
}
