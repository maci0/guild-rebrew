/* ADDRESS: GOLD 0x005f3244 */
extern char g_6772c8[];



#include <windows.h>

void __cdecl fcn_00411780(int a1, int a2, char* fmt, ...)
{
	char buf[0x400];
	char* s;
	va_list va;

	va_start(va, fmt);
	s = buf;
	s += wsprintfA(s, fmt, va);
	wsprintfA(s, g_6772c8, a2);
}
