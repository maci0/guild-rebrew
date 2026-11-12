#include <stdarg.h>
#include <string.h>

#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLD 0x0046bc90 */
void __cdecl fcn_0046bc90(int index, int count, ...)
{
	char* text;
	va_list args;
	text = g_00f8f080[index].u.text + 0x5c;
	*text = 0;
	va_start(args, count);
	if (count > 0) {
		index = count;
		do {
			strcat(text, va_arg(args, char*));
			strcat(text, "|");
		} while (--index != 0);
	}
	va_end(args);
}
