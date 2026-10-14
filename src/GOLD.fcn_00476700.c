

#include "gold_gui.h"

extern GuiWin g_00f8f120[]; /* 0x00f8f120 */
extern int g_006ed938; /* 0x006ed938 */
extern char s_005feb68[]; /* 0x005feb68 */
extern char s_005feb3c[]; /* 0x005feb3c */

void __cdecl fcn_004222b0(const char* msg);
void __cdecl fcn_004796b0(int a);

void __cdecl fcn_00476700(void)
{
	GuiWin* m;

	m = &g_00f8f120[g_006ed938];
	if (m->active == 0) {
		fcn_004222b0(s_005feb68);
		return;
	}
	if (m->f28 == 0) {
		fcn_004222b0(s_005feb3c);
		return;
	}
	fcn_004796b0(m->f28);
}
