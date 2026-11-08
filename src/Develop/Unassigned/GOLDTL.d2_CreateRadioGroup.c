#include <stdarg.h>

#include "client_types.h"
typedef Group_102cbc4 Group;
// SIZE 0x8c

typedef struct Slot {
	char pad0[0x58];
	int dirty;
	char pad5c[0x1d0 - 0x5c];
	int flags;
	char pad1d4[0x2f4 - 0x1d4];
} Slot;
// SIZE 0x2f4

extern Group_102cbc4 g_102cbc4[8];
extern char* g_1015ea0;
extern char s_67d4b0[];

#include "Develop/Units/Error/error_message.h"

/* ADDRESS: GOLDTL 0x004693b0 */
int __cdecl d2_CreateRadioGroup(int n, ...)
{
	int i;
	int j;
	va_list ap;

	for (i = 0; i < 8; i++) {
		if (g_102cbc4[i].count == 0) {
			break;
		}
	}
	if (i >= 8) {
		return -1;
	}
	if (n > 0x20) {
		ReportClientMessage(s_67d4b0);
		return -1;
	}
	g_102cbc4[i].count = n;
	g_102cbc4[i].sel = -1;
	va_start(ap, n);
	for (j = 0; j < n; j++) {
		g_102cbc4[i].ids[j] = va_arg(ap, int);
		((Slot*)g_1015ea0)[g_102cbc4[i].ids[j]].dirty = 1;
		((Slot*)g_1015ea0)[g_102cbc4[i].ids[j]].flags &= ~2;
	}
	va_end(ap);
	return i;
}
