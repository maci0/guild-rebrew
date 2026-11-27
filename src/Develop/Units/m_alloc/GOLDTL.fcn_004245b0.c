#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x004245b0 */
int __cdecl sbs_UnloadSoundBanks(char* name)
{
	char* e;
	char* prev;
	char* next;
	int r;

	r = 0;
	prev = 0;
	if (sbs_BankManager != 0) {
		if (name != 0) {
			for (e = *(char**) (sbs_BankManager + 0x38); e != 0; e = *(char**) (e + 0x104)) {
				if (strcmp(e, name) == 0) {
					if (prev != 0) {
						*(char**) (prev + 0x104) = *(char**) (e + 0x104);
					} else {
						*(char**) (sbs_BankManager + 0x38) = *(char**) (e + 0x104);
					}
					*(int*) (sbs_BankManager + 0x34) -= *(int*) (e + 0x100);
					m_FreeTracked(e);
					g_6b7d6c++;
					break;
				}
				prev = e;
			}
		} else {
			e = *(char**) (sbs_BankManager + 0x38);
			while (e != 0) {
				next = *(char**) (e + 0x104);
				*(int*) (sbs_BankManager + 0x34) -= *(int*) (e + 0x100);
				m_FreeTracked(e);
				g_6b7d6c++;
				e = next;
			}
		}
	} else {
		r = -1;
	}
	return r;
}
