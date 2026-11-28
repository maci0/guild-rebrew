#include "Develop/DieGildeAddOn/game/game_matrices.h"

/* ADDRESS: GOLD 0x0050c520 */
/* ADDRESS: GOLDTL 0x0050f950 */
int __cdecl gm_GetEntityRelation(int row, int column)
{
	if (row == column) {
		return 0x7f;
	}
	return (signed char) *(char*) (((char*)gm_EntityRelationMatrix) + row * 768 + column);
}
