#include "Develop/DieGildeAddOn/game/game_matrices.h"




unsigned int __cdecl vfs_fwrite(void*, int, int, int);

/* ADDRESS: GOLDDE 0x00509b30 */
int __cdecl ls_SaveRelationMatrices(int x)
{
	int i;
	int j;

	for (j = 0; j < 0x300; j++) {
		for (i = 0; i < 0x300; i++) {
			if (vfs_fwrite(&gm_EntityRelationMatrix[j][i], 1, 1, x) <= 0) {
				return 0;
			}
		}
	}
	for (j = 0; j < 0x300; j++) {
		for (i = 0; i < 0x300; i++) {
			if (vfs_fwrite(&gm_RelationDeltaMatrix[j][i], 1, 1, x) <= 0) {
				return 0;
			}
		}
	}
	return 1;
}
