


#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl msx_CloseStream(int);

/* ADDRESS: GOLDDE 0x00425270 */
int __cdecl msx_CloseAllStreams(void)
{
	int r = 0;
	int i;
	int j;

	if (msx_Initialized != 0) {
		for (i = 0; i < 0x10; i++) {
			if (msx_WaveDrivers[i] != 0) {
				for (j = 0; j < msx_WaveDrivers[i][6]; j++) {
					if (msx_StreamHandles[i][j] != 0 && msx_CloseStream(msx_StreamHandles[i][j]) != 0) {
						r = -1;
					}
				}
			}
		}
	} else {
		r = -1;
	}
	return r;
}
