

#include "client_types.h"
typedef Loot_7774a0 Loot;
// SIZE 0x40

extern Loot_7774a0 g_7774a0[32];
extern int g_14ce8e0;
extern int g_774654;
extern int g_100f1dc;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_005c69d0(char*);
int __cdecl fcn_00525fb0(char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_005c6a10(int, int);

int __cdecl fcn_00471f80(int);
void __cdecl fcn_00472380(int, int);

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005ae4f0(char* e)
{
	int dlg;
	int i;

	if (fcn_00525fb0(e) == 0) {
		dlg = fcn_00470820(0, 0, "locations\\diebesgilde\\diebesgilde_trainieren");
		fcn_005c69d0(e);
		fcn_00473a90(0, 0);
		do {
			fcn_005c6a10(dlg, 2);
			if (g_14ce8e0 != 0) {
				if (CountDisplayCounters() == 0) {
					g_774654 = 1;
				} else {
					for (i = 0; i < 32; i++) {
						if (g_7774a0[i].btn != -1 && fcn_00471f80(g_7774a0[i].btn) != 0) {
							fcn_00472380(g_7774a0[i].btn, 0);
						}
					}
					ResetDisplayCounters();
				}
			}
			if (g_100f1dc != -1 && g_100f1dc == 0x113) {
				for (i = 0; i < 32; i++) {
					if (g_7774a0[i].btn != -1 && fcn_00471f80(g_7774a0[i].btn) != 0) {
						fcn_00472380(g_7774a0[i].btn, 0);
					}
				}
				ResetDisplayCounters();
			}
		} while (fcn_005373e0((void*) fcn_005ae4f0, 0x677c7) != 0);
		fcn_00471e30(dlg);
		fcn_00532ef0();
	}
}
