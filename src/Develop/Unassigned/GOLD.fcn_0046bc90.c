#include <stdarg.h>
#include <string.h>

#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLD 0x0046bc90 */
void __cdecl fcn_0046bc90(int index, int count, ...)
{
	GuiEnt* p;
	int i;
	va_list args;
	p = &g_00f8f080[index];
	p->u.text[0x5c] = 0;
	va_start(args, count);
	for (i = 0; i < count; i++) {
		strcat(p->u.text + 0x5c, va_arg(args, char*));
		strcat(p->u.text + 0x5c, "|");
	}
	va_end(args);
}
