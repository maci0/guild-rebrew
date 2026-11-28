extern char str_Error_hex[];



#include <windows.h>

/* ADDRESS: GOLDDE 0x004103e0 */
void __cdecl io_FormatInputError(int unused, int hr, char* fmt, ...)
{
	char buf[0x400];
	char* s;
	va_list va;

	va_start(va, fmt);
	s = buf;
	s += wsprintfA(s, fmt, va);
	wsprintfA(s, str_Error_hex, hr);
}
