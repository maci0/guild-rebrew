// FUNCTION: GOLD 0x0046c550

#include "gold_gui.h"

typedef struct Group {
	int count;
	int sel;
	int ids[33];
} Group;
// SIZE 0x8c

extern Group g_00fa5aa4[8]; /* 0x00fa5aa4 */
extern GuiEnt* g_00f8f080; /* 0x00f8f080 */

void __cdecl fcn_0046c620(int g, int sel);

void __cdecl fcn_0046c550(int g, int id)
{
	g_00fa5aa4[g].ids[g_00fa5aa4[g].count] = id;
	g_00f8f080[id].dirty = 1;
	g_00f8f080[id].flags &= ~2;
	g_00fa5aa4[g].count++;
	if (g_00fa5aa4[g].sel == -1) {
		fcn_0046c620(g, 0);
	}
}
