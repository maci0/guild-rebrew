#include <string.h>
#pragma intrinsic(strcpy)

__declspec(dllimport) unsigned int __stdcall GetPrivateProfileIntA(const char *, const char *, int, const char *);

/* ADDRESS: GOLD 0x00575880 */
void __cdecl fcn_00575880(char *src)
{
	strcpy((char *)0x6fa0e0, src);
	*(unsigned int *)0x6f263c = GetPrivateProfileIntA(
		(const char *)0x62916c,
		(const char *)0x629174,
		0,
		(const char *)0x6fa0e0);
}
