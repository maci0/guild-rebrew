#include "Develop/DieGildeAddOn/game/game_matrices.h"

/* ADDRESS: GOLD 0x0050c520 */
/* ADDRESS: GOLDTL 0x0050f950 */
int __cdecl fcn_0050f950(int a1, int a2)
{
	if (a1 == a2) {
		return 0x7f;
	}
	return (signed char) *(char*) (((char*)g_869480) + a1 * 768 + a2);
}
