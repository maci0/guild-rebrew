


#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl fcn_0042ac40(int);

int __cdecl fcn_0042ad00(void)
{
	int r = 0;
	int i;
	int j;

	if (g_6b7f90 != 0) {
		for (i = 0; i < 0x10; i++) {
			if (g_6b7ed0[i] != 0) {
				for (j = 0; j < g_6b7ed0[i][6]; j++) {
					if (g_6b7f50[i][j] != 0 && fcn_0042ac40(g_6b7f50[i][j]) != 0) {
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
