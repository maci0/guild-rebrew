#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/game_matrices.h"




#include "Develop/DieGildeAddOn/loadsave/loadsave.h"

/* ADDRESS: GOLDDE 0x0050d8e0 */
int __cdecl ls_LoadGameMatrices(void* x)
{
	int n;
	int i;
	int j;

	if (ls_SaveVersion < 0x1003a) {
		n = 0x100;
	} else {
		n = ls_SaveVersion < 0x10042 ? 0x200 : 0x300;
	}
	for (j = 0; j < n; j++) {
		for (i = 0; i < n; i++) {
			if (ls_ReadVfsDataChecked(&gm_EntityRelationMatrix[j][i], 1, 1, x) == 0) {
				return 0;
			}
		}
	}
	if (ls_SaveVersion >= 0x10036) {
		for (j = 0; j < n; j++) {
			for (i = 0; i < n; i++) {
				if (ls_ReadVfsDataChecked(&gm_RelationDeltaMatrix[j][i], 1, 1, x) == 0) {
					return 0;
				}
			}
		}
	}
	return 1;
}
