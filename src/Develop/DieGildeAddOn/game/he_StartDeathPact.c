#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char gm_EntitySlotTable[];
extern pos14_7f4c00 gm_GameTime;

int __cdecl ai_CollectMatchingBuildings(char*, int, int, int, int, int, int, int*);
void __cdecl gm_AddTime(void*, int, int, int);
void __cdecl he_FreeAction(char*);
int __cdecl cm_SendSetHE(char, unsigned char*);

/* ADDRESS: GOLDTL 0x00578e10 */
void __cdecl he_StartDeathPact(char* action)
{
	int flag;
	int zero;
	int n;
	char* rec;

	flag = 4;
	zero = 0;
	if ((*(unsigned char*) (action + 0x78) & flag) != 0) {
		return;
	}
	rec = ((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[*(unsigned short*) (action + 8)]);
	n = ai_CollectMatchingBuildings(rec,
	    5, flag, zero, zero, zero, 5, (int*) (action + 0xb4));
	if (n == 0) {
		he_FreeAction(action);
		return;
	}
	if (n < 5) {
		*(int*) (action + 0xb4 + n * 4) = 0;
	}
	*(int*) (action + 0xb0) = 0;
	*(pos14_7f4c00*) (action + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
	gm_AddTime(action + 0x52, 0, 1, 0);
	*(int*) (action + 0x84) = cm_SendSetHE(0, (unsigned char*) action);
}
