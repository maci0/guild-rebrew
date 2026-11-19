#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x0042d5f0 */
void __cdecl fcn_0042d5f0(void)
{
	int i;

	for (i = 0; i < 128; i++) {
		if (*(void**) (txt_TextBanks[i] + 0x68) != 0) {
			m_FreeTracked(*(void**) (txt_TextBanks[i] + 0x68));
			*(void**) (txt_TextBanks[i] + 0x68) = 0;
			memset(txt_TextBanks[i], 0, 0x74);
		}
	}
}
