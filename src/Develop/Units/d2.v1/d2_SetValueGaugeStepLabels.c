#include <stdarg.h>
#include <string.h>

typedef struct Slot {
	char pad[0xe8];
	char text[0x2f4 - 0xe8];
} Slot;
// SIZE 0x2f4

#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLDTL 0x00468bb0 */
void __cdecl d2_SetValueGaugeStepLabels(int slot, int n, ...)
{
	Slot* p;
	int i;
	va_list ap;

	p = (Slot*)&((D2_CONTROL_TL*)g_1015ea0)[slot];
	*((char*)((D2_CONTROL_TL*)p) + 0xe8) = 0;
	va_start(ap, n);
	for (i = 0; i < n; i++) {
		strcat(((char*)((D2_CONTROL_TL*)p) + 0xe8), va_arg(ap, char*));
		strcat(((char*)((D2_CONTROL_TL*)p) + 0xe8), "|");
	}
	va_end(ap);
}
