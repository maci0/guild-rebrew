

#include "gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"

extern GOLD_GUI_WINDOW g_00f8f120[]; /* 0x00f8f120 */
extern int g_006ed938; /* 0x006ed938 */
extern char s_005feb68[]; /* 0x005feb68 */
extern char s_005feb3c[]; /* 0x005feb3c */

void __cdecl fcn_004222b0(const char* msg);
void __cdecl fcn_004796b0(int a);

/* ADDRESS: GOLD 0x00476700 */
void __cdecl fcn_00476700(void)
{
	GOLD_GUI_WINDOW* m;

	m = &g_00f8f120[g_006ed938];
	if (m->active == 0) {
		fcn_004222b0(s_005feb68);
		return;
	}
	if (m->unk_028 == 0) {
		fcn_004222b0(s_005feb3c);
		return;
	}
	fcn_004796b0(m->unk_028);
}
