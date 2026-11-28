


#include <string.h>

// SIZE 0xc
struct slot {
	void* obj;
	int ctl;
	int dlg;
};

#include "Develop/DieGildeAddOn/game/he_action.h"










extern unsigned char* g_7d1980[];
#include "Develop/client_types.h"

extern int he_LastEventSlot;
extern int g_7749d8;
extern int g_7dc424;

void __cdecl m_FreeTracked(void*);
void __cdecl d2_CloseActionPopup(HE_ACTION*);

/* ADDRESS: GOLDDE 0x0052c810 */
void __cdecl he_FreeAction(HE_ACTION* u)
{
	int i;
	int n;

	if (u == 0) {
		return;
	}
	if (u->data != 0) {
		m_FreeTracked(u->data);
		u->data = 0;
	}
	if (u->flags & 8) {
		for (i = 0; i < 256; i++) {
			if (((HE_ACTION**)g_7d1980)[i] == u) {
				break;
			}
		}
		if (((HE_ACTION**)g_7d1980)[i] != u) {
			return;
		}
		if (((HE_ACTION**)g_7d1980)[i]->slot != 0 && ((struct slot*) ((HE_ACTION**)g_7d1980)[i]->slot)->dlg != -1) {
			d2_CloseActionPopup(((HE_ACTION**)g_7d1980)[i]);
		}
		((HE_ACTION**)g_7d1980)[i] = 0;
		if (i == g_7749d8) {
			for (n = g_7749d8; n >= 0; n--) {
				if (((HE_ACTION**)g_7d1980)[n] != 0) {
					break;
				}
			}
			g_7749d8 = n < 0 ? 0 : n;
		}
	}
	g_7dc424--;
	memset(u, 0, sizeof(HE_ACTION));
	if (u == &he_ActionSlots[he_LastEventSlot]) {
		for (n = he_LastEventSlot; n >= 0; n--) {
			if (he_ActionSlots[n].kind != 0) {
				break;
			}
		}
		he_LastEventSlot = n < 0 ? 0 : n;
	}
}
