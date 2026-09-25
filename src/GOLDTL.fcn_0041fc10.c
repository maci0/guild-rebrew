// FUNCTION: GOLD 0x423930
// SIZE: 98
// FUNCTION: GOLDTL 0x41fc10
// SIZE: 98

#include <windows.h>

extern int g_6b71a4;
extern CRITICAL_SECTION g_14cc5a0;
int __cdecl fcn_0042ae10(int, int);

void __cdecl fcn_0041fc10(char* p, int a2)
{
	if (g_6b71a4 != 0 && p != 0) {
		EnterCriticalSection(&g_14cc5a0);
		*(int*) (p + 0x118) = a2;
		if (*(int*) (p + 0x114) == 0 && p[0x104] != 0) {
			*(int*) (p + 0x11c) = a2;
			if (*(int*) (p + 0x100) != 0) {
				fcn_0042ae10(*(int*) (p + 0x100), a2);
			}
		}
		LeaveCriticalSection(&g_14cc5a0);
	}
}
