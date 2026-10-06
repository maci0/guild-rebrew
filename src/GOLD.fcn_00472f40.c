// FUNCTION: GOLD 0x00472f40

#include <string.h>

#include "gold_gui.h"

extern GuiEnt* g_00f8f080; /* 0x00f8f080 */
extern GuiEnt** g_006ed964; /* 0x006ed964 */

void __cdecl fcn_00472f40(int slot)
{
	GuiEnt* s;
	int i;
	int free;

	free = -1;
	i = 0x2ff;
	s = &g_00f8f080[slot];
	do {
		if (g_006ed964[i] == s) {
			if (free != -1) {
				g_006ed964[free] = g_006ed964[i];
				memmove(&g_006ed964[i], &g_006ed964[i + 1], 0xbf8 - i * 4);
			}
			return;
		}
		if (g_006ed964[i] != 0 && free == -1) {
			free = i + 1;
		}
		i--;
	} while (i > 0);
}
