#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl msx_FindWaveDriverIndex(int *);
int __cdecl msx_CloseStream(int);

/* ADDRESS: GOLDTL 0x0042aca0 */
int __cdecl fcn_0042aca0(int *o)
{
	int r = 0;
	int idx;
	int i;
	int v;

	if (g_6b7f90 != 0 && (idx = msx_FindWaveDriverIndex(o)) >= 0) {
		for (i = 0; i < o[6]; i++) {
			v = ((int *) g_6b7f50[idx])[i];
			if (v != 0 && msx_CloseStream(v) != 0) {
				r = -1;
			}
		}
	} else {
		r = -1;
	}
	return r;
}
