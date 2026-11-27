


#include "client_types.h"
extern Slot170_7731b8 g_7731b8[8];
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl gm_LookupSlot170ByKey(int selectedKey)
{
	int i;
	int a;

	if (selectedKey == -1) {
		return 0;
	}
	i = 0;
	a = (int) g_7731b8;
	do {
		if (*(int*) a == selectedKey) {
			return (int) (((char*)g_7731b8) + i * 368);
		}
		a += 0x170;
		i++;
	} while (a < (int) &cm_LastCrimeId);
	return 0;
}
