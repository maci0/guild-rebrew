


extern int cut_SkipMode;
extern int g_772f64;
extern int g_772f68;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_RemoveSkyLayer(int, int);
void __cdecl d3_FreeSkyDome(int);

/* ADDRESS: GOLDDE 0x004d1580 */
void __cdecl d3_DestroySkyLayer(void)
{
	if (cut_SkipMode == 0) {
		if (g_772f64 != 0) {
			d3_RemoveSkyLayer(g_772f68, g_772f64);
		}
		d3_FreeSkyDome(g_772f68);
		g_6b89c0 = 0;
	}
}
