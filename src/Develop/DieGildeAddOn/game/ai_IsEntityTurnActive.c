extern unsigned char gm_PlayerCount;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned int nt_LocalShardIndex;
extern unsigned int main_PlayerTurnIndex;

int __cdecl fcn_0047d220(char* a);

/* Wall: the reference keeps p in ecx across the fcn_0047d220 call and reads
 * [ecx+4] after it; no conforming C compiler may assume a call preserves ecx,
 * so the first block cannot be reproduced from C. The body matches the guard,
 * the modulo gates and both comparisons. The 96-byte extent also includes the
 * 10 nop bytes after the 86-byte body. */
/* ADDRESS: GOLDTL 0x0047d240 */
/* ADDRESS: GOLDDE 0x0046c200 */
int __cdecl ai_IsEntityTurnActive(char* entity)
{
	int turn_slice;
	unsigned int seed;

	if (fcn_0047d220(entity) == 0) {
		return 0;
	}
	if (gm_PlayerCount != 0) {
		turn_slice = nt_ClientSocket;
		seed = *(unsigned int*) (entity + 4);
		if (turn_slice != -1) {
			if (seed % gm_PlayerCount != nt_LocalShardIndex) {
				return 0;
			}
		} else {
			if (seed % gm_PlayerCount != main_PlayerTurnIndex) {
				return 0;
			}
		}
	}
	return 1;
}
