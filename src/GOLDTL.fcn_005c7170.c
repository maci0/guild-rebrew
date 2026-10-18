

#include "client_types.h"
typedef Loot_7774a0 Loot;
// SIZE 0x40

extern Loot_7774a0 g_7774a0[32];
extern int g_14ce8e0;
extern int g_774654;
extern int g_100f1dc;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_005c69d0(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_005c6a10(int, int);

int __cdecl fcn_00471f80(int);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005c7170(int a1)
{
	int dlg;
	int i;

	dlg = fcn_00470820(0, 0, "locations\\diebesgilde\\diebesgilde_trainieren");
	fcn_00471b60(dlg);
	fcn_005c69d0(a1);
	fcn_00473a90(0, 0);
	do {
		fcn_005c6a10(dlg, 2);
		if (g_14ce8e0 != 0) {
			if (CountDisplayCounters() == 0) {
				g_774654 = 1;
			} else {
				for (i = 0; i < 32; i++) {
					if (g_7774a0[i].btn != -1 && fcn_00471f80(g_7774a0[i].btn) != 0) {
						d2_SetElementValue(g_7774a0[i].btn, 0);
					}
				}
				ResetDisplayCounters();
			}
		}
		if (g_100f1dc != -1 && g_100f1dc == 0x113) {
			for (i = 0; i < 32; i++) {
				if (g_7774a0[i].btn != -1 && fcn_00471f80(g_7774a0[i].btn) != 0) {
					d2_SetElementValue(g_7774a0[i].btn, 0);
				}
			}
			ResetDisplayCounters();
		}
	} while (fcn_005373e0((void*) fcn_005c7170, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
