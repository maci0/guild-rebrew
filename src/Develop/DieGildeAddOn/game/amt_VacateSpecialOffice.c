


#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_664e0c[];

int __cdecl amt_FindOfficeSlotByType(int id, int* out);
int __cdecl gm_LookupEntityRecordById(int h);
#include "Develop/DieGildeAddOn/game/aemter.h"

/* ADDRESS: GOLDDE 0x0049b970 */
void __cdecl amt_VacateSpecialOffice(void)
{
	int info[6];
	int n;

	n = (*(int*)&gm_GameTime);
	if (n >= 4) {
		n = n % 4;
		if (n != 0) {
			n = g_664e0c[n];
			if (amt_FindOfficeSlotByType(n, info) != 0) {
				if (gm_LookupEntityRecordById(info[1]) != 0) {
					amt_SendOfficeCommand(info[0], 0, 0, 1, 0xff);
				}
			}
		}
	}
}
