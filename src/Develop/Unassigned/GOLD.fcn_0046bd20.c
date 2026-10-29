

#include <string.h>

#include "gold_gui.h"

extern GuiEnt* g_00f8f080; /* 0x00f8f080 */

void __cdecl fcn_0046bd20(int slot, int n, char* out)
{
	char buf[0x400];
	char* p;
	char* q;
	int i;

	i = 0;
	strcpy(buf, (char*) g_00f8f080 + slot * 0x2ec + 0xdc);
	q = buf;
	p = strchr(buf + 1, '|');
	for (; i < n; i++) {
		if (p == 0) {
			return;
		}
		q = p;
		p = strchr(p + 1, '|');
	}
	if (p != 0) {
		*p = 0;
		strcpy(out, q);
	}
}
