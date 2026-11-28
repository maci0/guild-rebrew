#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6a25bc;
extern int g_6a25c4[4];
extern int g_6a25d4;
extern int g_6a25d8;
extern int g_6a25dc;
extern int g_6a25e0;
extern int g_6a25e4;
extern int g_6a25e8;
extern int g_6a25f0;



void __cdecl d2_DestroyElement(int);
void __cdecl d2_DestroyForm(int);
/* ADDRESS: GOLD 0x529ff0 */

/* ADDRESS: GOLDDE 0x005180a0 */
void __cdecl d2_DestroySelectionPanel(void)
{
	int i;

	if (g_6a25b8 != -1) {
		for (i = 0; i < 4; i++) {
			if (g_6a25c4[i] != -1) {
				d2_DestroyElement(g_6a25c4[i]);
				g_6a25c4[i] = -1;
			}
		}
		d2_DestroyForm(g_6a25b8);
		g_6a25b8 = -1;
		g_6a25bc = -1;
		d2_CurrentValueBar = -1;
		g_6a25f0 = -1;
		g_6a25ec = -1;
		g_6a25e4 = -1;
		g_6a25e8 = -1;
		g_6a25dc = -1;
		g_6a25e0 = -1;
		g_6a25d8 = -1;
		g_6a25d4 = -1;
	}
}
