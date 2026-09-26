#include <stdarg.h>
#include <string.h>

typedef struct Slot {
	char pad[0xe8];
	char text[0x2f4 - 0xe8];
} Slot;
// SIZE 0x2f4

extern char* g_1015ea0;

// FUNCTION: GOLDTL 0x468bb0
// SIZE: 128
void __cdecl fcn_00468bb0(int slot, int n, ...)
{
	Slot* p;
	int i;
	va_list ap;

	p = &((Slot*)g_1015ea0)[slot];
	p->text[0] = 0;
	va_start(ap, n);
	for (i = 0; i < n; i++) {
		strcat(p->text, va_arg(ap, char*));
		strcat(p->text, "|");
	}
	va_end(ap);
}
